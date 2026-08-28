// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib

// FILE: ControlBarPrintPositions.cpp /////////////////////////////////////////
//
// PrintOffsetsFromControlBarParent, retail 0x004AAC50. No port of Zero Hour's
// ControlBarPrintPositions.cpp existed under Code/; the body is Zero Hour's
// unchanged, found by the "controlBarHidden.wnd" literal it pushes.
//
// Four interfaces are spelled TU-locally for the slots this one call site
// proves: winGetWindowFromId at 0xDC and winCreateLayout at 0x6C of
// GameWindowManager, and destroyWindows at 0x20 of WindowLayout. Zero Hour's
// deleteInstance() is the MemoryPoolObject macro; BFME reaches the scalar
// deleting destructor at slot 4 instead, which is what `delete layout' spells.
//
// getFirstWindow is inlined: retail reads the window list straight out of
// +8 of the layout.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "Common/AsciiString.h"

typedef int Int;
typedef unsigned int NameKeyType;

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class BfmeWindowLayout
{
public:
	virtual void slot00() = 0;
	virtual void deletingDestructor( unsigned int flags ) = 0;  // slot 0x04
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void destroyWindows() = 0;                          // slot 0x20

	// getFirstWindow is inlined against this member.
	char m_pad[4];
	GameWindow *m_windowList;
};

class BfmeGameWindowManager
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual BfmeWindowLayout *winCreateLayout( AsciiString filename ) = 0;   // slot 0x6C
	virtual void slot070() = 0; virtual void slot074() = 0; virtual void slot078() = 0;
	virtual void slot07C() = 0; virtual void slot080() = 0; virtual void slot084() = 0;
	virtual void slot088() = 0; virtual void slot08C() = 0; virtual void slot090() = 0;
	virtual void slot094() = 0; virtual void slot098() = 0; virtual void slot09C() = 0;
	virtual void slot0A0() = 0; virtual void slot0A4() = 0; virtual void slot0A8() = 0;
	virtual void slot0AC() = 0; virtual void slot0B0() = 0; virtual void slot0B4() = 0;
	virtual void slot0B8() = 0; virtual void slot0BC() = 0; virtual void slot0C0() = 0;
	virtual void slot0C4() = 0; virtual void slot0C8() = 0; virtual void slot0CC() = 0;
	virtual void slot0D0() = 0; virtual void slot0D4() = 0; virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *window, NameKeyType id ) = 0;  // slot 0xDC
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern BfmeGameWindowManager *TheWindowManager;

void PrintInfoRecursive( GameWindow *window, FILE *fp );

// ?PrintOffsetsFromControlBarParent@@YAXXZ
void PrintOffsetsFromControlBarParent( void )
{
	GameWindow *controlBarParent = TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ControlBarParent" ));
	if(!controlBarParent)
		return;

	BfmeWindowLayout *layout = TheWindowManager->winCreateLayout("controlBarHidden.wnd");
	if(!layout)
		return;
	FILE *fp = fopen("ControlBarEasier.txt", "w");
	if(!fp)
		return;

	PrintInfoRecursive(layout->m_windowList, fp);

	fclose(fp);
	layout->destroyWindows();
	// ZH spells this deleteInstance(); BFME reaches the scalar deleting
	// destructor at slot 4 with the deleting flag set.
	layout->deletingDestructor( 1 );
}
