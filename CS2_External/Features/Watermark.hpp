#pragma once
#include "..\OS-ImGui\imgui\imgui.h"
#include "../Components/GlobalVars.h"
#include "../Components/MenuConfig.hpp"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace Watermark
{
    inline void Render() noexcept
    {
        if (MenuConfig::WaterMark) {
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
            if (ImGui::Begin("ofwatermark", nullptr, windowFlags))
            {
                ImGui::BeginChild("##WM", ImVec2{ 200, 50 }, false);
                {
                    auto pos = ImGui::GetWindowPos();
                    auto size = ImGui::GetWindowSize();
                    auto draw = ImGui::GetWindowDrawList();
                    draw->AddText(ImVec2(pos.x + 65, pos.y + 3), ImColor(255, 255, 255, 255), "overflow.su");
                    draw->AddLine(ImVec2(pos.x + 0, pos.y + 25), ImVec2(pos.x + 600, pos.y + 20), ImColor(0, 255, 255));

                    DWORD buffer_size = 256;
                    wchar_t username[256];
                    if (GetUserName(username, &buffer_size)) {
                        char narrowUsername[256];
                        size_t charsConverted = 0;
                        if (wcstombs_s(&charsConverted, narrowUsername, sizeof(narrowUsername), username, _TRUNCATE) == 0) {
                            if (MenuConfig::watermarkuser) {
                                ImGui::SetCursorPos(ImVec2{ 75, 30 });
                                ImGui::Text(narrowUsername);
                            }
                        }
                    }

                    ImGui::EndChild();
                }

                ImGui::End();
            }
            
        }
    }
}