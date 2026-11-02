// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Rva0051A5A0Host::setup at retail 0x00518FF0 (282 bytes, ret 4). The only
// caller is the matched Rva0051A5A0Host::apply (0x0051A5A0), which passes 0;
// the host's identity is not recovered, so the name stays address-derived.
// When the flag at +0x3D3 changes and both windows exist, it rebuilds the
// GameWindowManager tab list (registerTabList is vtable slot 0x9C,
// clearTabList 0xA0, winSetFocus 0xB0), the same push_front/push_back/
// clear/register sequence as the matched
// BfmeAptScreenOnlineLogin_onInitGadget.cpp.
//
// Compiler context read from retail:
//  * push_front (0x004FFE70) and push_back (0x00469A90) are called out of
//    line and their bodies inline _M_create_node, so STLport's try/unwind is
//    compiled out (_STLP_NO_EXCEPTIONS); the node allocator is the static one.
//  * push_back receives a temporary copy of the +0x3C8 pointer, which a
//    GameWindow * lvalue would not need: the field is kept as an untyped
//    pointer and converted at the call.
//  * The two null checks read the windows into locals; reading the fields
//    directly swaps the enable byte (retail CL) with the check temporaries.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class GameWindow;

typedef std::list<GameWindow *> GameWindowList;

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void registerTabList(GameWindowList tabList);
	virtual void clearTabList();
	virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual int winSetFocus(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

class Rva0051A5A0Host
{
public:
	void setup(int enable);

private:
	unsigned char m_lead[0x3bc];
	GameWindow *m_window3BC;				// +0x3BC
	unsigned char m_gap3C0[0x3c8 - 0x3c0];
	void *m_window3C8;						// +0x3C8
	unsigned char m_gap3CC[0x3d3 - 0x3cc];
	unsigned char m_flag3D3;				// +0x3D3
};

// ?setup@Rva0051A5A0Host@@QAEXH@Z
void Rva0051A5A0Host::setup(int enable)
{
	unsigned char en = (unsigned char)enable;
	if (en == m_flag3D3)
		return;
	void *second = m_window3C8;
	if (second == 0)
		return;
	GameWindow *first = m_window3BC;
	if (first == 0)
		return;

	m_flag3D3 = en;
	if (en)
	{
		GameWindowList tabList;
		tabList.push_front(m_window3BC);
		tabList.push_back((GameWindow *)m_window3C8);
		TheWindowManager->clearTabList();
		TheWindowManager->registerTabList(tabList);
		TheWindowManager->winSetFocus(m_window3BC);
	}
	else
		TheWindowManager->clearTabList();
}
