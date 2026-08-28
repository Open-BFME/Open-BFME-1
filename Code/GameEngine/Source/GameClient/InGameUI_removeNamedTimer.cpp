// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?removeNamedTimer@InGameUI@@QAEXABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// Open-BFME: InGameUI::removeNamedTimer, retail 0x0044A1B0, 113 bytes.
//
// The reference's body unchanged: look the timer up by name, free its display
// string, delete it and erase the entry.
//
// The map is at this+0x77C and its find is a real call -- STLport leaves it
// out of line -- with the end test comparing against the tree header the
// iterator is measured from. The mapped value sits at the node's +0x14, and a
// timer carries its display string at +0x0C.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	Bool operator<(const AsciiString &that) const;

private:
	char *m_text;
};

class DisplayString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void slot0() = 0;	virtual void slot1() = 0;
	virtual void slot2() = 0;	virtual void slot3() = 0;
	virtual void slot4() = 0;	virtual void slot5() = 0;
	virtual void slot6() = 0;	virtual void slot7() = 0;
	virtual void slot8() = 0;	virtual void slot9() = 0;
	virtual void freeDisplayString(DisplayString *string) = 0;	// slot 10, vtable+0x28
};

extern DisplayStringManager *TheDisplayStringManager;		// 0x012F12CC

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
struct NamedTimerInfo
{
	virtual ~NamedTimerInfo();				// pool object vptr, this+0x00

	char m_bfme_head[0x0C - 0x04];
	DisplayString *displayString;				// this+0x0C
};

typedef _STL::map<AsciiString, NamedTimerInfo *> NamedTimerMap;
typedef NamedTimerMap::iterator NamedTimerMapIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	void removeNamedTimer(const AsciiString &timerName);

private:
	char m_slice_pad[0x77C];				// retail this+0x00 .. +0x77B, untouched
	NamedTimerMap m_namedTimers;				// this+0x77C
};

void InGameUI::removeNamedTimer( const AsciiString& timerName )
{
	NamedTimerMapIt mapIt = m_namedTimers.find(timerName);
	if (mapIt != m_namedTimers.end())
	{
		TheDisplayStringManager->freeDisplayString( mapIt->second->displayString );
		delete mapIt->second;
		m_namedTimers.erase(mapIt);
		return;
	}
}
