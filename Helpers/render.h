#pragma once
#include <imgui.h>

typedef struct {
	ImU32 R;
	ImU32 G;
	ImU32 B;
} RGB;
ImU32 Color(RGB color) { return IM_COL32(color.R, color.G, color.B, 255); }
namespace Render {
	void DrawRect(int x, int y, int width, int height, RGB color, int thickness) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), Color(color), 0, 0, thickness);
	}
}