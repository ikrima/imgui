// Copyright Kite & Lightning

#include "imgui_user.h"

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#undef IMGUI_DEFINE_MATH_OPERATORS

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

bool ImGuiUX::Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2,
    float splitter_long_axis_size /*= -1.0f*/)
{
    using namespace ImGui;

    ImGuiContext& g      = *GImGui;
    ImGuiWindow*  window = g.CurrentWindow;
    ImGuiID       id     = window->GetID("##Splitter");
    ImRect        bb;
    bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
    bb.Max = bb.Min
             + CalcItemSize(
                 split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
    return SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
}

const char* ImGuiUX::GetMainHostWindowName()
{
    static const char* mainHostWndName = "MainWindowHost";
    return mainHostWndName;
}
const char* ImGuiUX::GetMainHostDockSpaceName()
{
    static const char* mainDockSpaceName = "MainWindowHostDockSpace";
    return mainDockSpaceName;
}

const char* ImGuiUX::GetMainHostToolMenuName()
{
    static const char* toolMenuName = "Tools";
    return toolMenuName;
}
