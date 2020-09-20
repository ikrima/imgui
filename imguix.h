#pragma once

#include "imgui.h"

//========================================================================================================================
#pragma region ImGui Functionality Extensions

namespace ImGuiUX {
  IMGUI_API ImGuiViewport* FindViewportByPlatformHandleRaw(void* platform_handle_raw);     // this is a helper for back-ends. the type platform_handle is decided by the back-end (e.g. HWND, MyWindow*, GLFWwindow* etc.)

  ES2FRCINL() int32_t DragInt(const char* label, int32_t v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d") {
    ImGui::DragInt(label,&v,v_speed,v_min,v_max,format);
    return v;
  }
}

#pragma endregion
//========================================================================================================================

//========================================================================================================================
#pragma region Scoped Helper Utils

#define IM_CONCAT(x, y) IM_CONCAT_IMPL(x, y)
#define IM_CONCAT_IMPL(x, y) x##y
#define IMWITH(x) if(auto IM_CONCAT(hold,__LINE__) = ImGuiUX::##x; IM_CONCAT(hold,__LINE__).IsOpen())


namespace ImGuiUX
{

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

struct [[nodiscard]] ImScopePushId final : _Scope
{
  ImScopePushId(int32_t a_intId)     { ImGui::PushID(a_intId); }
  ImScopePushId(const void* a_ptrId) { ImGui::PushID(a_ptrId); }
  ~ImScopePushId()                   { ImGui::PopID(); }
};

struct [[nodiscard]] ImScopeIndent final : _Scope
{
  ImScopeIndent() { ImGui::Indent(); }
  ~ImScopeIndent() { ImGui::Unindent(); }
};

struct [[nodiscard]] ImScopeWindow final : _Scope
{
  explicit ImScopeWindow(
    const char* name,
    bool* p_open = nullptr,
    ImGuiWindowFlags flags = 0,
    const char* dockSpaceName = nullptr)
  {
      if ((bool)dockSpaceName)
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
  explicit ImScopeMenu(const char* name) { _bOpened = ImGui::BeginMenu(name); }
  ~ImScopeMenu() { if (_bOpened) { ImGui::EndMenu(); } }
};

struct [[nodiscard]] ImScopePopup final : _Scope
{
  explicit ImScopePopup(const char* str_id, ImGuiWindowFlags flags = 0) { _bOpened = ImGui::BeginPopup(str_id,flags); }
  ~ImScopePopup() { if (_bOpened) { ImGui::EndPopup(); } }
};

struct [[nodiscard]] ImScopeVertical final : _Scope
{
  explicit ImScopeVertical(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f) { ImGui::BeginVertical(str_id,size,align); }
  explicit ImScopeVertical(int   id, const ImVec2& size = ImVec2(0, 0), float align = -1) { ImGui::BeginVertical(id,size,align); }
  ~ImScopeVertical() { ImGui::EndVertical(); }
};

struct [[nodiscard]] ImScopeHorizontal final : _Scope
{
  explicit ImScopeHorizontal(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f) { ImGui::BeginHorizontal(str_id,size,align); }
  ~ImScopeHorizontal() { ImGui::EndHorizontal(); }
};

#pragma endregion
//------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------
#pragma region Node Editor Scope Helpers
#if IMGUIUIX_FEATURE_NODEDITOR

namespace ned = ax::NodeEditor;
struct [[nodiscard]] ImScopeNed final : _Scope
{
  ImScopeNed(const char* id, ned::EditorContext* a_nedCtx) { ned::SetCurrentEditor(a_nedCtx); ned::Begin(id); }
  ~ImScopeNed() { ned::End(); ned::SetCurrentEditor(nullptr); }
};

struct [[nodiscard]] ImScopeNedNode final : _Scope
{
  explicit ImScopeNedNode(ned::NodeId id) { ned::BeginNode(id); }
  explicit ImScopeNedNode(uint64_t a_id)  { ned::BeginNode(ned::NodeId(a_id)); }
  ~ImScopeNedNode() { ned::EndNode(); }
};

struct [[nodiscard]] ImScopeNedPin final : _Scope
{
  ImScopeNedPin(ned::PinId a_id, ned::PinKind a_knd) { ned::BeginPin(a_id,a_knd); }
  ImScopeNedPin(uint64_t   a_id, ned::PinKind a_knd) { ned::BeginPin(ned::PinId(a_id),a_knd); }
  ~ImScopeNedPin() { ned::EndPin(); }
};

struct [[nodiscard]] ImScopeNedCreate final : _Scope
{
  explicit ImScopeNedCreate(const ImVec4 & color = ImVec4(1, 1, 1, 1), float thickness = 1.0f) { _bOpened = ned::BeginCreate(color,thickness); }
  ~ImScopeNedCreate() { ned::EndCreate(); }
};

struct [[nodiscard]] ImScopeNedDelete final : _Scope
{
  ImScopeNedDelete() { _bOpened = ned::BeginDelete(); }
  ~ImScopeNedDelete() { ned::EndDelete(); }
};

#endif
#pragma endregion
//------------------------------------------------------------------------------------------------------------------------

inline void Tooltip(const char* Txt)
{
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::TextUnformatted(Txt);
    ImGui::EndTooltip();
  }
}

}


#pragma endregion
//========================================================================================================================
