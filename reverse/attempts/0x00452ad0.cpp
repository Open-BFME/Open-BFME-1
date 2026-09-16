// ?positionAdditionalImages@@YAXPAVMapMetaData@@PAVGameWindow@@_N@Z
// partial score=0.9 date=2026-09-15
// ?positionAdditionalImages@@YAXPAVMapMetaData@@PAVGameWindow@@_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include "GameClient/MapUtil.h"

// This is the released Zero Hour source twin.  Retail's complete boundary is
// 0x00452AD0..0x00452D62 (659 bytes): the old 656-byte dump truncates the
// final `add esp, 0x34; ret` instruction sequence.
void positionAdditionalImages(MapMetaData *mmd, GameWindow *mapWindow, Bool force)
{
	TheSupplyAndTechImageLocations.m_supplyPosList.clear();
	TheSupplyAndTechImageLocations.m_techPosList.clear();

	if (!mmd || !mapWindow || mapWindow->winIsHidden())
		return;
	static MapMetaData *prevMMD = NULL;
	if (force)
		prevMMD = NULL;
	if (mmd == prevMMD)
		return;

	ICoord2D winMapSize;
	ICoord2D winMapPos;
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);

	ICoord2D ul;
	ICoord2D lr;
	findDrawPositions(0, 0, winMapSize.x, winMapSize.y, mmd->m_extent, &ul, &lr);
	Int smallWidth = lr.x - ul.x;
	Int smallHeight = lr.y - ul.y;

	Coord3DList::iterator it = mmd->m_supplyPositions.begin();
	while (it != mmd->m_supplyPositions.end()) {
		ICoord2D markerPos;
		Real position = (it->x - mmd->m_extent.lo.x)
			/ (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = position * smallWidth - SUPPLY_TECH_SIZE / 2 + ul.x;
		position = (it->y - mmd->m_extent.lo.y)
			/ (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = (1 - position) * smallHeight
			- SUPPLY_TECH_SIZE / 2 + ul.y;
		TheSupplyAndTechImageLocations.m_supplyPosList.push_front(markerPos);
		++it;
	}

	it = mmd->m_techPositions.begin();
	while (it != mmd->m_techPositions.end()) {
		ICoord2D markerPos;
		Real position = (it->x - mmd->m_extent.lo.x)
			/ (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = position * smallWidth - SUPPLY_TECH_SIZE / 2 + ul.x;
		position = (it->y - mmd->m_extent.lo.y)
			/ (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = (1 - position) * smallHeight
			- SUPPLY_TECH_SIZE / 2 + ul.y;
		TheSupplyAndTechImageLocations.m_techPosList.push_front(markerPos);
		++it;
	}
}
