#include <Windows.h>
#include <thread>
#include <dwmapi.h>
#include <d3d11.h>
#include <windowsx.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "Helpers/memory.h"
#include "Helpers/vector.h"
#include "Features/ESP.h"
#include "Helpers/gui.h"
#include "Features/AntiFlash.h"
#pragma comment(lib, "dwmapi.lib")

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam)) return 0L;
	if (message == WM_DESTROY) { PostQuitMessage(0); return 0L; }
	switch (message) {
		case WM_NCHITTEST:
		{
			const LONG borderWidth = GetSystemMetrics(SM_CXSIZEFRAME);
			const LONG titlebarHeight = GetSystemMetrics(SM_CYCAPTION);
			POINT cursorPos = { GET_X_LPARAM(wparam), GET_Y_LPARAM(lparam) };
			RECT windowRect;
			GetWindowRect(window, &windowRect);
			if (cursorPos.y >= windowRect.top && cursorPos.y < windowRect.top + titlebarHeight) return HTCAPTION;
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(window, message, wparam, lparam);
}
INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	DWORD64 client = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("client.dll"));
	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = window_procedure;
	wc.hInstance = instance;
	wc.lpszClassName = L"OverFlowOverlayClass";
	RegisterClassExW(&wc);
	const HWND overlay = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,wc.lpszClassName,L"OverFlowOverlay",WS_POPUP,0,0,screenWidth,screenHeight,nullptr,nullptr,wc.hInstance,nullptr);
	SetLayeredWindowAttributes(overlay, RGB(0,0,0), BYTE(255), LWA_ALPHA);
	{
		RECT client_area{};
		GetClientRect(overlay, &client_area);
		RECT window_area{};
		GetWindowRect(overlay, &window_area);
		POINT diff{};
		ClientToScreen(overlay, &diff);
		const MARGINS margins{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom,
		};
		DwmExtendFrameIntoClientArea(overlay, &margins);
	}
	LONG exStyle = GetWindowLong(overlay, GWL_EXSTYLE);
	SetWindowLong(overlay, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(overlay, RGB(0, 0, 0), 255, LWA_COLORKEY);
	DWM_BLURBEHIND bb = { 0 };
	bb.dwFlags = DWM_BB_ENABLE;
	bb.fEnable = TRUE;
	bb.hRgnBlur = NULL;
	DwmEnableBlurBehindWindow(overlay, &bb);
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.RefreshRate.Numerator = 60U; //60FPS
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = overlay;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	constexpr D3D_FEATURE_LEVEL levels[2]{ D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
	D3D_FEATURE_LEVEL level{};
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0U, levels, 2U, D3D11_SDK_VERSION, &sd, &swap_chain, &device, &level, &device_context);
	ID3D11Texture2D* back_buffer{ nullptr };
	swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));
	if (back_buffer) { device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view); back_buffer->Release(); }
	else return 1;
	ShowWindow(overlay, cmd_show);
	UpdateWindow(overlay);
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(overlay);
	ImGui_ImplDX11_Init(device, device_context);
	bool running = true;
	while (running) {
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) running = false;
		}
		if (!running) break;

		//BUGFIX #1: ImGui MouseFix by TxmuXn
		POINT cursorPos_Windows;
		GetCursorPos(&cursorPos_Windows);
		ImVec2 cursorPos = ImVec2(cursorPos_Windows.x, cursorPos_Windows.y);
		bool mouseClicked = GetAsyncKeyState(VK_LBUTTON);
		ImGui::GetIO().MousePos = cursorPos;
		ImGui::GetIO().MouseDown[0] = mouseClicked;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// KEY EVENTS
		if (GetAsyncKeyState(VK_INSERT)) {
			GVARS::Menu::Active = !GVARS::Menu::Active;
			Sleep(200);
		}

		// USER INTERFACE
		if (GVARS::Menu::Active) GUI::Menu();

		// FEATURES
		RunEsp(client, GVARS::Visuals::ESP::enable, GVARS::Visuals::ESP::box, GVARS::Visuals::ESP::name);
		RunAntiFlash(client, GVARS::Visuals::Camera::antiFlash);
		//BUGFIX #2: Menu Variable Fix by TxmuXn

		ImGui::Render();
		float color[4]{ 0,0,0,0 };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		swap_chain->Present(0U, 0U);
		Sleep(10);
	}
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (swap_chain) swap_chain->Release();
	if (device_context) device_context->Release();
	if (device) device->Release();
	if (render_target_view) render_target_view->Release();
	DestroyWindow(overlay);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);
	return 0;
}