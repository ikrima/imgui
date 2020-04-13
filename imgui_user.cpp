// Copyright Kite & Lightning

#include "imgui_user.h"
#include "imgui.h"

#if IMGUIUX_SHAREDLIB

namespace
{
    ImGuiContext* globalImGuiCtx = nullptr;

}

ImGuiContext* ImGuiUX::GetGlobalImGuiCtx()
{
    return globalImGuiCtx;
}

void ImGuiUX::SetGlobalImGuiCtx(ImGuiContext* InCtx)
{
    globalImGuiCtx = InCtx;
}

#endif
