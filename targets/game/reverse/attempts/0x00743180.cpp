// ?lookAt@W3DView@@UAEXPBUCoord3D@@@Z
// partial score=0.8977 date=2026-09-29
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DView.cpp //////////////////////////////////////////////////////////////////////////////
//
// W3D implementation of the game view class.  This view allows us to have
// a "window" into the game world that can change its width, height as 
// well as camera positioning controls
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <windows.h>

// BFME added this nonvirtual notifier after the shared Zero Hour declaration;
// injecting it on this TU's first include keeps the vendored header unchanged.
#define forceUnfreezeTime(argument) notifyCameraChange(argument); void forceUnfreezeTime(argument)
#include "GameLogic/ScriptEngine.h"
#undef forceUnfreezeTime

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "Common/BuildAssistant.h"
#include "Common/GlobalData.h"
#include "Common/Module.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingSort.h"
#include "Common/PerfTimer.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"

#include "GameClient/Color.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Image.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Line2D.h"
#include "GameClient/SelectionInfo.h"
#include "GameClient/Shell.h"
#include "GameClient/TerrainVisual.h"
#include "GameClient/Water.h"

#include "GameLogic/AI.h"			///< For AI debug (yes, I'm cheating for now)
#include "GameLogic/AIPathfind.h"			///< For AI debug (yes, I'm cheating for now)
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Object.h"
#include "GameLogic/TerrainLogic.h"									///< @todo This should be TerrainVisual (client side)
#include "Common/AudioEventInfo.h"

#include "W3DDevice/Common/W3DConvert.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DView.h"
#include "D3dx8math.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"

#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Light.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Coltype.h"
#include "WW3D2/PredLod.h"
#include "WW3D2/WW3D.h"

#include "W3DDevice/GameClient/camerashakesystem.h"

#include "WinMain.h"  /** @todo Remove this, it's only here because we
													are using timeGetTime, but we can remove that
													when we have our own timer */
// BFME adds View and Display virtuals that the shared Zero Hour headers omit;
// these scoped views preserve the witnessed slots and +0x104 camera offset.
class BfmeW3DViewViewportVtable
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setWidth(Int width);
	virtual Int getWidth();
	virtual void setHeight(Int height);
	virtual Int getHeight();
};

class BfmeDisplayViewportVtable
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual UnsignedInt getWidth();
	virtual UnsignedInt getHeight();
};

struct BfmeW3DViewViewportFields
{
	void *m_vtable;
	unsigned char m_padding04[0x14];
	Int m_width;
	Int m_height;
	Int m_originX;
	Int m_originY;
	unsigned char m_padding28[0x104 - 0x28];
	CameraClass *m_3DCamera;
};

// BFME inserted view state that the shared Zero Hour header does not expose;
// keeping its witnessed offsets here prevents that ABI from leaking to other TUs.
struct BfmeCameraCoord2D
{
	Real x;
	Real y;
};

struct BfmeCameraCoord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmeCameraRegion2D
{
	BfmeCameraCoord2D lo;
	BfmeCameraCoord2D hi;
};

struct BfmeW3DViewCameraFields
{
	unsigned char m_padding0000[0x0C];
	BfmeCameraCoord3D m_pos;
	unsigned char m_padding0018[0x44 - 0x18];
	bool m_applyCameraConstraints;
	unsigned char m_padding0045[0x6C - 0x45];
	Real m_FOV;
	unsigned char m_padding0070[0x104 - 0x70];
	CameraClass *m_3DCamera;
	unsigned char m_padding0108[0x23C8 - 0x108];
	bool m_cameraHasMovedSinceRequest;
	unsigned char m_padding23C9[0x23FC - 0x23C9];
	BfmeCameraRegion2D m_cameraConstraint;
	bool m_cameraConstraintValid;

	const BfmeCameraCoord3D *getPosition() const { return &m_pos; }
	void setPosition(const BfmeCameraCoord3D *position) { m_pos = *position; }
};

// These debug-camera fields are present in BFME but absent from the shared
// Zero Hour GlobalData definition used by this translation unit.
struct BfmeGlobalDataCameraFields
{
	unsigned char m_padding0000[0xA28];
	Real m_maxCameraHeight;
	unsigned char m_padding0A2C[0xED0 - 0xA2C];
	bool m_debugCamera;
	unsigned char m_padding0ED1[3];
	Real m_debugCameraFOV;
	Real m_debugCameraAngle;
};

#define BFME_UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9(); virtual void prefix##a(); virtual void prefix##b(); \
	virtual void prefix##c(); virtual void prefix##d(); virtual void prefix##e(); virtual void prefix##f()

// BFME's terrain primary vtable places updateCenter at slot 0x21c, three
// entries after the Zero Hour declaration included above.
class BfmeTerrainCameraUpdateVtable
{
public:
	BFME_UNUSED_VIRTUALS_16(slot000_);
	BFME_UNUSED_VIRTUALS_16(slot040_);
	BFME_UNUSED_VIRTUALS_16(slot080_);
	BFME_UNUSED_VIRTUALS_16(slot0c0_);
	BFME_UNUSED_VIRTUALS_16(slot100_);
	BFME_UNUSED_VIRTUALS_16(slot140_);
	BFME_UNUSED_VIRTUALS_16(slot180_);
	BFME_UNUSED_VIRTUALS_16(slot1c0_);
	virtual void slot200();
	virtual void slot204();
	virtual void slot208();
	virtual void slot20c();
	virtual void slot210();
	virtual void slot214();
	virtual void slot218();
	virtual void updateCenter(CameraClass *camera, RefRenderObjListIterator *lights);
};

#undef BFME_UNUSED_VIRTUALS_16

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



// 30 fps
Int TheW3DFrameLengthInMsec = 1000/LOGICFRAMES_PER_SECOND; // default is 33msec/frame == 30fps. but we may change it depending on sys config.
static const Int MAX_REQUEST_CACHE_SIZE = 40;	// Any size larger than 10, or examine code below for changes. jkmcd.
static const Real DRAWABLE_OVERSCAN = 75.0f;  ///< 3D world coords of how much to overscan in the 3D screen region






//=================================================================================================
inline Real minf(Real a, Real b) { if (a < b) return a; else return b; }
inline Real maxf(Real a, Real b) { if (a > b) return a; else return b; }
__forceinline Real clampf(Real value, Real lo, Real hi)
{
	if (value < lo) return lo;
	if (value > hi) return hi;
	return value;
}

//-------------------------------------------------------------------------------------------------
// Normalizes angle to +- PI.
//-------------------------------------------------------------------------------------------------
static void normAngle(Real &angle)
{
	if (angle < -10*PI) {
		angle = 0;
	}
	if (angle > 10*PI) {
		angle = 0;
	}
	while (angle < -PI) {
		angle += 2*PI;
	}
	while (angle > PI) {
		angle -= 2*PI;
	}
}

#define TERRAIN_SAMPLE_SIZE 40.0f
static Real getHeightAroundPos(Real x, Real y)
{
	// terrain height + desired height offset == cameraOffset * actual zoom
	Real terrainHeight = TheTerrainLogic->getGroundHeight(x, y);

	// find best approximation of max terrain height we can see
	Real terrainHeightMax = terrainHeight;
	terrainHeightMax = max(terrainHeightMax, TheTerrainLogic->getGroundHeight(x+TERRAIN_SAMPLE_SIZE, y-TERRAIN_SAMPLE_SIZE));
	terrainHeightMax = max(terrainHeightMax, TheTerrainLogic->getGroundHeight(x-TERRAIN_SAMPLE_SIZE, y-TERRAIN_SAMPLE_SIZE));
	terrainHeightMax = max(terrainHeightMax, TheTerrainLogic->getGroundHeight(x+TERRAIN_SAMPLE_SIZE, y+TERRAIN_SAMPLE_SIZE));
	terrainHeightMax = max(terrainHeightMax, TheTerrainLogic->getGroundHeight(x-TERRAIN_SAMPLE_SIZE, y+TERRAIN_SAMPLE_SIZE));

	return terrainHeightMax;
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class BfmeLookAtTerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, void *normal = 0) const;
};

class BfmeLookAtSlot27
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();;
	virtual void setInt23BC(int value);
};

class Rva0045A000
{
public:
	char m_padding00[0x1c];
	bool m_ready;
	Real sample(Real x, Real y);
};

class BfmeLookAtResetFields
{
public:
	char m_padding00[0x58];
	int m_int58;
	int m_int5c;
	int m_int60;
	int m_int64;
	int m_int68;
	char m_padding6c[0x1dc - 0x6c];
	bool m_byte1dc;
	char m_padding1dd[0x204 - 0x1dd];
	bool m_byte204;
	char m_padding205[0x228 - 0x205];
	bool m_byte228;
	char m_padding229[0x27c - 0x229];
	bool m_byte27c;
	bool m_byte27d;
	char m_padding27e[0x2354 - 0x27e];
	int m_int2354;
	char m_padding2358[0x23b8 - 0x2358];
	char m_byte23b8;
	char m_padding23b9[3];
	int m_int23bc;
	char m_padding23c0[0x243c - 0x23c0];
	int m_int243c;
	int m_int2440;
	int m_int2444;
};

class BfmeLookAtGroundState
{
public:
	char m_padding00[0x23f8];
	Real m_groundLevel;
	char m_padding23fc[0x240c - 0x23fc];
	bool m_cameraConstraintValid;
};

extern void j_00046fa1(void);

class BfmeSubETH
{
public:
	Real m_x;
	Real m_y;
};

class BfmeViewETH
{
public:
	void bfmeApplyETH(BfmeSubETH *position);
};

// ?lookAt@W3DView@@ present-unmatched
void W3DView::lookAt( const Coord3D *o ) 
{
	Coord3D pos;
	pos.x = o->x;
	pos.y = o->y;
	pos.z = o->z;
	((BfmeViewETH *)this)->bfmeApplyETH((BfmeSubETH *)&pos);


// no, don't call the super-lookAt, since it will munge our coords
// as for a 2d view. just call setPosition.
//View::lookAt(&pos);

	if (o->z > PATHFIND_CELL_SIZE_F+((BfmeLookAtTerrainLogic *)TheTerrainLogic)->getGroundHeight(pos.x, pos.y)) {
		// Pos.z is not used, so if we want to look at something off the ground, 
		// we have to look at the spot on the ground such that the object intersects
		// with the look at vector in the center of the screen.  jba.
		Vector3 rayStart,rayEnd;
		LineSegClass lineseg;
		CastResultStruct result;
		Vector3 intersection(0,0,0);

		rayStart = ((BfmeW3DViewCameraFields *)this)->m_3DCamera->Get_Position();	//get camera location
		((BfmeW3DViewCameraFields *)this)->m_3DCamera->Un_Project(rayEnd,Vector2(0.0f,0.0f));	//get world space point
		rayEnd -= rayStart;	//vector camera to world space point
		rayEnd.Normalize();	//make unit vector
		rayEnd *= ((BfmeW3DViewCameraFields *)this)->m_3DCamera->Get_Depth();	//adjust length to reach far clip plane
		rayStart.Set(pos.x, pos.y, pos.z);
		rayEnd += rayStart;	//get point on far clip plane along ray from camera.
		lineseg.Set(rayStart,rayEnd);

		RayCollisionTestClass raytest(lineseg,&result);

		if( TheTerrainRenderObject->Cast_Ray(raytest) )
		{
			// get the point of intersection according to W3D
			pos.x = result.ContactPoint.X;
			pos.y = result.ContactPoint.Y;
			
		}  // end if
	}			 
	pos.z = 0;
	Coord3D *viewPos = (Coord3D *)((char *)this + 0x0c);
	setPosition(&pos);
	BfmeLookAtResetFields *reset = (BfmeLookAtResetFields *)this;
	reset->m_int2354 = 0;
	reset->m_byte1dc = false;
	reset->m_byte204 = false;
	reset->m_byte228 = false;
	reset->m_byte27d = false;
	reset->m_byte27c = false;
	reset->m_byte23b8 = 0;
	reset->m_int243c = 0;
	reset->m_int2440 = 0;
	reset->m_int2444 = 0;
	_ReadWriteBarrier();
	reset->m_int58 = 0;
	reset->m_int5c = 0;
	reset->m_int68 = 0;
	((BfmeLookAtSlot27 *)this)->setInt23BC(0);

	Real groundHeight = getHeightAroundPos(viewPos->x, ((BfmeW3DViewCameraFields *)this)->m_pos.y);
	BfmeLookAtGroundState *groundState = (BfmeLookAtGroundState *)this;
	if (*((bool *)((char *)this + 0x2464)))
	{
		typedef Real (Rva0045A000::*Sample)(Real, Real);
		union
		{
			void (*function)(void);
			Sample member;
		} thunk;
		thunk.function = j_00046fa1;
		groundHeight = (((Rva0045A000 *)((char *)this + 0x2448))->*thunk.member)(viewPos->x, ((BfmeW3DViewCameraFields *)this)->m_pos.y);
	}
	Real oldGroundLevel = groundState->m_groundLevel;
	if (groundHeight > oldGroundLevel)
	{
		groundState->m_groundLevel = groundHeight;
		groundState->m_cameraConstraintValid = false;
		setCameraTransform();
	}
	else
	{
		setCameraTransform();
	}

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
