// Copyright Kite & Lightning

#include "imgui_user.h"
#include "imgui.h"

#ifdef IMGUIUX_SHAREDLIB

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
