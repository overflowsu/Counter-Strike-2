#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include "vars.h"

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

                // Add New Tabs Like This
                //ImGui::SetCursorPos(ImVec2{ 220, 30 });
                //if (ImGui::Button("", ImVec2(160, 35))) tab = 2;
                //draw->AddLine(ImVec2(pos.x + 220, pos.y + 65), ImVec2(pos.x + 220 + 160, pos.y + 65), ImColor(0, 255, 255));

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
                        ImGui::OFCheckbox("Anti Flash", &GVARS::Visuals::Camera::antiFlash);

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
}