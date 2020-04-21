// Copyright Kite & Lightning

#include "imguix.h"
#include "imgui_internal.h"

//========================================================================================================================
#pragma region Support for global across dll boundaries ImGui context
#if IMGUIUX_SHAREDLIB
namespace { ImGuiContext* globalImGuiCtx = nullptr; }
ImGuiContext* ImGuiUX::GetGlobalImGuiCtx() { return globalImGuiCtx; }
void ImGuiUX::SetGlobalImGuiCtx(ImGuiContext* InCtx) { globalImGuiCtx = InCtx; }
#endif
#pragma endregion
//========================================================================================================================


ImGuiViewport* ImGuiUX::FindViewportByPlatformHandleRaw(void* platform_handle_raw)
{
    ImGuiContext& g = *GImGui;
    for (int i = 0; i != g.Viewports.Size; i++)
        if (g.Viewports[i]->PlatformHandleRaw == platform_handle_raw)
            return g.Viewports[i];
    return nullptr;
};
