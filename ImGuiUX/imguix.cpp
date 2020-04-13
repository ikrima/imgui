// Copyright Kite & Lightning

#include "imguix.h"

//========================================================================================================================
#pragma region Support for global across dll boundaries ImGui context
#if IMGUIUX_SHAREDLIB
namespace { ImGuiContext* globalImGuiCtx = nullptr; }
ImGuiContext* ImGuiUX::GetGlobalImGuiCtx() { return globalImGuiCtx; }
void ImGuiUX::SetGlobalImGuiCtx(ImGuiContext* InCtx) { globalImGuiCtx = InCtx; }
#endif
#pragma endregion
//========================================================================================================================
