#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include "vars.h"
#include "keymap.h"
#include "username.h"
#include "../Offsets/client.h"
#include "../Offsets/offsets.h"

namespace GUI {
	void Menu() {
        ImGuiStyle* MenuStyle = &ImGui::GetStyle();
        MenuStyle->WindowRounding = 0.0f;
        MenuStyle->Colors[ImGuiCol_WindowBg] = ImColor(25, 25, 25);
        MenuStyle->Colors[ImGuiCol_ChildBg] = ImColor(25, 25, 25);
        MenuStyle->Colors[ImGuiCol_Button] = ImColor(30, 30, 30);
        MenuStyle->Colors[ImGuiCol_ButtonHovered] = ImColor(35, 35, 35);
        MenuStyle->Colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30);
        MenuStyle->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
        constexpr auto windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        if (ImGui::Begin("of@menu", NULL, windowFlags))
        {
            ImGui::BeginChild("##CONTENT", ImVec2{ 600, 500 }, false);
            {
                static int tab = 1;
                auto pos = ImGui::GetWindowPos();
                auto size = ImGui::GetWindowSize();
                auto draw = ImGui::GetWindowDrawList();

                // HEADER
                ImGui::Text(GVARS::Menu::Name);
                ImGui::SameLine();
                ImGui::TextColored(ImColor(0, 255, 255, 255), GVARS::Menu::Version);
                draw->AddLine(ImVec2(pos.x + 0, pos.y + 20), ImVec2(pos.x + 600, pos.y + 20), ImColor(0, 255, 255));

                // NAVBAR
                ImGui::SetCursorPos(ImVec2{ 0, 30 });
                if (ImGui::Button("Visuals", ImVec2(160, 35))) tab = 1;
                draw->AddLine(ImVec2(pos.x + 0, pos.y + 65), ImVec2(pos.x + 160, pos.y + 65), ImColor(0, 255, 255));

                ImGui::SetCursorPos(ImVec2{ 220, 30 });
                if (ImGui::Button("Misc", ImVec2(160, 35))) tab = 2;
                draw->AddLine(ImVec2(pos.x + 220, pos.y + 65), ImVec2(pos.x + 220 + 160, pos.y + 65), ImColor(0, 255, 255));

                // CONTENTS
                if (tab == 1)
                {
                    MenuStyle->Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
                    ImGui::SetCursorPos(ImVec2{ 0, 75 });
                    if (ImGui::BeginChild("##tab1", ImVec2{ 600, 400 }, false)) {
                        draw->AddText(ImVec2(pos.x + 270, pos.y + 80), ImColor(255, 255, 255, 255), "ESP");
                        draw->AddLine(ImVec2(pos.x + 0, pos.y + 95), ImVec2(pos.x + 600, pos.y + 95), ImColor(0, 255, 255));

                        MenuStyle->Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30);
                        MenuStyle->Colors[ImGuiCol_FrameBgActive] = ImColor(30, 30, 30);
                        MenuStyle->Colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30);

                        ImGui::SetCursorPos(ImVec2{ 5, 35 });
                        ImGui::OFCheckbox("Enable ESP", &GVARS::Visuals::ESP::enable);
                        ImGui::SetCursorPos(ImVec2{ 5, 60 });
                        ImGui::OFCheckbox("Box", &GVARS::Visuals::ESP::box);
                        ImGui::SetCursorPos(ImVec2{ 5, 85 });
                        ImGui::OFCheckbox("Name", &GVARS::Visuals::ESP::name);
                        ImGui::SetCursorPos(ImVec2{ 5, 110 });
                        ImGui::OFCheckbox("Healthbar", &GVARS::Visuals::ESP::healthbar);
                        ImGui::SetCursorPos(ImVec2{ 5, 135 });
                        ImGui::OFCheckbox("Health", &GVARS::Visuals::ESP::health);
                        ImGui::SetCursorPos(ImVec2{ 5, 160 });
                        ImGui::OFCheckbox("Weapon", &GVARS::Visuals::ESP::weapon);
                        ImGui::SetCursorPos(ImVec2{ 5, 185 });
                        ImGui::OFCheckbox("Anti Flash", &GVARS::Visuals::Effects::antiFlash);
                        ImGui::SetCursorPos(ImVec2{ 5, 210 });
                        ImGui::OFCheckbox("Fov Changer", &GVARS::Visuals::Camera::fovchanger);
                        ImGui::SetCursorPos(ImVec2{ 5, 235 });
                        ImGui::SliderInt("Value", &GVARS::Visuals::Camera::fov, 60, 150, "%d");

                        ImGui::EndChild();
                    }
                }
                if (tab == 2)
                {
                    MenuStyle->Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
                    ImGui::SetCursorPos(ImVec2{ 0, 75 });
                    if (ImGui::BeginChild("##tab1", ImVec2{ 600, 400 }, false)) {
                        draw->AddText(ImVec2(pos.x + 250, pos.y + 80), ImColor(255, 255, 255, 255), "Miscellaneous");
                        draw->AddLine(ImVec2(pos.x + 0, pos.y + 95), ImVec2(pos.x + 600, pos.y + 95), ImColor(0, 255, 255));

                        MenuStyle->Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30);
                        MenuStyle->Colors[ImGuiCol_FrameBgActive] = ImColor(30, 30, 30);
                        MenuStyle->Colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30);

                        ImGui::SetCursorPos(ImVec2{ 10, 35 });
                        ImGui::Text("Menu Key:");
                        ImGui::SameLine();
                        if (ImGui::Button(GetKeyName(GVARS::Menu::MenuKey))) ImGui::OpenPopup("Menu Key Binder");
                        if (ImGui::BeginPopupModal("Menu Key Binder", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                            ImGui::Text("Press a Key...");
                            for (int key = 1; key < 256; key++) {
                                if (GetAsyncKeyState(key) & 0x8000) {
                                    GVARS::Menu::MenuKey = key;
                                    ImGui::CloseCurrentPopup();
                                }
                            }
                            ImGui::EndPopup();
                        }
                        ImGui::SetCursorPos(ImVec2{ 5, 60 });
                        ImGui::OFCheckbox("Watermark", &GVARS::Visuals::Menu::watermark);

                        ImGui::EndChild();
                    }
                }

                // FOOTER
                ImGui::SetCursorPos(ImVec2{ 0, 485 });
                draw->AddLine(ImVec2(pos.x + 0, pos.y + 480), ImVec2(pos.x + 600, pos.y + 480), ImColor(0, 255, 255));
                ImGui::Text("%s by", GVARS::Menu::Name);
                ImGui::SameLine();
                ImGui::TextColored(ImColor(0, 255, 255, 255), GVARS::Menu::Author);
                ImGui::SameLine();
                ImGui::Text("for");
                ImGui::SameLine();
                ImGui::TextColored(ImColor(0, 255, 255, 255), GVARS::Menu::Game);

                ImGui::EndChild();
            }
            ImGui::End();
        }
	}
    void Watermark(uintptr_t client) {
        ImGuiStyle* MenuStyle = &ImGui::GetStyle();
        MenuStyle->WindowRounding = 0.0f;
        MenuStyle->Colors[ImGuiCol_WindowBg] = ImColor(25, 25, 25);
        MenuStyle->Colors[ImGuiCol_ChildBg] = ImColor(25, 25, 25);
        MenuStyle->Colors[ImGuiCol_Button] = ImColor(30, 30, 30);
        MenuStyle->Colors[ImGuiCol_ButtonHovered] = ImColor(35, 35, 35);
        MenuStyle->Colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30);
        MenuStyle->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
        constexpr auto windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        std::string username = GetWindowsUsername();
        int fps = static_cast<int>(1.0f / ImGui::GetIO().DeltaTime);
        uintptr_t controller;
        ProcessMgr.ReadMemory(client + cs2_dumper::offsets::client_dll::dwLocalPlayerController, controller);
        uintptr_t ping;
        ProcessMgr.ReadMemory(controller + cs2_dumper::schemas::client_dll::CCSPlayerController::m_iPing, ping);
        std::string name = GVARS::Menu::Name;
        std::string total = name + " / " + username.c_str() + " / " + std::to_string(fps) + " FPS / " + std::to_string(ping) + " MS";
        float width = ImGui::CalcTextSize(total.c_str()).x;
        if (ImGui::Begin("of@watermark", NULL, windowFlags))
        {
            ImGui::BeginChild("##CONTENT", ImVec2{ width + 10, 17 }, false);
            {
                auto pos = ImGui::GetWindowPos();
                auto size = ImGui::GetWindowSize();
                auto draw = ImGui::GetWindowDrawList();

                // CONTENTS
                ImGui::Text(GVARS::Menu::Name);
                ImGui::SameLine();
                ImGui::TextColored(ImColor(0, 255, 255, 255), "/");
                ImGui::SameLine();
                ImGui::Text(username.c_str());
                ImGui::SameLine();
                ImGui::TextColored(ImColor(0, 255, 255, 255), "/");
                ImGui::SameLine();
                ImGui::Text("%d FPS", fps);
                ImGui::SameLine();
                ImGui::TextColored(ImColor(0, 255, 255, 255), "/");
                ImGui::SameLine();
                ImGui::Text("%d MS", ping);
                draw->AddLine(ImVec2(pos.x + 0, pos.y + 16), ImVec2(pos.x + width + 10, pos.y + 16), ImColor(0, 255, 255));

                ImGui::EndChild();
            }
            ImGui::End();
        }
    }
}