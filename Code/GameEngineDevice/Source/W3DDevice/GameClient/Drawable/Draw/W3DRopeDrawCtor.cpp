// cl: /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
#define Matrix4x4 Matrix4

#include <stdlib.h>
#include <windows.h>
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/ClientRandomValue.h"
#include "GameClient/Color.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameLogic/GameLogic.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/Module/W3DRopeDraw.h"
#include "WW3D2/Line3D.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "Common/GameState.h"

// ??0W3DRopeDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DRopeDraw::W3DRopeDraw(Thing *thing, const ModuleData *moduleData) : DrawModule(thing, moduleData)
{
	m_curLen = 0.0f;
	m_maxLen = 1.0f;
	m_width = 0.5f;
	m_color.red = 0.0f;
	m_color.green = 0.0f;
	m_color.blue = 0.0f;
	m_curSpeed = 0.0f;
	m_maxSpeed = 0.0f;
	m_accel = 0.0f;
	m_wobbleLen = m_maxLen;
	m_wobbleAmp = 0.0f;
	m_segments.clear();
	m_wobbleRate = 0.0f;
	m_curWobblePhase = 0.0f;
	m_curZOffset = 0.0f;
}
