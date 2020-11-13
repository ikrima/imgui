#pragma once

#ifndef IMGUI_VERSION
#error Must include imgui.h before imgui_internal.h
#endif

//========================================================================================================================
#pragma region Support for global across dll boundaries ImGui context
#if IMGUIUX_SHAREDLIB
// If compiling imgui as a shared dll, we need to wrap the global context with a function
#define GImGui (ImGuiX::GetGlobalImGuiCtx())
#define IMGUI_SET_CURRENT_CONTEXT_FUNC(InCtx) ImGuiX::SetGlobalImGuiCtx(InCtx)

namespace ImGuiX {
    IMGUI_API ImGuiContext* GetGlobalImGuiCtx();
    IMGUI_API void          SetGlobalImGuiCtx(ImGuiContext*);
};

#endif
#pragma endregion
//========================================================================================================================


//========================================================================================================================
#pragma region Widget Extensions

#if IMGUIUIX_FEATURE_ADOBESPECTRUM
#include "ImGuiUX/AdobeSpectrum/imgui_spectrum.h"
#endif

#if IMGUIUIX_FEATURE_NODEDITOR
#include "ImGuiUX/DmdNodeEditor/imgui_node_editor.h"
#endif

#pragma endregion
//========================================================================================================================
