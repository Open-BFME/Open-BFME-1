// ?refreshActive@Rva006F88B0Owner@@QAEXH@Z
// ILT 0x000474B5 -> 0x006F7CB0, the matched Rva006F7CB0Owner::refresh(CameraClass *)
// (W3DDevice/GameClient/Rva006F7CB0FrustumVisibility.cpp), called on each item.
class CameraClass;
struct Rva006F7CB0Owner { bool refresh(CameraClass *camera); };
struct Rva006F88B0Item { char m_pad[0x90]; int m_ready; };
struct Rva006F88B0Link { Rva006F88B0Link* m_next; Rva006F88B0Link* m_prev; Rva006F88B0Item* m_item; };
struct Rva006F88B0Owner {
	char m_pad[0x20];
	Rva006F88B0Link* m_head;
	char m_pad2[0x29 - 0x24];
	bool m_wasActive;
	bool m_active;
	void refreshActive(int key);
};
void Rva006F88B0Owner::refreshActive(int key)
{
	m_active = m_wasActive;
	for (Rva006F88B0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		if (((Rva006F7CB0Owner *)n->m_item)->refresh((CameraClass *)key) && n->m_item->m_ready)
			m_active = true;
	}
}
