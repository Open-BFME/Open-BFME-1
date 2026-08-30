// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define Matrix4x4 Matrix4

// Open-BFME: clean reconstruction of the retail Spiral animation update.

#include "PreRTS.h"
#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"

// ?updateAnimateWindow@ProcessAnimateWindowSpiral@@UAE_NPAVAnimateWindow@@@Z
Bool ProcessAnimateWindowSpiral::updateAnimateWindow( AnimateWindow *animWin )
{
	if (!animWin)
		return TRUE;

	if (animWin->isFinished())
		return TRUE;

	GameWindow *win = animWin->getGameWindow();
	if (!win)
		return TRUE;

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();

	curPos.x = (vel.y * cos(vel.x)) + endPos.x;
	curPos.y = (vel.y * sin(vel.x)) + endPos.y;

	vel.x = vel.x - m_deltaTheta;
	vel.y += 5;

	ICoord2D size;
	win->winGetSize(&size.x, &size.y);

	if (vel.y > m_maxR)
	{
		animWin->setFinished(TRUE);
		return TRUE;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	Coord2D storedVel = {vel.x, vel.y};
	animWin->setVel(storedVel);
	return FALSE;
}
