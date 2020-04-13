#pragma once

#ifndef IMGUI_VERSION
#error Must include imgui.h before imgui_internal.h
#endif

//========================================================================================================================
#pragma region Support for global across dll boundaries ImGui context
#if IMGUIUX_SHAREDLIB
// If compiling imgui as a shared dll, we need to wrap the global context with a function
#define GImGui (ImGuiUX::GetGlobalImGuiCtx())
#define IMGUI_SET_CURRENT_CONTEXT_FUNC(InCtx) ImGuiUX::SetGlobalImGuiCtx(InCtx)

namespace ImGuiUX {
    IMGUI_API ImGuiContext* GetGlobalImGuiCtx();
    IMGUI_API void          SetGlobalImGuiCtx(ImGuiContext*);
};

#endif
#pragma endregion
//========================================================================================================================


//========================================================================================================================
#pragma region Widget Extensions

#if IMGUIUIX_FEATURE_ADOBESPECTRUM
#include "ImGuiUX/AdobeSpectrum/spectrum.h"
#endif

#if IMGUIUIX_FEATURE_NODEDITOR
#include "ImGuiUX/DmdNodeEditor/NodeEditor/include/imgui_node_editor.h"
#endif

#pragma endregion
//========================================================================================================================


//========================================================================================================================
#pragma region Scoped Helper Utils

#define IM_CONCAT(x, y) IM_CONCAT_IMPL(x, y)
#define IM_CONCAT_IMPL(x, y) x##y
#define IMWITH(x) if(auto IM_CONCAT(hold,__LINE__) = ImGuiUX::##x; IM_CONCAT(hold,__LINE__).IsOpen())


namespace ImGuiUX {

    struct [[nodiscard]] _Scope;


//------------------------------------------------------------------------------------------------------------------------
#pragma region ImGui Scope Helpers
    struct [[nodiscard]] ImScopeIndent;
    struct [[nodiscard]] ImScopeWindow;
    struct [[nodiscard]] ImScopeMainMenuBar;
    struct [[nodiscard]] ImScopeMenu;
    struct [[nodiscard]] ImScopePopup;
#pragma endregion
//------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------
#pragma region Node Editor Scope Helpers
#if IMGUIUIX_FEATURE_NODEDITOR

    struct [[nodiscard]] ImScopeNed;
    struct [[nodiscard]] ImScopeNedNode;
    struct [[nodiscard]] ImScopeNedCreate ;
    struct [[nodiscard]] ImScopeNedDelete ;

#endif
#pragma endregion
//------------------------------------------------------------------------------------------------------------------------


}


#pragma endregion
//========================================================================================================================
