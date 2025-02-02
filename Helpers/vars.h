#pragma once
#include <string>

namespace GVARS {
	namespace Menu {
		static const char* Name = "OverFlow";
		static const char* Version = "v0.03";
		static const char* Author = "TxmuXn";
		static const char* Game = "Counter-Strike 2";
		static bool Active = true;
		static int MenuKey = VK_INSERT;
	}
	namespace Visuals {
		namespace ESP {
			static bool enable = false;
			static bool box = false;
			static bool name = false;
			static bool healthbar = false;
			static bool health = false;
			static bool weapon = false;
		}
		namespace Effects {
			static bool antiFlash = false;
		}
		namespace Camera {
			static bool fovchanger = false;
			static int fov = 150;
		}
		namespace Menu {
			static bool watermark = true;
		}
	}
}