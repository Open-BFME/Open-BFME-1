// ?d_00497640@@YAXXZ
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME5: 0x00495850, near-twin of the ZH-shaped
// ProcessAnimateWindowSlideFromRight::updateAnimateWindow already compiled
// (present-unmatched) in ProcessAnimateWindow.cpp -- same body, ~223 of 230
// bytes match instruction-for-instruction.  The one real BFME divergence:
// the `if (vel.x >= -1.0f) vel.x = -1.0f;` clamp compares against the
// global float at 0x0109BF3C (pinned ?BfmeShadowScale@@3MB) instead of an
// immediate -1.0f, which is what shifts the stack frame by the extra
// spilled compare result and reorders the closing stores.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"

// BFME calls timeGetTime without dllimport in this TU: its call sites go
// through the ILT thunk at 0x481E4 (e8 rel32), not the IAT (ff 15) used by
// most other TUs. Alias the symbol after the headers so cl emits e8.
extern "C" DWORD WINAPI bfme_timeGetTime( void );
#define timeGetTime bfme_timeGetTime

static const float BfmeShadowScale = -1.0f;

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z
Bool ProcessAnimateWindowSlideFromRight::updateAnimateWindow( AnimateWindow *animWin )
{

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x < endPos.x)
	{
		curPos.x = endPos.x;
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( curPos.x - endPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_slowDownRatio;
	}
	if( vel.x >= BfmeShadowScale)
		vel.x = BfmeShadowScale;
	animWin->setVel(vel);
	return FALSE;
}
