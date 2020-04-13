#pragma once



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
#pragma region Scoped Helper Utils



#define IM_CONCAT(x, y) IM_CONCAT_IMPL(x, y)
#define IM_CONCAT_IMPL(x, y) x##y
#define IMWITH(x) if(auto IM_CONCAT(hold,__LINE__) = ImGuiUX::##x; IM_CONCAT(hold,__LINE__).IsOpen())


namespace ImGuiUX {

    struct [[nodiscard]] _Scope
    {
        _Scope() = default;
        _Scope(const _Scope&) = delete;
        _Scope& operator=(const _Scope&) = delete;

        bool IsOpen() const
        {
            return _bOpened;
        }

    protected:
        bool _bOpened = true;
    };



//------------------------------------------------------------------------------------------------------------------------
#pragma region ImGui Scope Helpers
    struct [[nodiscard]] ImScopeIndent final : _Scope
    {
        ImScopeIndent() { ImGui::Indent(); }
        ~ImScopeIndent() { ImGui::Unindent(); }
    };

    struct [[nodiscard]] ImScopeWindow final : _Scope
    {
        ImScopeWindow(
            const char* name,
            bool* p_open = nullptr,
            ImGuiWindowFlags flags = 0,
            const char* dockSpaceName = nullptr)
        {
            if (dockSpaceName)
            {
                const ImGuiID HostDockspaceId = ImGui::GetID(dockSpaceName);
                ImGui::SetNextWindowDockID(HostDockspaceId, ImGuiCond_FirstUseEver);
            }
            _bOpened = ImGui::Begin(name, p_open, flags);
        }

        ~ImScopeWindow()
        {
            // Always call End
            ImGui::End();
        }
    };

    struct [[nodiscard]] ImScopeMainMenuBar final : _Scope
    {
        ImScopeMainMenuBar() { _bOpened = ImGui::BeginMainMenuBar(); }
        ~ImScopeMainMenuBar() { if (_bOpened) { ImGui::EndMainMenuBar(); } }
    };

    struct [[nodiscard]] ImScopeMenu final : _Scope
    {
        ImScopeMenu(const char* name) { _bOpened = ImGui::BeginMenu(name); }
        ~ImScopeMenu()                { if (_bOpened) { ImGui::EndMenu(); } }
    };

    struct [[nodiscard]] ImScopePopup final : _Scope
    {
        ImScopePopup(const char* str_id, ImGuiWindowFlags flags=0) { _bOpened = ImGui::BeginPopup(str_id,flags); }
        ~ImScopePopup()                                            { if (_bOpened) { ImGui::EndPopup(); } }
    };
#pragma endregion
//------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------
#pragma region Node Editor Scope Helpers
#if IMGUIUIX_FEATURE_NODEDITOR

    namespace ned = ax::NodeEditor;
    struct [[nodiscard]] ImScopeNed final : _Scope
    {
        ImScopeNed(const char* id) { ned::Begin(id); }
        ~ImScopeNed() { ned::End(); }
    };

    struct [[nodiscard]] ImScopeNedNode final : _Scope
    {
        ImScopeNedNode(ned::NodeId id) { ned::BeginNode(id); }
        ~ImScopeNedNode()              { ned::EndNode();     }
    };

    struct [[nodiscard]] ImScopeNedCreate final : _Scope
    {
        ImScopeNedCreate(const ImVec4& color = ImVec4(1, 1, 1, 1), float thickness = 1.0f)  { _bOpened = ned::BeginCreate(color,thickness); }
        ~ImScopeNedCreate() { ned::EndCreate(); }
    };

    struct [[nodiscard]] ImScopeNedDelete final : _Scope
    {
        ImScopeNedDelete()  { _bOpened = ned::BeginDelete(); }
        ~ImScopeNedDelete() { ned::EndDelete(); }
    };

#endif
#pragma endregion
//------------------------------------------------------------------------------------------------------------------------


}


#pragma endregion
//========================================================================================================================
