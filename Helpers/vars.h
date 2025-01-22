#pragma once
#include <string>

namespace GVARS {
	namespace Menu {
		static const char* Name = "OverFlow";
		static const char* Version = "v0.02";
		static const char* Author = "TxmuXn";
		static const char* Game = "Counter-Strike 2";
		static bool Active = true;
	}
	namespace Visuals {
		namespace ESP {
			static bool enable = false;
			static bool box = false;
			static bool name = false;
		}
		namespace Camera {
			static bool antiFlash = false;
		}
	}
}