// ?setAddButtonEnabled@Rva00511260Owner@@QAEX_N@Z
struct Rva00579160Manager { void fire(void* target, const char* name, int a, int b, int c, int d, int e, int f); };
// Retail global 0x012F19E8. EA's own name for this pointer; see
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp for the definition.
// This TU keeps its local view type Rva00579160Manager and casts at the use.
class WindowManager;
extern WindowManager* g_rva012F19E8WindowManager;
struct Rva00511260Owner {
	char m_pad[0x250];
	void* m_target;
	char m_pad2[0x292 - 0x254];
	bool m_dirty;
	bool m_enabled;
	void setAddButtonEnabled(bool enabled);
};
void Rva00511260Owner::setAddButtonEnabled(bool enabled)
{
	if (m_dirty || enabled != m_enabled) {
		m_enabled = enabled;
		m_dirty = false;
		((Rva00579160Manager*)g_rva012F19E8WindowManager)->fire(m_target, enabled ? "EnableAddButton" : "DisableAddButton", 0, 0, 0, 0, 0, 0);
	}
}
