#include "ConfigMenu.hpp"
#include "MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../Features/TriggerBot.h"
#include "../Features/AimBot.hpp"
#include <filesystem>

namespace ConfigMenu {
	void RenderConfigMenu() {
		static char configNameBuffer[128] = "";
		static int selectedConfig = -1;
		static const std::string configDir = MenuConfig::path;
		static std::vector<std::string> configFiles;

		ImGui::InputText("Create New", configNameBuffer, sizeof(configNameBuffer));
		configFiles.clear();
		for (const auto& entry : std::filesystem::directory_iterator(configDir))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".config")
			{
				configFiles.push_back(entry.path().filename().string());
			}
		}
		for (int i = 0; i < configFiles.size(); ++i)
		{
			if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
			{
					selectedConfig = i;
			}
		}
		ImGui::Separator();

		if (ImGui::Button("Create"))
		{
			std::string configFileName = std::string(configNameBuffer) + ".config";
			MyConfigSaver::SaveConfig(configFileName);
		}
		if (ImGui::Button("Load") && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::LoadConfig(selectedConfigFile);
		}
		if (ImGui::Button("Save") && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::SaveConfig(selectedConfigFile);
		}
		if (ImGui::Button("Delete") && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			std::string fullPath = configDir + "/" + selectedConfigFile;
			if (std::remove(fullPath.c_str()) == 0)
			{
				configFiles.erase(configFiles.begin() + selectedConfig);
				selectedConfig = -1;
			}
			else
			{
			}
		}
		if (ImGui::Button("Reset"))
		{
			ConfigMenu::ResetToDefault();
		}
    }
    void ResetToDefault() {
		MenuConfig::ShowBoneESP = true;
		MenuConfig::ShowBoxESP = true;
		MenuConfig::ShowHealthBar = true;
		MenuConfig::ShowWeaponESP = true;
		MenuConfig::ShowDistance = true;
		MenuConfig::ShowEyeRay = true;
		MenuConfig::ShowPlayerName = true;
		MenuConfig::AimBot = true;
		MenuConfig::AimPosition = 0;
		MenuConfig::AimPositionIndex = BONEINDEX::head;
		MenuConfig::BoxType = 0;
		MenuConfig::HealthBarType = 0;
		MenuConfig::BoneColor = ImVec4(255, 255, 255, 255);
		MenuConfig::BoxColor = ImVec4(255, 255, 255, 255);
		MenuConfig::EyeRayColor = ImVec4(255, 0, 0, 255);
		MenuConfig::ShowMenu = true;
		MenuConfig::TriggerBot = true;
		MenuConfig::TeamCheck = true;
		MenuConfig::VisibleCheck = true;
		MenuConfig::ShowHeadShootLine = true;
		MenuConfig::HeadShootLineColor = ImVec4(255, 255, 255, 255);
		MenuConfig::AimBotHotKey = 0;
		AimControl::SetHotKey(MenuConfig::AimBotHotKey);
		MenuConfig::ShowLineToEnemy = false;
		MenuConfig::FovLineSize = 60.0f;
		TriggerBot::TriggerDelay = 90;
		AimControl::RCSBullet = 1;
		MenuConfig::TriggerHotKey = 0;
		TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
		MenuConfig::TriggerMode = 0;
		TriggerBot::SetMode(MenuConfig::TriggerMode);//TriggerMode
		AimControl::RCSScale = ImVec2(1.2f, 1.4f);
		MenuConfig::FovLineColor = ImVec4(55, 55, 55, 220);
		MenuConfig::LineToEnemyColor = ImVec4(255, 255, 255, 220);
		MenuConfig::ShowAimFovRange = true;
		MenuConfig::AimFovRangeColor= ImColor(230, 230, 230, 255);
		MenuConfig::OBSBypass = true;
		MenuConfig::BunnyHop = false;
		MenuConfig::ShowWhenSpec = true;
    }
}