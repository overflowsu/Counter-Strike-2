#pragma once
#include <imgui.h>

typedef struct {
	ImU32 R;
	ImU32 G;
	ImU32 B;
} RGB;
inline ImU32 Color(RGB color) { return IM_COL32(color.R, color.G, color.B, 255); }
namespace Render {
	inline void DrawRect(int x, int y, int width, int height, RGB color, int thickness) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), Color(color), 0, 0, thickness);
	}
	inline void DrawFilledRect(int x, int y, int width, int height, RGB color) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), Color(color), 0, 0);
	}
	inline void DrawLabel(int x, int y, RGB color, const char* text) {
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), Color(color), text);
	}
}