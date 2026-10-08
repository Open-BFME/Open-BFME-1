// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/viewpitchoutofline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
// Retail uses ECX for this reference; expose that proven ABI as the single external provider.
void __fastcall normAngle(Real &angle)
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


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0W3DView@@ present-unmatched
W3DView::W3DView()
{
	
	m_3DCamera = NULL;
	m_2DCamera = NULL;
	m_groundLevel = 10.0;
	m_cameraOffset.z = TheGlobalData->m_cameraHeight;
	m_cameraOffset.y = -(m_cameraOffset.z / tan(TheGlobalData->m_cameraPitch * (PI / 180.0)));
	m_cameraOffset.x = -(m_cameraOffset.y * tan(TheGlobalData->m_cameraYaw * (PI / 180.0)));

	m_viewFilterMode = FM_VIEW_DEFAULT;
	m_viewFilter = FT_VIEW_DEFAULT;
	m_isWireFrameEnabled = m_nextWireFrameEnabled = FALSE;
	m_shakeOffset.x = 0.0f;
	m_shakeOffset.y = 0.0f;
	m_shakeIntensity = 0.0f;
	m_FXPitch = 1.0f;
	m_freezeTimeForCameraMovement = false;
	m_cameraHasMovedSinceRequest = true;
	m_locationRequests.clear();
	m_locationRequests.reserve(MAX_REQUEST_CACHE_SIZE + 10);	// This prevents the vector from ever re-allocing

	//Enhancements from CNC3 WST 4/15/2003. JSC Integrated 5/20/03.
	m_CameraArrivedAtWaypointOnPathFlag = false;	// Scripts for polling camera reached targets
	m_isCameraSlaved = false;						// This is for 3DSMax camera playback
	m_useRealZoomCam = false;						// true;	//WST 10/18/2002
	m_shakerAngles.X =0.0f;							// Proper camera shake generator & sources
	m_shakerAngles.Y =0.0f;
	m_shakerAngles.Z =0.0f;

}  // end W3DView

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DView@@ present-unmatched
W3DView::~W3DView()
{

	REF_PTR_RELEASE( m_2DCamera );
	REF_PTR_RELEASE( m_3DCamera );

}  // end ~W3DView

//-------------------------------------------------------------------------------------------------
/** Sets the height of the viewport, while maintaining original camera perspective. */
//-------------------------------------------------------------------------------------------------
void W3DView::setHeight(Int height)
{
	BfmeW3DViewViewportFields *fields = (BfmeW3DViewViewportFields *)this;
	BfmeW3DViewViewportVtable *view = (BfmeW3DViewViewportVtable *)this;
	fields->m_height = height;

	Vector2 vMin,vMax;
	fields->m_3DCamera->Set_Aspect_Ratio((Real)view->getWidth()/(Real)height);
	fields->m_3DCamera->Get_Viewport(vMin,vMax);
	vMax.Y=(Real)(fields->m_originY+height)/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getHeight();
	fields->m_3DCamera->Set_Viewport(vMin,vMax);
}

//-------------------------------------------------------------------------------------------------
/** Sets the width of the viewport, while maintaining original camera perspective. */
//-------------------------------------------------------------------------------------------------
void W3DView::setWidth(Int width)
{
	BfmeW3DViewViewportFields *fields = (BfmeW3DViewViewportFields *)this;
	BfmeW3DViewViewportVtable *view = (BfmeW3DViewViewportVtable *)this;
	fields->m_width = width;

	Vector2 vMin,vMax;
	fields->m_3DCamera->Set_Aspect_Ratio((Real)width/(Real)view->getHeight());
	fields->m_3DCamera->Get_Viewport(vMin,vMax);
	vMax.X=(Real)(fields->m_originX+width)/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getWidth();
	fields->m_3DCamera->Set_Viewport(vMin,vMax);
	fields->m_3DCamera->Set_View_Plane((Real)width/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getWidth()*DEG_TO_RADF(50.0f),-1);
}

//-------------------------------------------------------------------------------------------------
/** Sets location of top-left view corner on display */
//-------------------------------------------------------------------------------------------------
void W3DView::setOrigin( Int x, Int y)
{
	BfmeW3DViewViewportFields *fields = (BfmeW3DViewViewportFields *)this;
	BfmeW3DViewViewportVtable *view = (BfmeW3DViewViewportVtable *)this;
	fields->m_originX = x;
	fields->m_originY = y;

	Vector2 vMin,vMax;

	fields->m_3DCamera->Get_Viewport(vMin,vMax);
	vMin.X=(Real)x/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getWidth();
	vMin.Y=(Real)y/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getHeight();
	fields->m_3DCamera->Set_Viewport(vMin,vMax);

	view->setWidth(fields->m_width);
	view->setHeight(fields->m_height);
}

//-------------------------------------------------------------------------------------------------
/** @todo This is inefficient. We should construct the matrix directly using vectors. */
//-------------------------------------------------------------------------------------------------
#define MIN_CAPPED_ZOOM (0.5f) //WST 10.19.2002. JSC integrated 5/20/03.
// Retail W3DView::buildCameraTransform (0x00741D30) is implemented in W3DViewBuildCameraTransformBfme.cpp.

// Retail W3DView::calcCameraConstraints (0x00740CF0) is implemented in W3DViewCalcCameraConstraintsBfme.cpp.

//-------------------------------------------------------------------------------------------------
/** Returns a world-space ray originating at a given screen pixel position
	and ending at the far clip plane for current camera.  Screen coordinates
	assumed in absolute values relative to full display resolution.*/
//-------------------------------------------------------------------------------------------------
class BFMERetailW3DViewInterface
{
public:
	virtual void unused00(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused0C(void) = 0;
	virtual void unused10(void) = 0;
	virtual void unused14(void) = 0;
	virtual void unused18(void) = 0;
	virtual void unused1C(void) = 0;
	virtual void unused20(void) = 0;
	virtual void unused24(void) = 0;
	virtual void unused28(void) = 0;
	virtual void unused2C(void) = 0;
	virtual void unused30(void) = 0;
	virtual void unused34(void) = 0;
	virtual void unused38(void) = 0;
	virtual Int getWidth(void) = 0;
	virtual void unused40(void) = 0;
	virtual Int getHeight(void) = 0;
};

void W3DView::getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd)
{
	Real logX,logY;

	//W3D Screen coordinates are -1 to 1, so we need to do some conversion:
	PixelScreenToW3DLogicalScreen(screen->x - m_originX,screen->y - m_originY, &logX, &logY,
		reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getWidth(),
		reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getHeight());

	*rayStart = (*reinterpret_cast<CameraClass **>(reinterpret_cast<unsigned char *>(this) + 0x104))->Get_Position();	//get camera location
	(*reinterpret_cast<CameraClass **>(reinterpret_cast<unsigned char *>(this) + 0x104))->Un_Project(*rayEnd,Vector2(logX,logY));	//get world space point
	*rayEnd -= *rayStart;	//vector camera to world space point
	rayEnd->Normalize();	//make unit vector
	*rayEnd *= (*reinterpret_cast<CameraClass **>(reinterpret_cast<unsigned char *>(this) + 0x104))->Get_Depth();	//adjust length to reach far clip plane
	*rayEnd += *rayStart;	//get point on far clip plane along ray from camera.
}

//-------------------------------------------------------------------------------------------------
/** set the transform matrix of m_3DCamera, based on m_pos & m_angle */
//-------------------------------------------------------------------------------------------------
void W3DView::setCameraTransform( void )
{
	BfmeW3DViewCameraFields *fields = (BfmeW3DViewCameraFields *)this;
	fields->m_cameraHasMovedSinceRequest = true;
	Matrix3D cameraTransform( true );

	fields->m_3DCamera->Set_Clip_Planes(
		10.0f, ((BfmeGlobalDataCameraFields *)TheWritableGlobalData)->m_maxCameraHeight * 1800.0f);

	if (!fields->m_cameraConstraintValid)
	{
		buildCameraTransform( &cameraTransform );
		fields->m_3DCamera->Set_Transform( cameraTransform );
		calcCameraConstraints();
	}

	if (fields->m_cameraConstraintValid && fields->m_applyCameraConstraints)
	{
		BfmeCameraCoord3D pos;
		pos.x = fields->getPosition()->x;
		pos.y = fields->getPosition()->y;
		pos.z = fields->getPosition()->z;
		pos.x = clampf( pos.x, fields->m_cameraConstraint.lo.x,
			fields->m_cameraConstraint.hi.x );
		pos.y = clampf( pos.y, fields->m_cameraConstraint.lo.y,
			fields->m_cameraConstraint.hi.y );
		fields->setPosition(&pos);
	}

	if (((BfmeGlobalDataCameraFields *)TheWritableGlobalData)->m_debugCamera)
		fields->m_3DCamera->Set_View_Plane(
			((BfmeGlobalDataCameraFields *)TheWritableGlobalData)->m_debugCameraFOV, -1.0f);
	else
		fields->m_3DCamera->Set_View_Plane(fields->m_FOV, -1.0f);

	buildCameraTransform( &cameraTransform );
	if (((BfmeGlobalDataCameraFields *)TheWritableGlobalData)->m_debugCamera)
		cameraTransform.Rotate_Y(
			((BfmeGlobalDataCameraFields *)TheWritableGlobalData)->m_debugCameraAngle);
	fields->m_3DCamera->Set_Transform( cameraTransform );

	if (TheTerrainRenderObject)
	{
		RefRenderObjListIterator *iterator = W3DDisplay::m_3DScene->createLightsIterator();
		((BfmeTerrainCameraUpdateVtable *)TheTerrainRenderObject)->updateCenter(
			fields->m_3DCamera, iterator);
		if (iterator)
			W3DDisplay::m_3DScene->destroyLightsIterator(iterator);
	}

	TheScriptEngine->notifyCameraChange();
}

// Retail W3DView::init (0x00742700) is implemented in W3DView_initBfme.cpp.

//-------------------------------------------------------------------------------------------------
// ?get3DCameraPosition@W3DView@@ present-unmatched
const Coord3D& W3DView::get3DCameraPosition() const
{
	Vector3 camera = m_3DCamera->Get_Position();
	static Coord3D pos;
	pos.set( camera.X, camera.Y, camera.Z );
	return pos;
}

// Retail W3DView::reset (0x0073AC90) is implemented in W3DViewResetBfme.cpp.


// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static void drawTerrainNormal( Drawable *draw, void *userData )
{
	UnsignedInt color = GameMakeColor( 255, 255, 0, 255 );
  if (TheTerrainLogic)
  {
    Coord3D pos = *draw->getPosition();
    Coord3D normal;
    pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, &normal);
    const Real NORMLEN = 20;
    normal.x = pos.x + normal.x * NORMLEN;
    normal.y = pos.y + normal.y * NORMLEN;
    normal.z = pos.z + normal.z * NORMLEN;
    ICoord2D start, end;
		TheTacticalView->worldToScreen(&pos, &start);
		TheTacticalView->worldToScreen(&normal, &end);
		TheDisplay->drawLine(start.x, start.y, end.x, end.y, 1.0f, color);
  }
}

#if defined(_DEBUG) || defined(_INTERNAL)
// ------------------------------------------------------------------------------------------------
// Draw a crude circle. Appears on top of any world geometry
// ------------------------------------------------------------------------------------------------
void drawDebugCircle( const Coord3D & center, Real radius, Real width, Color color )
{
  const Real inc = PI/4.0f;
  Real angle = 0.0f;
  Coord3D pnt, lastPnt;
  ICoord2D start, end;
  Bool endValid, startValid;

  lastPnt.x = center.x + radius * (Real)cos(angle);
  lastPnt.y = center.y + radius * (Real)sin(angle);
  lastPnt.z = center.z;
  endValid = ( TheTacticalView->worldToScreenTriReturn( &lastPnt, &end ) != View::WTS_INVALID );
  
  for( angle = inc; angle <= 2.0f * PI; angle += inc )
  {
    pnt.x = center.x + radius * (Real)cos(angle);
    pnt.y = center.y + radius * (Real)sin(angle);
    pnt.z = center.z;
    startValid = ( TheTacticalView->worldToScreenTriReturn( &pnt, &start ) != View::WTS_INVALID );
    
    if ( startValid && endValid ) 
      TheDisplay->drawLine( start.x, start.y, end.x, end.y, width, color );
    
    lastPnt = pnt;
    end = start;
    endValid = startValid;
  }
}

void drawDrawableExtents( Drawable *draw, void *userData );  // FORWARD DECLARATION
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
static void drawContainedDrawable( Object *obj, void *userData )
{
	Drawable *draw = obj->getDrawable();

	if( draw )
		drawDrawableExtents( draw, userData );

}  // end drawContainedDrawable

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static void drawDrawableExtents( Drawable *draw, void *userData )
{
	UnsignedInt color = GameMakeColor( 0, 255, 0, 255 );

	switch( draw->getDrawableGeometryInfo().getGeomType() )
	{

		//---------------------------------------------------------------------------------------------
		case GEOMETRY_BOX:
		{
			Real angle = draw->getOrientation();
			Real c = (Real)cos(angle);
			Real s = (Real)sin(angle);
			Real exc = draw->getDrawableGeometryInfo().getMajorRadius()*c;
			Real eyc = draw->getDrawableGeometryInfo().getMinorRadius()*c;
			Real exs = draw->getDrawableGeometryInfo().getMajorRadius()*s;
			Real eys = draw->getDrawableGeometryInfo().getMinorRadius()*s;
			Coord3D pts[4];
			pts[0].x = draw->getPosition()->x - exc - eys;
			pts[0].y = draw->getPosition()->y + eyc - exs;
			pts[0].z = 0;
			pts[1].x = draw->getPosition()->x + exc - eys;
			pts[1].y = draw->getPosition()->y + eyc + exs;
			pts[1].z = 0;
			pts[2].x = draw->getPosition()->x + exc + eys;
			pts[2].y = draw->getPosition()->y - eyc + exs;
			pts[2].z = 0;
			pts[3].x = draw->getPosition()->x - exc + eys;
			pts[3].y = draw->getPosition()->y - eyc - exs;
			pts[3].z = 0;
			Real z = draw->getPosition()->z;
			for( int i = 0; i < 2; i++ )
			{

				for (int corner = 0; corner < 4; corner++)
				{
					ICoord2D start, end;
					pts[corner].z = z;
					pts[(corner+1)&3].z = z;
					TheTacticalView->worldToScreen(&pts[corner], &start);
					TheTacticalView->worldToScreen(&pts[(corner+1)&3], &end);
					TheDisplay->drawLine(start.x, start.y, end.x, end.y, 1.0f, color);
				}

				z += draw->getDrawableGeometryInfo().getMaxHeightAbovePosition();

			}  // end for i

			break;

		}  // end case box

		//---------------------------------------------------------------------------------------------
		case GEOMETRY_SPHERE:	// not quite right, but close enough
		case GEOMETRY_CYLINDER:
		{ 
      Coord3D center = *draw->getPosition();
      const Real radius = draw->getDrawableGeometryInfo().getMajorRadius();

			// draw cylinder
			for( int i=0; i<2; i++ )
			{
        drawDebugCircle( center, radius, 1.0f, color );

        // next time 'round, draw the top of the cylinder
        center.z += draw->getDrawableGeometryInfo().getMaxHeightAbovePosition();
			}	// end for i

			// draw centerline
      ICoord2D start, end;
      center = *draw->getPosition();
      TheTacticalView->worldToScreen( &center, &start );
      center.z += draw->getDrawableGeometryInfo().getMaxHeightAbovePosition();
      TheTacticalView->worldToScreen( &center, &end );
			TheDisplay->drawLine( start.x, start.y, end.x, end.y, 1.0f, color );

			break;

		}	// case CYLINDER

	} // end switch

	// draw any extents for things that are contained by this
	Object *obj = draw->getObject();
	if( obj )
	{
		ContainModuleInterface *contain = obj->getContain();

		if( contain )
			contain->iterateContained( drawContainedDrawable, userData, FALSE );

	}  // end if

}  // end drawDrawableExtents


void drawAudioLocations( Drawable *draw, void *userData );
// ------------------------------------------------------------------------------------------------
// Helper for drawAudioLocations
// ------------------------------------------------------------------------------------------------
static void drawContainedAudioLocations( Object *obj, void *userData )
{
  Drawable *draw = obj->getDrawable();
  
  if( draw )
    drawAudioLocations( draw, userData );
  
}  // end drawContainedAudio


//-------------------------------------------------------------------------------------------------
// Draw the location of audio objects in the world
//-------------------------------------------------------------------------------------------------
static void drawAudioLocations( Drawable *draw, void *userData )
{
  // draw audio for things that are contained by this
  Object *obj = draw->getObject();
  if( obj )
  {
    ContainModuleInterface *contain = obj->getContain();
    
    if( contain )
      contain->iterateContained( drawContainedAudioLocations, userData, FALSE );
    
  }  // end if

  const ThingTemplate * thingTemplate = draw->getTemplate();

  if ( thingTemplate == NULL || thingTemplate->getEditorSorting() != ES_AUDIO )
  {
    return; // All done
  }

  // Copied in hideously inappropriate code copying ways from DrawObject.cpp
  // Should definately be a global, probably read in from an INI file <gasp>
  static const Int poleHeight = 20;
  static const Int flagHeight = 10;
  static const Int flagWidth = 10;
  const Color color = GameMakeColor(0x25, 0x25, 0xEF, 0xFF);

  // Draw flag for audio-only objects:
  //  *
  //  * *
  //  *   *
  //  *     *
  //  *   *
  //  * *
  //  *
  //  *
  //  *
  //  *
  //  *

  Coord3D worldPoint;
  ICoord2D start, end;

  worldPoint = *draw->getPosition();
  TheTacticalView->worldToScreen( &worldPoint, &start );
  worldPoint.z += poleHeight;
  TheTacticalView->worldToScreen( &worldPoint, &end );
  TheDisplay->drawLine( start.x, start.y, end.x, end.y, 1.0f, color );
  
  worldPoint.z -= flagHeight / 2;
  worldPoint.x += flagWidth;
  TheTacticalView->worldToScreen( &worldPoint, &start );
  TheDisplay->drawLine( start.x, start.y, end.x, end.y, 1.0f, color );

  worldPoint.z -= flagHeight / 2;
  worldPoint.x -= flagWidth;
  TheTacticalView->worldToScreen( &worldPoint, &end );
  TheDisplay->drawLine( start.x, start.y, end.x, end.y, 1.0f, color );
}

//-------------------------------------------------------------------------------------------------
// Draw the radii of sounds attached to any type of object. 
//-------------------------------------------------------------------------------------------------
static void drawAudioRadii( const Drawable * drawable )
{
  
  // Draw radii, if sound is playing
  const AudioEventRTS * ambientSound = drawable->getAmbientSound();
  
  if ( ambientSound && ambientSound->isCurrentlyPlaying() )
  {
    const AudioEventInfo * ambientInfo = ambientSound->getAudioEventInfo();
    
    if ( ambientInfo == NULL )
    {
      // I don't think that's right...
      OutputDebugString( ("Playing sound has NULL AudioEventInfo?\n" ) );
      
      if ( TheAudio != NULL )
      {
        ambientInfo = TheAudio->findAudioEventInfo( ambientSound->getEventName() );
      }
    }
    
    if ( ambientInfo != NULL )
    {
      // Colors match those used in WorldBuilder
      drawDebugCircle( *drawable->getPosition(), ambientInfo->m_minDistance, 1.0f, GameMakeColor(0x00, 0x00, 0xFF, 0xFF) );
      drawDebugCircle( *drawable->getPosition(), ambientInfo->m_maxDistance, 1.0f, GameMakeColor(0xFF, 0x00, 0xFF, 0xFF) );
    }
  }
}

#endif

//-------------------------------------------------------------------------------------------------
/** An opportunity to draw something after all drawables have been drawn once */
//-------------------------------------------------------------------------------------------------
static void drawablePostDraw( Drawable *draw, void *userData )
{
	Real FXPitch = TheTacticalView->getFXPitch();
	if (draw->isDrawableEffectivelyHidden() || FXPitch < 0.0f)
		return;

	Object* obj = draw->getObject();
	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
#if defined(_DEBUG) || defined(_INTERNAL)
	ObjectShroudStatus ss = (!obj || !TheGlobalData->m_shroudOn) ? OBJECTSHROUD_CLEAR : obj->getShroudedStatus(localPlayerIndex);
#else
	ObjectShroudStatus ss = (!obj) ? OBJECTSHROUD_CLEAR : obj->getShroudedStatus(localPlayerIndex);
#endif
	if (ss > OBJECTSHROUD_PARTIAL_CLEAR)
		return;

	// draw the any "icon" UI for a drawable (health bars, veterency, etc);
	
	//*****
	//@TODO: Create a way to reject this call easily -- like objects that have no compatible modules.
	//*****
	//if( draw->getStatusBits() )
	//{
			draw->drawIconUI();
	//}

#if defined(_DEBUG) || defined(_INTERNAL)
	// debug collision extents
	if( TheGlobalData->m_showCollisionExtents )
	  drawDrawableExtents( draw, userData );

  if ( TheGlobalData->m_showAudioLocations )
    drawAudioLocations( draw, userData );
#endif

	// debug terrain normals at object positions
	if( TheGlobalData->m_showTerrainNormals )
	  drawTerrainNormal( draw, userData );

	TheGameClient->incrementRenderedObjectCount();

}  // end drawablePostDraw

//-------------------------------------------------------------------------------------------------
// Display AI debug visuals
//-------------------------------------------------------------------------------------------------
static void renderAIDebug( void )
{
}

// Retail W3DView::updateCameraMovements (0x00744530) is implemented in W3DViewUpdateCameraMovementsBfme.cpp.


/** This function performs all actions which affect the camera transform or 3D objects
	rendered in this frame.

// ?draw@W3DView@@ present-unmatched
   MW: I moved this code out out W3DView::draw() so that we can get final camera and object
   positions before any rendering begins.  This was necessary so that reflection textures
   (which update before the main rendering loop) could get a correct version of the scene.
   Without this change, the reflections were always 1 frame behind the non-reflected view.
*/
// ?updateView@W3DView@@ present-unmatched
void W3DView::updateView(void)
{
	UPDATE();
}

// Retail W3DView::getAxisAlignedViewRegion (0x0073AFA0) is implemented in W3DViewGetAxisAlignedViewRegion.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?setFadeParameters@W3DView@@ present-unmatched
void W3DView::setFadeParameters(Int fadeFrames, Int direction)
{
	ScreenBWFilter::setFadeParameters(fadeFrames, direction);
	ScreenCrossFadeFilter::setFadeParameters(fadeFrames,direction);
}

void W3DView::set3DWireFrameMode(Bool enable)
{
	m_nextWireFrameEnabled = enable;
}

//-------------------------------------------------------------------------------------------------
/** Sets the view filter mode. */
//-------------------------------------------------------------------------------------------------
void W3DView::setViewFilterPos(const Coord3D *pos)
{
	ScreenMotionBlurFilter::setZoomToPos(pos);
}
//-------------------------------------------------------------------------------------------------
/** Sets the view filter mode. */
//-------------------------------------------------------------------------------------------------
// ?setViewFilterMode@W3DView@@ present-unmatched
Bool W3DView::setViewFilterMode(enum FilterModes filterMode)
{
	FilterModes oldMode = m_viewFilterMode;	//save previous mode in case setup fails.

	m_viewFilterMode = filterMode;
	if (m_viewFilterMode != FM_NULL_MODE && 
		m_viewFilter != FT_NULL_FILTER) {
		if (!W3DShaderManager::filterSetup(m_viewFilter, m_viewFilterMode))
		{	//setup failed so restore previous mode.
			m_viewFilterMode = oldMode;
			return FALSE;
		}
	}
	return TRUE;
}
//-------------------------------------------------------------------------------------------------
/** Sets the view filter. */
//-------------------------------------------------------------------------------------------------
// ?setViewFilter@W3DView@@ present-unmatched
Bool W3DView::setViewFilter(enum FilterTypes filter)
{
	FilterTypes oldFilter = m_viewFilter;	//save previous filter in case setup fails.

	m_viewFilter = filter;
	if (m_viewFilterMode != FM_NULL_MODE && 
		m_viewFilter != FT_NULL_FILTER) {
		if (!W3DShaderManager::filterSetup(m_viewFilter, m_viewFilterMode))
		{	//setup failed so restore previous mode.
			m_viewFilter = oldFilter;
			return FALSE;
		};
	}
	return TRUE;
}

//-------------------------------------------------------------------------------------------------
/** Calculates how many pixels we scrolled since last frame for motion blur calculations. */
//-------------------------------------------------------------------------------------------------
// ?calcDeltaScroll@W3DView@@AAEXAAUCoord2D@@@Z
// Exact retail helper emitted by W3DViewCalcDeltaScrollThunk.cpp.


//-------------------------------------------------------------------------------------------------
/** Draw member for the W3D window, this will literally draw the window 
  * for this view */
//-------------------------------------------------------------------------------------------------
// ?drawView@W3DView@@ present-unmatched
void W3DView::drawView( void )
{
	DRAW();
}

//DECLARE_PERF_TIMER(W3DView_drawView)
// ?draw@W3DView@@ present-unmatched
void W3DView::draw( void )
{
	//USE_PERF_TIMER(W3DView_drawView)
	Bool skipRender = false;
	Bool doExtraRender = false;
	CustomScenePassModes customScenePassMode  = SCENE_PASS_DEFAULT;
	Bool preRenderResult = false;

	if (m_viewFilterMode && 
			m_viewFilter > FT_NULL_FILTER && 
			m_viewFilter < FT_MAX)
	{	
		// Most likely will redirect rendering to a texture.
		preRenderResult=W3DShaderManager::filterPreRender(m_viewFilter, skipRender, customScenePassMode);
		if (!skipRender && getCameraLock()) 
		{
			Object* cameraLockObj = TheGameLogic->findObjectByID(getCameraLock());
			if (cameraLockObj) 
			{
				Drawable *drawable = cameraLockObj->getDrawable();
				drawable->setDrawableHidden(true);
			}
		}
	}

	if (!skipRender) 
	{
		// Render 3D scene from our camera
		W3DDisplay::m_3DScene->setCustomPassMode(customScenePassMode);
		if (m_isWireFrameEnabled)
			W3DDisplay::m_3DScene->Set_Extra_Pass_Polygon_Mode(SceneClass::EXTRA_PASS_CLEAR_LINE);
		W3DDisplay::m_3DScene->doRender( m_3DCamera );
		W3DDisplay::m_3DScene->Set_Extra_Pass_Polygon_Mode(SceneClass::EXTRA_PASS_DISABLE);
		m_isWireFrameEnabled = m_nextWireFrameEnabled;
	}

	if (m_viewFilterMode && 
			m_viewFilter > FT_NULL_FILTER && 
			m_viewFilter < FT_MAX)
	{	
		Coord2D deltaScroll;
		calcDeltaScroll(deltaScroll);
		Bool continueTheEffect = false;
		if (preRenderResult)	//if prerender passed, do the post render.
			continueTheEffect = W3DShaderManager::filterPostRender(m_viewFilter, m_viewFilterMode, deltaScroll,doExtraRender);
		if (!skipRender && getCameraLock()) 
		{
			Object* cameraLockObj = TheGameLogic->findObjectByID(getCameraLock());
			if (cameraLockObj) 
			{
				Drawable *drawable = cameraLockObj->getDrawable();
				drawable->setDrawableHidden(false);
				RenderInfoClass rinfo(*m_3DCamera);
				// Apply the camera and viewport (including depth range)
				m_3DCamera->Apply();
				TheDX8MeshRenderer.Set_Camera(&rinfo.Camera);
				W3DDisplay::m_3DScene->renderSpecificDrawables(rinfo, 1, &drawable);
				WW3D::Flush(rinfo);
			}
		}
		if (!continueTheEffect) 
		{
			// shut it down.
			m_viewFilter = FT_VIEW_DEFAULT;
			m_viewFilterMode = FM_VIEW_DEFAULT;
		}
	}

	//Some effects require that we render a modified version of the scene into a texture but also require
	//an unaltered version in the framebuffer.  So we re-render again into framebuffer after texture rendering
	//was turned off by filterPostRender().
	if (doExtraRender)
	{
		//Reset to normal scene rendering.
		//The pass that rendered into a texture may have left the z-buffer in a weird state
		//so clear it before rendering normal scene.
		///@todo: Don't clear z-buffer unless shader uses z-bias or anything else that would cause <= z to fail on normal render.
// ?Clear@DX8Wrapper@@ present-unmatched
		DX8Wrapper::Clear(false, true, Vector3(0.0f,0.0f,0.0f), TheWaterTransparency->m_minWaterOpacity);	// Clear z but not color
		W3DDisplay::m_3DScene->setCustomPassMode(SCENE_PASS_DEFAULT);
		W3DDisplay::m_3DScene->doRender( m_3DCamera );
		Coord2D deltaScroll;
		W3DShaderManager::filterPostRender(m_viewFilter, m_viewFilterMode, deltaScroll, doExtraRender);
	}

	if( TheGlobalData->m_debugAI )
	{
		if (TheAI->pathfinder()->getDebugPath())
		{
			// setup screen clipping region
			IRegion2D clipRegion;
			clipRegion.lo.x = 0;
			clipRegion.lo.y = 0;
			clipRegion.hi.x = getWidth();
			clipRegion.hi.y = getHeight();

			UnsignedInt color = 0xFFFFFF00;  //0xAARRGGBB
			ICoord2D start, end;
			PathNode *prevNode = TheAI->pathfinder()->getDebugPath()->getFirstNode();

			if (worldToScreen( prevNode->getPosition(), &start )) {
				TheDisplay->drawLine( start.x-3, start.y-3, start.x+3, start.y-3, 1.0f, color );
				TheDisplay->drawLine( start.x+3, start.y-3, start.x+3, start.y+3, 1.0f, color );
				TheDisplay->drawLine( start.x+3, start.y+3, start.x-3, start.y+3, 1.0f, color );
				TheDisplay->drawLine( start.x-3, start.y+3, start.x-3, start.y-3, 1.0f, color );
			}
			for( PathNode *node = prevNode->getNext(); node; node = node->getNext() )
			{
				Int k;
				Coord3D s, e;
				Coord3D delta;
				s = *node->getPosition();
				e = *prevNode->getPosition();
				delta.x = e.x-s.x;
				delta.y = e.y-s.y;
				delta.z = e.z-s.z;
				for (k = 0; k<10; k++) {
					Real factor1 = (k)/10.0;
					Real factor2 = (k+1)/10.0;
					s = *node->getPosition();
					e = *node->getPosition();
					s.x += delta.x*factor1;
					s.y += delta.y*factor1;
					s.z += delta.z*factor1;
					e.x += delta.x*factor2;
					e.y += delta.y*factor2;
					e.z += delta.z*factor2;
					Bool onScreen1 = worldToScreen( &e, &end );
					Bool onScreen2 = worldToScreen( &s, &start );
					if (!onScreen1 && !onScreen2) {
						continue; // neither point visible.
					}
					ICoord2D clipStart, clipEnd;

					if( ClipLine2D( &start, &end, &clipStart, &clipEnd, &clipRegion ) ) {
						TheDisplay->drawLine( clipStart.x, clipStart.y, clipEnd.x, clipEnd.y, 1.0f, color );
					}
				}
				prevNode = node;
				if (node->getNext()) {
					if (worldToScreen( node->getPosition(), &start )) {
 						TheDisplay->drawLine( start.x-4, start.y, start.x+3, start.y, 1.0f, color );
					}
				}
			}
			if (prevNode && worldToScreen( prevNode->getPosition(), &start )) {
 				TheDisplay->drawLine( start.x-4, start.y, start.x+3, start.y, 1.0f, color );
				TheDisplay->drawLine( start.x, start.y-4, start.x, start.y+3, 1.0f, color );
			}
			color = 0xFFFF0000;  //0xAARRGGBB
			if (worldToScreen( TheAI->pathfinder()->getDebugPathPosition(), &start )) {
				TheDisplay->drawLine( start.x-3, start.y, start.x+3, start.y, 1.0f, color );
				TheDisplay->drawLine( start.x, start.y-3, start.x, start.y+3, 1.0f, color );
			}
		}

	}  // end if, show debug AI

#if defined(_DEBUG) || defined(_INTERNAL)
	if( TheGlobalData->m_debugCamera )
	{
		UnsignedInt c = 0xaaffffff;
		Coord3D worldPos = *getPosition();
		worldPos.z = TheTerrainLogic->getGroundHeight(worldPos.x, worldPos.y);

		Coord3D p1, p2;
		ICoord2D s1, s2;
		p1 = worldPos;
		p1.x += TERRAIN_SAMPLE_SIZE;
		p1.y += TERRAIN_SAMPLE_SIZE;
		p1.z = TheTerrainLogic->getGroundHeight(p1.x, p1.y);
		p2 = worldPos;
		p2.x += TERRAIN_SAMPLE_SIZE;
		p2.y -= TERRAIN_SAMPLE_SIZE;
		p2.z = TheTerrainLogic->getGroundHeight(p2.x, p2.y);
		worldToScreen( &p1, &s1 );
		worldToScreen( &p2, &s2 );
		TheDisplay->drawLine(s1.x, s1.y, s2.x, s2.y, 1.0f, c);

		p1 = worldPos;
		p1.x += TERRAIN_SAMPLE_SIZE;
		p1.y -= TERRAIN_SAMPLE_SIZE;
		p1.z = TheTerrainLogic->getGroundHeight(p1.x, p1.y);
		p2 = worldPos;
		p2.x -= TERRAIN_SAMPLE_SIZE;
		p2.y -= TERRAIN_SAMPLE_SIZE;
		p2.z = TheTerrainLogic->getGroundHeight(p2.x, p2.y);
		worldToScreen( &p1, &s1 );
		worldToScreen( &p2, &s2 );
		TheDisplay->drawLine(s1.x, s1.y, s2.x, s2.y, 1.0f, c);

		p1 = worldPos;
		p1.x -= TERRAIN_SAMPLE_SIZE;
		p1.y -= TERRAIN_SAMPLE_SIZE;
		p1.z = TheTerrainLogic->getGroundHeight(p1.x, p1.y);
		p2 = worldPos;
		p2.x -= TERRAIN_SAMPLE_SIZE;
		p2.y += TERRAIN_SAMPLE_SIZE;
		p2.z = TheTerrainLogic->getGroundHeight(p2.x, p2.y);
		worldToScreen( &p1, &s1 );
		worldToScreen( &p2, &s2 );
		TheDisplay->drawLine(s1.x, s1.y, s2.x, s2.y, 1.0f, c);

		p1 = worldPos;
		p1.x -= TERRAIN_SAMPLE_SIZE;
		p1.y += TERRAIN_SAMPLE_SIZE;
		p1.z = TheTerrainLogic->getGroundHeight(p1.x, p1.y);
		p2 = worldPos;
		p2.x += TERRAIN_SAMPLE_SIZE;
		p2.y += TERRAIN_SAMPLE_SIZE;
		p2.z = TheTerrainLogic->getGroundHeight(p2.x, p2.y);
		worldToScreen( &p1, &s1 );
		worldToScreen( &p2, &s2 );
		TheDisplay->drawLine(s1.x, s1.y, s2.x, s2.y, 1.0f, c);

	}

  if ( TheGlobalData->m_showAudioLocations )
  {
    // Draw audio radii for ALL drawables, not just those on screen
    const Drawable * drawable = TheGameClient->getDrawableList();

    while ( drawable != NULL )
    {
      drawAudioRadii( drawable );
      drawable = drawable->getNextDrawable();
    }
  }
#endif // DEBUG or INTERNAL

	Region3D axisAlignedRegion;
	getAxisAlignedViewRegion(axisAlignedRegion);

	//
	// there are several things we might want to do as a post pass on the objects after
	// they are all drawn
	/// @todo we might want to consider wiping this iterate out if there is nothing to post draw
	//
	TheGameClient->resetRenderedObjectCount();
	TheGameClient->iterateDrawablesInRegion( &axisAlignedRegion, drawablePostDraw, this );

	TheGameClient->flushTextBearingDrawables();

	// Render 2D scene
	W3DDisplay::m_2DScene->doRender( m_2DCamera );
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?setCameraLock@W3DView@@ present-unmatched
void W3DView::setCameraLock(ObjectID id)
{		 
	// If we're disabling camera movements, don't lock onto the object.
	if (TheGlobalData->m_disableCameraMovement && id!=INVALID_ID) {
		return;
	}
	View::setCameraLock(id);
	m_doingScriptedCameraLock = FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?setSnapMode@W3DView@@ present-unmatched
void W3DView::setSnapMode( CameraLockType lockType, Real lockDist )
{
	View::setSnapMode(lockType, lockDist);
	m_doingScriptedCameraLock = TRUE;
}

//-------------------------------------------------------------------------------------------------
/** Scroll the view by the given delta in SCREEN COORDINATES, this interface 
	* assumes we will be scrolling along the X,Y plane */
//-------------------------------------------------------------------------------------------------
// ?scrollBy@W3DView@@ present-unmatched
void W3DView::scrollBy( Coord2D *delta )
{
	// if we haven't moved, ignore
	if( delta && (delta->x != 0 || delta->y != 0) )
	{
		const Real SCROLL_RESOLUTION = 250.0f;

		Vector3 world, worldStart, worldEnd;
		Vector2 screen, start, end;

		m_scrollAmount = *delta;

		screen.X = delta->x;
		screen.Y = delta->y;
													  
		start.X = getWidth();
		start.Y = getHeight();
		Real aspect = getWidth()/getHeight();
		end.X = start.X + delta->x * SCROLL_RESOLUTION;
		end.Y = start.Y + delta->y * SCROLL_RESOLUTION*aspect;

		m_3DCamera->Device_To_World_Space( start, &worldStart );
		m_3DCamera->Device_To_World_Space( end, &worldEnd );

		world.X = worldEnd.X - worldStart.X;
		world.Y = worldEnd.Y - worldStart.Y;
		world.Z = worldEnd.Z - worldStart.Z;

		// scroll by delta
		Coord3D pos = *getPosition();
		pos.x += world.X;
		pos.y += world.Y;
		//DEBUG_LOG(("Delta %.2f, %.2f\n", world.X, world.Z));
		// no change to z
		setPosition(&pos);

		//m_cameraConstraintValid = false;	// pos change does NOT invalidate cam constraints

		m_doingRotateCamera = false;
		// set new camera position
		setCameraTransform();

	}  // end if

}  // end scrollBy

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?forceRedraw@W3DView@@ present-unmatched
void W3DView::forceRedraw()
{

	// set the camera
	setCameraTransform();
}

//-------------------------------------------------------------------------------------------------
/** Rotate the view around the up axis to the given angle. */
//-------------------------------------------------------------------------------------------------
// ?setAngle@W3DView@@ present-unmatched
void W3DView::setAngle( Real angle )
{
	// Normalize to +-PI.
	normAngle(angle);
	// call our base class, we are adding functionality
	View::setAngle( angle );


	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;

	m_doingRotateCamera = false;
	m_doingPitchCamera = false;
	m_doingZoomCamera = false;
	m_doingScriptedCameraLock = false;
	// set the camera
	setCameraTransform();
}

//-------------------------------------------------------------------------------------------------
/** Rotate the view around the horizontal (X) axis to the given angle. */
//-------------------------------------------------------------------------------------------------
void W3DView::setPitch( Real angle )
{
	View::setPitch( angle );

	unsigned char *view_bytes = reinterpret_cast<unsigned char *>(this);
	view_bytes[0x1DC] = 0;
	view_bytes[0x204] = 0;
	view_bytes[0x27C] = 0;
	view_bytes[0x228] = 0;
	view_bytes[0x27D] = 0;
	setCameraTransform();
}

//-------------------------------------------------------------------------------------------------
/** Set the view angle & pitch back to default */
//-------------------------------------------------------------------------------------------------
// ?setAngleAndPitchToDefault@W3DView@@ present-unmatched
void W3DView::setAngleAndPitchToDefault( void )
{ 
	// call our base class, we are adding functionality
	View::setAngleAndPitchToDefault();

	this->m_FXPitch = 1.0;

	// set the camera
	setCameraTransform();
}

// Retail W3DView::setDefaultView (0x0073F9C0) is implemented in W3DViewSetDefaultViewBfme.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?setHeightAboveGround@W3DView@@ present-unmatched
void W3DView::setHeightAboveGround(Real z)
{
	m_heightAboveGround = z;

  // if our zoom is limited, we will stay within a predefined distance from the terrain
	if( m_zoomLimited )
	{

		if (m_heightAboveGround < m_minHeightAboveGround)
			m_heightAboveGround = m_minHeightAboveGround;

		if (m_heightAboveGround > m_maxHeightAboveGround)
			m_heightAboveGround = m_maxHeightAboveGround;

	}  // end if

	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;
	m_doingRotateCamera = false;
	m_doingPitchCamera = false;
	m_doingZoomCamera = false;
	m_doingScriptedCameraLock = false;
	m_cameraConstraintValid = false; // recalc it.
	setCameraTransform();
}

// Retail W3DView::setZoom (0x00742E60) is implemented in W3DViewSetZoomBfme.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?setZoomToDefault@W3DView@@ present-unmatched
void W3DView::setZoomToDefault( void )
{
	// default zoom has to be max, otherwise players will just zoom to max always

	// terrain height + desired height offset == cameraOffset * actual zoom
	// find best approximation of max terrain height we can see
	Real terrainHeightMax = getHeightAroundPos(m_pos.x, m_pos.y);

	Real desiredHeight = (terrainHeightMax + m_maxHeightAboveGround);
	Real desiredZoom = desiredHeight / m_cameraOffset.z;

	//DEBUG_LOG(("W3DView::setZoomToDefault() Current zoom: %g  Desired zoom: %g\n", m_zoom, desiredZoom));

	m_zoom = desiredZoom;
	m_heightAboveGround = m_maxHeightAboveGround;

	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;
	m_doingRotateCamera = false;
	m_doingPitchCamera = false;
	m_doingZoomCamera = false;
	m_doingScriptedCameraLock = false;
	m_cameraConstraintValid = false; // recalc it.
	setCameraTransform();
}

//-------------------------------------------------------------------------------------------------
/** Set the horizontal field of view angle */
//-------------------------------------------------------------------------------------------------
void W3DView::setFieldOfView( Real angle )
{
	View::setFieldOfView( angle );

#if defined(_DEBUG) || defined(_INTERNAL)
	// this is only for testing, and recalculating the 
	// camera every frame is wasteful
	setCameraTransform();
#endif
}

//-------------------------------------------------------------------------------------------------
/** Using the W3D camera translate the world coordinate to a screen coord.
	Screen coordinates returned in absolute values relative to full display resolution.  
  Returns if the point is on screen, off screen, or not transformable */
// Retail W3DView::worldToScreenTriReturn (0x0073BA10) is implemented in W3DViewWorldToScreenBfme.cpp.

//-------------------------------------------------------------------------------------------------
/** Using the W3D camera translate the screen coord to world coord */
//-------------------------------------------------------------------------------------------------
// ?screenToWorld@W3DView@@ present-unmatched
void W3DView::screenToWorld( const ICoord2D *s, Coord3D *w )
{

	// sanity
	if( s == NULL || w == NULL )
		return;

	if( m_3DCamera )
	{
		DEBUG_CRASH(("implement me"));
	}  // end if

}  // end screenToWorld

//-------------------------------------------------------------------------------------------------
/** all the drawables in the view, that fall within the 2D screen region
	* will call the callback function.  The number of drawables that passed
	* the test are returned.
	Screen coordinates assumed in absolute values relative to full display resolution. */
// Retail W3DView::iterateDrawablesInRegion (0x0073BB10) is implemented in W3DViewIterateDrawablesInRegionBfme.cpp.

//-------------------------------------------------------------------------------------------------
/** cast a ray from the screen coords into the scene and return a drawable
  * there if present. Screen coordinates assumed in absolute values relative
  * to full display resolution. */
//-------------------------------------------------------------------------------------------------
// ?pickDrawable@W3DView@@ present-unmatched
Drawable *W3DView::pickDrawable( const ICoord2D *screen, Bool forceAttack, PickType pickType )
{
	RenderObjClass *renderObj = NULL;
	Drawable *draw = NULL;
	DrawableInfo *drawInfo = NULL;

	// sanity
	if( screen == NULL )
		return NULL;

	// don't pick a drawable if there is a window under the cursor
	GameWindow *window = NULL;
	if (TheWindowManager)
		window = TheWindowManager->getWindowUnderCursor(screen->x, screen->y);

	while (window)
	{
		// check to see if it or any of its parents are opaque.  If so, we can't select anything.
		if (!BitTest( window->winGetStatus(), WIN_STATUS_SEE_THRU ))
			return NULL;

		window = window->winGetParent();
	}

	Vector3 rayStart,rayEnd;
	getPickRay(screen,&rayStart,&rayEnd);

	LineSegClass lineseg;
	lineseg.Set(rayStart,rayEnd);

	CastResultStruct result;

	if (forceAttack) 
		result.ComputeContactPoint = true;

	//Don't check against translucent or hidden objects
	RayCollisionTestClass raytest(lineseg,&result,COLL_TYPE_ALL,false,false);

	if( W3DDisplay::m_3DScene->castRay( raytest, false, (Int)pickType ) )
		renderObj = raytest.CollidedRenderObj;

	// for right now there is no drawable data in a render object which is			 	// if we've found a render object, return our drawable associated with it,

	// the terrain, therefore the userdata is NULL
	/// @todo terrain and picking!
	if( renderObj )
		drawInfo = (DrawableInfo *)renderObj->Get_User_Data();
	if (drawInfo)
		draw=drawInfo->m_drawable;

	return draw;

}  // end pickDrawable

//-------------------------------------------------------------------------------------------------
/** convert a pixel (x,y) to a location in the world on the terrain.
	Screen coordinates assumed in absolute values relative to full display resolution.  */
//-------------------------------------------------------------------------------------------------
// ?screenToTerrain@W3DView@@ present-unmatched
void W3DView::screenToTerrain( const ICoord2D *screen, Coord3D *world )
{
	// sanity
	if( screen == NULL || world == NULL || TheTerrainRenderObject == NULL )
		return;

	if (m_cameraHasMovedSinceRequest) {
		m_locationRequests.clear();
		m_cameraHasMovedSinceRequest = false;
	}

	if (m_locationRequests.size() > MAX_REQUEST_CACHE_SIZE) {
		m_locationRequests.erase(m_locationRequests.begin(), m_locationRequests.begin() + 10);
	}


	// We insert them at the end for speed (no copies needed), but using the princ of locality, we should 
	// start searching where we most recently inserted
	for (int i = m_locationRequests.size() - 1; i >= 0; --i) {
		if (m_locationRequests[i].first.x == screen->x && m_locationRequests[i].first.y == screen->y) {
			(*world) = m_locationRequests[i].second;
			return;
		}
	}

	Vector3 rayStart,rayEnd;
	LineSegClass lineseg;
	CastResultStruct result;
	Vector3 intersection(0,0,0);

	getPickRay(screen,&rayStart,&rayEnd);

	lineseg.Set(rayStart,rayEnd);

	RayCollisionTestClass raytest(lineseg,&result);

	if( TheTerrainRenderObject->Cast_Ray(raytest) )
	{
		// get the point of intersection according to W3D
		intersection = result.ContactPoint;
		
	}  // end if

	// Pick bridges.  
	Vector3 bridgePt;
	Drawable *bridge = TheTerrainLogic->pickBridge(rayStart, rayEnd, &bridgePt);
	if (bridge && bridgePt.Z > intersection.Z) {
		intersection = bridgePt;
	}

	world->x = intersection.X;
	world->y = intersection.Y;
	world->z = intersection.Z;

	PosRequest req;
	req.first = (*screen);
	req.second = (*world);
	m_locationRequests.push_back(req);	// Insert this request at the end, requires no extra copies

}  // end screenToTerrain

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?lookAt@W3DView@@ present-unmatched
void W3DView::lookAt( const Coord3D *o ) 
{
	Coord3D pos = *o;


// no, don't call the super-lookAt, since it will munge our coords
// as for a 2d view. just call setPosition.
//View::lookAt(&pos);

	if (o->z > PATHFIND_CELL_SIZE_F+TheTerrainLogic->getGroundHeight(pos.x, pos.y)) {
		// Pos.z is not used, so if we want to look at something off the ground, 
		// we have to look at the spot on the ground such that the object intersects
		// with the look at vector in the center of the screen.  jba.
		Vector3 rayStart,rayEnd;
		LineSegClass lineseg;
		CastResultStruct result;
		Vector3 intersection(0,0,0);

		rayStart = m_3DCamera->Get_Position();	//get camera location
		m_3DCamera->Un_Project(rayEnd,Vector2(0.0f,0.0f));	//get world space point
		rayEnd -= rayStart;	//vector camera to world space point
		rayEnd.Normalize();	//make unit vector
		rayEnd *= m_3DCamera->Get_Depth();	//adjust length to reach far clip plane
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
	setPosition(&pos); 
	m_doingRotateCamera = false;
	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;
	m_doingScriptedCameraLock = false;

	setCameraTransform();

}

// Retail W3DView::initHeightForMap (0x00743520) is implemented in W3DViewInitHeightForMapBfme.cpp.

//-------------------------------------------------------------------------------------------------
/** Move camera to in an interesting fashion.  Sets up parameters that get
 * evaluated in draw(). */
//-------------------------------------------------------------------------------------------------
// ?moveCameraTo@W3DView@@ present-unmatched
void W3DView::moveCameraTo(const Coord3D *o, Int milliseconds, Int shutter, Bool orient, Real easeIn, Real easeOut)
{
	m_mcwpInfo.waypoints[0] = *getPosition();	
	m_mcwpInfo.cameraAngle[0] = getAngle();	
	m_mcwpInfo.waySegLength[0] = 0;	

	m_mcwpInfo.waypoints[1] = *getPosition();	
	m_mcwpInfo.waySegLength[1] = 0;	

	m_mcwpInfo.waypoints[2] = *o;	
	m_mcwpInfo.waySegLength[2] = 0;	

	m_mcwpInfo.numWaypoints = 2;
	if (milliseconds<1) milliseconds = 1;
	m_mcwpInfo.totalTimeMilliseconds = milliseconds;
	m_mcwpInfo.shutter = 1;
	m_mcwpInfo.ease.setEaseTimes(easeIn/milliseconds, easeOut/milliseconds);
	m_mcwpInfo.curSegment = 1;
	m_mcwpInfo.curSegDistance = 0;
	m_mcwpInfo.totalDistance = 0;

	setupWaypointPath(orient);
	if (m_mcwpInfo.totalTimeMilliseconds==1) {
		// do it instantly.
		moveAlongWaypointPath(1);
		m_doingMoveCameraOnWaypointPath = true;
		m_CameraArrivedAtWaypointOnPathFlag = false;
	}
}

//-------------------------------------------------------------------------------------------------
/** Rotate the camera */
//-------------------------------------------------------------------------------------------------
// ?rotateCamera@W3DView@@ present-unmatched
void W3DView::rotateCamera(Real rotations, Int milliseconds, Real easeIn, Real easeOut)
{
	m_rcInfo.numHoldFrames = 0;
	m_rcInfo.trackObject = FALSE;

	if (milliseconds<1) milliseconds = 1;
	m_rcInfo.numFrames = milliseconds/TheW3DFrameLengthInMsec;
	if (m_rcInfo.numFrames < 1) {
		m_rcInfo.numFrames = 1;
	}
	m_rcInfo.curFrame = 0;
	m_doingRotateCamera = true;
	m_rcInfo.angle.startAngle = m_angle;
	m_rcInfo.angle.endAngle = m_angle + 2*PI*rotations;
	m_rcInfo.startTimeMultiplier = m_timeMultiplier;
	m_rcInfo.endTimeMultiplier = m_timeMultiplier;
	m_rcInfo.ease.setEaseTimes(easeIn/milliseconds, easeOut/milliseconds);

	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;
}

//-------------------------------------------------------------------------------------------------
/** Rotate the camera to follow a unit */
//-------------------------------------------------------------------------------------------------
// ?rotateCameraTowardObject@W3DView@@ present-unmatched
void W3DView::rotateCameraTowardObject(ObjectID id, Int milliseconds, Int holdMilliseconds, Real easeIn, Real easeOut)
{
	m_rcInfo.trackObject = TRUE;
	if (holdMilliseconds<1) holdMilliseconds = 0;
	m_rcInfo.numHoldFrames = holdMilliseconds/TheW3DFrameLengthInMsec;
	if (m_rcInfo.numHoldFrames < 1) {
		m_rcInfo.numHoldFrames = 0;
	}

	if (milliseconds<1) milliseconds = 1;
	m_rcInfo.numFrames = milliseconds/TheW3DFrameLengthInMsec;
	if (m_rcInfo.numFrames < 1) {
		m_rcInfo.numFrames = 1;
	}
	m_rcInfo.curFrame = 0;
	m_doingRotateCamera = true;
	m_rcInfo.target.targetObjectID = id;
	m_rcInfo.startTimeMultiplier = m_timeMultiplier;
	m_rcInfo.endTimeMultiplier = m_timeMultiplier;
	m_rcInfo.ease.setEaseTimes(easeIn/milliseconds, easeOut/milliseconds);

	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;
}

//-------------------------------------------------------------------------------------------------
/** Rotate camera to face a location */
//-------------------------------------------------------------------------------------------------
// ?rotateCameraTowardPosition@W3DView@@ present-unmatched
void W3DView::rotateCameraTowardPosition(const Coord3D *pLoc, Int milliseconds, Real easeIn, Real easeOut, Bool reverseRotation)
{
	m_rcInfo.numHoldFrames = 0;
	m_rcInfo.trackObject = FALSE;

	if (milliseconds<1) milliseconds = 1;
	m_rcInfo.numFrames = milliseconds/TheW3DFrameLengthInMsec;
	if (m_rcInfo.numFrames < 1) {
		m_rcInfo.numFrames = 1;
	}
	Coord3D curPos = *getPosition();
	Vector2 dir(pLoc->x-curPos.x, pLoc->y-curPos.y);
	const Real dirLength = dir.Length();
	if (dirLength<0.1f) return;
	Real angle = WWMath::Acos(dir.X/dirLength);
	if (dir.Y<0.0f) {
		angle = -angle;
	}
	// Default camera is rotated 90 degrees, so match.
	angle -= PI/2;
	normAngle(angle);

	if (reverseRotation) {
		if (m_angle < angle) {
			angle -= 2.0f*WWMATH_PI;
		} else {
			angle += 2.0f*WWMATH_PI;
		}
	}

	m_rcInfo.curFrame = 0;
	m_doingRotateCamera = true;
	m_rcInfo.angle.startAngle = m_angle;
	m_rcInfo.angle.endAngle = angle;
	m_rcInfo.startTimeMultiplier = m_timeMultiplier;
	m_rcInfo.endTimeMultiplier = m_timeMultiplier;
	m_rcInfo.ease.setEaseTimes(easeIn/milliseconds, easeOut/milliseconds);

	m_doingMoveCameraOnWaypointPath = false;
	m_CameraArrivedAtWaypointOnPathFlag = false;
}

// Retail W3DView::zoomCamera (0x0073FC40) is implemented in W3DViewZoomCameraBfme.cpp.

// Retail W3DView::pitchCamera (0x0073FCF0) is implemented in W3DViewPitchCameraBfme.cpp.

// Retail W3DView::cameraModFinalZoom (0x0073BF80) is implemented in W3DViewCameraModFinalZoomBfme.cpp.

//-------------------------------------------------------------------------------------------------
/** Sets the final zoom for a camera movement. */
//-------------------------------------------------------------------------------------------------
// ?cameraModFreezeAngle@W3DView@@ present-unmatched
void W3DView::cameraModFreezeAngle(void) 
{
	if (m_doingRotateCamera) {
		if (m_rcInfo.trackObject) {
			m_rcInfo.target.targetObjectID = INVALID_ID;
		} else {
			m_rcInfo.angle.startAngle = m_rcInfo.angle.endAngle = m_angle; // Silly, but consistent.
		}
	}
	if (m_doingMoveCameraOnWaypointPath) {
		Int i;
//		Real curDistance = 0;
		for (i=0; i<m_mcwpInfo.numWaypoints; i++) {
			m_mcwpInfo.cameraAngle[i+1] = m_mcwpInfo.cameraAngle[0];
		}
	}
}

// Retail W3DView::cameraModLookToward (0x0073FF30) is implemented in W3DViewCameraModLookTowardBfme.cpp.

// Retail W3DView::cameraModFinalMoveTo (0x0073C1B0) is implemented in W3DViewCameraModFinalMoveToBfme.cpp.

// Retail W3DView::cameraModFinalLookToward (0x007401A0) is implemented in W3DViewCameraModFinalLookTowardBfme.cpp.

// Retail W3DView::cameraModFinalTimeMultiplier (0x0073C2D0) is implemented in W3DViewCameraModFinalTimeMultiplierBfme.cpp.

// ------------------------------------------------------------------------------------------------
/** Sets the number of frames to average motion for a camera movement */
// ------------------------------------------------------------------------------------------------
// ?cameraModRollingAverage@W3DView@@ present-unmatched
void W3DView::cameraModRollingAverage(Int framesToAverage) 
{
	if (framesToAverage < 1) framesToAverage = 1;
	m_mcwpInfo.rollingAverageFrames = framesToAverage;
}
 
// Retail W3DView::cameraModFinalPitch (0x0073C440) is implemented in W3DViewCameraModFinalPitchBfme.cpp.

// Retail W3DView::resetCamera (0x00743640) is implemented in W3DViewResetCameraBfme.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?isCameraMovementFinished@W3DView@@ present-unmatched
Bool W3DView::isCameraMovementFinished(void)
{
	if (m_viewFilter == FT_VIEW_MOTION_BLUR_FILTER) {
		// Several of the motion blur effects are similar to camera movements.
		if (m_viewFilterMode == FM_VIEW_MB_IN_AND_OUT_ALPHA ||
				m_viewFilterMode == FM_VIEW_MB_IN_AND_OUT_SATURATE ||
				m_viewFilterMode == FM_VIEW_MB_IN_ALPHA ||
				m_viewFilterMode == FM_VIEW_MB_OUT_ALPHA ||
				m_viewFilterMode == FM_VIEW_MB_IN_SATURATE ||
				m_viewFilterMode == FM_VIEW_MB_OUT_SATURATE ) {
			return true;
		}
	}
	return !m_doingMoveCameraOnWaypointPath && !m_doingRotateCamera && !m_doingPitchCamera && !m_doingZoomCamera;
}


// ?isCameraMovementAtWaypointAlongPath@W3DView@@ present-unmatched
Bool W3DView::isCameraMovementAtWaypointAlongPath(void)
{
	// WWDEBUG_SAY((( "MBL: Polling W3DView::isCameraMovementAtWaypointAlongPath\n" )));
	
	Bool return_value = m_CameraArrivedAtWaypointOnPathFlag;
	#pragma message( "MBL: Clearing variable after polling - for scripting - see Adam.\n" )
	m_CameraArrivedAtWaypointOnPathFlag = false;
	return( return_value );
}

// ------------------------------------------------------------------------------------------------
/** Move camera along a waypoint path in an interesting fashion.  Sets up parameters that get
 * evaluated in draw(). */
 // ------------------------------------------------------------------------------------------------
// ?moveCameraAlongWaypointPath@W3DView@@ present-unmatched
void W3DView::moveCameraAlongWaypointPath(Waypoint *pWay, Int milliseconds, Int shutter, Bool orient, Real easeIn, Real easeOut)
{
	const Real MIN_DELTA = MAP_XY_FACTOR;

	m_mcwpInfo.waypoints[0] = *getPosition();	
	m_mcwpInfo.cameraAngle[0] = getAngle();	
	m_mcwpInfo.waySegLength[0] = 0;	
	m_mcwpInfo.waypoints[1] = *getPosition();	
	m_mcwpInfo.numWaypoints = 1;
	if (milliseconds<1) milliseconds = 1;
	m_mcwpInfo.totalTimeMilliseconds = milliseconds;
	m_mcwpInfo.shutter = shutter/TheW3DFrameLengthInMsec;
	if (m_mcwpInfo.shutter<1) m_mcwpInfo.shutter = 1;
	m_mcwpInfo.ease.setEaseTimes(easeIn/milliseconds, easeOut/milliseconds);

	while (pWay && m_mcwpInfo.numWaypoints <MAX_WAYPOINTS) {
		m_mcwpInfo.numWaypoints++;
		m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints] = *pWay->getLocation();
		if (pWay->getNumLinks()>0) {
			pWay = pWay->getLink(0);
		} else {
			pWay = NULL;
		}	
		Vector2 dir(m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints].x-m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints-1].x, m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints].y-m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints-1].y);
		if (dir.Length()<MIN_DELTA) {
			if (pWay) {
				m_mcwpInfo.numWaypoints--; // drop this one.
			} else {
				m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints-1] = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints];
				m_mcwpInfo.numWaypoints--; // Push this one back.
			}
		}
	}
	setupWaypointPath(orient);
}

// ------------------------------------------------------------------------------------------------
/** Calculates angles and distances for moving along a waypoint path.  Sets up parameters that get
 * evaluated in draw(). */
// ------------------------------------------------------------------------------------------------
// ?setupWaypointPath@W3DView@@ present-unmatched
void W3DView::setupWaypointPath(Bool orient)
{
	m_mcwpInfo.curSegment = 1;
	m_mcwpInfo.curSegDistance = 0;
	m_mcwpInfo.totalDistance = 0;
	m_mcwpInfo.rollingAverageFrames = 1;
	Int i;
	Real angle = getAngle();
	for (i=1; i<m_mcwpInfo.numWaypoints; i++) {
		Vector2 dir(m_mcwpInfo.waypoints[i+1].x-m_mcwpInfo.waypoints[i].x, m_mcwpInfo.waypoints[i+1].y-m_mcwpInfo.waypoints[i].y);
		m_mcwpInfo.waySegLength[i] = dir.Length();
		m_mcwpInfo.totalDistance += m_mcwpInfo.waySegLength[i];
		if (orient) {
			angle = WWMath::Acos(dir.X/m_mcwpInfo.waySegLength[i]);
			if (dir.Y<0.0f) {
				angle = -angle;
			}

			// Default camera is rotated 90 degrees, so match.
			angle -= PI/2;
			normAngle(angle);
		}
		//DEBUG_LOG(("Original Index %d, angle %.2f\n", i, angle*180/PI));
		m_mcwpInfo.cameraAngle[i] = angle;
	}
	m_mcwpInfo.cameraAngle[1] = getAngle();	
	m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints] = m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints-1];	
	for (i=m_mcwpInfo.numWaypoints-1; i>1; i--) {
		m_mcwpInfo.cameraAngle[i] = (m_mcwpInfo.cameraAngle[i] + m_mcwpInfo.cameraAngle[i-1]) / 2;  
	}
	m_mcwpInfo.waySegLength[m_mcwpInfo.numWaypoints+1] = m_mcwpInfo.waySegLength[m_mcwpInfo.numWaypoints];	

	// Prevent a possible divide by zero.
	if (m_mcwpInfo.totalDistance<1.0) {
		m_mcwpInfo.waySegLength[m_mcwpInfo.numWaypoints-1] += 1.0-m_mcwpInfo.totalDistance;
		m_mcwpInfo.totalDistance = 1.0;
	}

	Real curDistance = 0;
	Coord3D finalPos = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints];
	Real newGround = TheTerrainLogic->getGroundHeight(finalPos.x, finalPos.y);
	for (i=0; i<=m_mcwpInfo.numWaypoints+1; i++) {
		Real factor2 = curDistance / m_mcwpInfo.totalDistance;
		Real factor1 = 1.0-factor2;
		m_mcwpInfo.timeMultiplier[i] = m_timeMultiplier;
		m_mcwpInfo.groundHeight[i] = m_groundLevel*factor1 + newGround*factor2;
		curDistance += m_mcwpInfo.waySegLength[i];
		//DEBUG_LOG(("New Index %d, angle %.2f\n", i, m_mcwpInfo.cameraAngle[i]*180/PI));
	}

	// Pad the end.
	m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints+1] = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints];
	Coord3D cur = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints];
	Coord3D prev = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints-1];
	m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints+1].x += cur.x-prev.x;
	m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints+1].y += cur.y-prev.y;
	m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints+1] = m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints];	
	m_mcwpInfo.groundHeight[m_mcwpInfo.numWaypoints+1] = newGround;	


	cur = m_mcwpInfo.waypoints[2];
	prev = m_mcwpInfo.waypoints[1];
	m_mcwpInfo.waypoints[0].x -= cur.x-prev.x;
	m_mcwpInfo.waypoints[0].y -= cur.y-prev.y;

	m_doingMoveCameraOnWaypointPath = m_mcwpInfo.numWaypoints>1;
	m_CameraArrivedAtWaypointOnPathFlag = false;
	m_doingRotateCamera = false;

	m_mcwpInfo.elapsedTimeMilliseconds = 0;
	m_mcwpInfo.curShutter = m_mcwpInfo.shutter;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
static Real makeQuadraticS(Real t) 
{
	// for t = linear 0-1, convert to quadratic s where 0==0, 0.5==0.5 && 1.0 == 1.0.
	Real tPrime = t;
	if (t<0.5) {
		tPrime = 0.5 * (2*t*2*t);
	} else {
		tPrime = (t-0.5)*2;
		tPrime = WWMath::Sqrt(tPrime);
		tPrime = 0.5 + 0.5*(tPrime);
	}
	return tPrime*0.5 + t*0.5;
}

// Retail W3DView::rotateCameraOneFrame (0x00743860) is implemented in W3DViewRotateCameraOneFrameBfme.cpp.

// Retail W3DView::zoomCameraOneFrame (0x0073C7C0) is implemented in W3DViewZoomCameraOneFrame.cpp.

// Retail W3DView::pitchCameraOneFrame (0x0073C890) is implemented in W3DViewPitchCameraOneFrame.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?moveAlongWaypointPath@W3DView@@ present-unmatched
void W3DView::moveAlongWaypointPath(Int milliseconds)
{
	m_mcwpInfo.elapsedTimeMilliseconds += milliseconds;
	if (TheGlobalData->m_disableCameraMovement) {
		if (m_mcwpInfo.elapsedTimeMilliseconds>m_mcwpInfo.totalTimeMilliseconds) {
			m_doingMoveCameraOnWaypointPath = false;
			m_freezeTimeForCameraMovement = false;
		}
		return;
	}
	if (m_mcwpInfo.elapsedTimeMilliseconds>m_mcwpInfo.totalTimeMilliseconds) {
		m_doingMoveCameraOnWaypointPath = false;
		m_CameraArrivedAtWaypointOnPathFlag = false;

		m_freezeTimeForCameraMovement = false;
		m_angle = m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints];

		m_groundLevel = m_mcwpInfo.groundHeight[m_mcwpInfo.numWaypoints];
		/////////////////////m_cameraOffset.z = m_groundLevel+TheGlobalData->m_cameraHeight;
		m_cameraOffset.y = -(m_cameraOffset.z / tan(TheGlobalData->m_cameraPitch * (PI / 180.0)));
		m_cameraOffset.x = -(m_cameraOffset.y * tan(TheGlobalData->m_cameraYaw * (PI / 180.0)));

		Coord3D pos = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints];
		pos.z = 0;
		setPosition(&pos);
		// Note - assuming that the scripter knows what he is doing, we adjust the constraints so that
		// the scripted action can occur.
		m_cameraConstraint.lo.x = minf(m_cameraConstraint.lo.x, pos.x);
		m_cameraConstraint.hi.x = maxf(m_cameraConstraint.hi.x, pos.x);
		m_cameraConstraint.lo.y = minf(m_cameraConstraint.lo.y, pos.y);
		m_cameraConstraint.hi.y = maxf(m_cameraConstraint.hi.y, pos.y);
		return;
	}

	const Real totalTime = m_mcwpInfo.totalTimeMilliseconds;
	const Real deltaTime = m_mcwpInfo.ease(m_mcwpInfo.elapsedTimeMilliseconds/totalTime) -
		m_mcwpInfo.ease((m_mcwpInfo.elapsedTimeMilliseconds - milliseconds)/totalTime);
	m_mcwpInfo.curSegDistance += deltaTime*m_mcwpInfo.totalDistance;
	while (m_mcwpInfo.curSegDistance >= m_mcwpInfo.waySegLength[m_mcwpInfo.curSegment]) {

		if ( m_doingMoveCameraOnWaypointPath )
		{
			//WWDEBUG_SAY(( "MBL TEST: Camera waypoint along path reached!\n" ));
			m_CameraArrivedAtWaypointOnPathFlag = true;
		}

		m_mcwpInfo.curSegDistance -= m_mcwpInfo.waySegLength[m_mcwpInfo.curSegment];
		m_mcwpInfo.curSegment++;
		if (m_mcwpInfo.curSegment >= m_mcwpInfo.numWaypoints) { 
			m_mcwpInfo.totalTimeMilliseconds = 0; // Will end following next frame.
			return;
		}
	}
	Real avgFactor = 1.0/m_mcwpInfo.rollingAverageFrames;
	m_mcwpInfo.curShutter--;
	if (m_mcwpInfo.curShutter>0) {
		return;
	}
	m_mcwpInfo.curShutter = m_mcwpInfo.shutter;
	Real factor = m_mcwpInfo.curSegDistance / m_mcwpInfo.waySegLength[m_mcwpInfo.curSegment];
	if (m_mcwpInfo.curSegment == m_mcwpInfo.numWaypoints-1) {
		avgFactor = avgFactor + (1.0-avgFactor)*factor;
	}
	Real factor1;
	Real factor2;
	factor1 = 1.0-factor;
	//factor1 = makeQuadraticS(factor1);
	factor2 = 1.0-factor1;
	Real angle1 = m_mcwpInfo.cameraAngle[m_mcwpInfo.curSegment];
	Real angle2 = m_mcwpInfo.cameraAngle[m_mcwpInfo.curSegment+1];
	if (angle2-angle1 > PI) angle1 += 2*PI;
	if (angle2-angle1 < -PI) angle1 -= 2*PI;
	Real angle = angle1 * (factor1) + angle2 * (factor2); 

	normAngle(angle);
	Real deltaAngle = angle-m_angle;
	normAngle(deltaAngle);
	if (fabs(deltaAngle) > PI/10) {
		DEBUG_LOG(("Huh.\n"));
	}
	m_angle += avgFactor*(deltaAngle);
	normAngle(m_angle);

	Real timeMultiplier = m_mcwpInfo.timeMultiplier[m_mcwpInfo.curSegment]*factor1 + 
			m_mcwpInfo.timeMultiplier[m_mcwpInfo.curSegment+1]*factor2;
	m_timeMultiplier = REAL_TO_INT_FLOOR(0.5 + timeMultiplier);

	m_groundLevel = m_mcwpInfo.groundHeight[m_mcwpInfo.curSegment]*factor1 + 
			m_mcwpInfo.groundHeight[m_mcwpInfo.curSegment+1]*factor2;
	//////////////m_cameraOffset.z = m_groundLevel+TheGlobalData->m_cameraHeight;
	m_cameraOffset.y = -(m_cameraOffset.z / tan(TheGlobalData->m_cameraPitch * (PI / 180.0)));
	m_cameraOffset.x = -(m_cameraOffset.y * tan(TheGlobalData->m_cameraYaw * (PI / 180.0)));

	Coord3D start, mid, end;
	if (factor<0.5) {
		start = m_mcwpInfo.waypoints[m_mcwpInfo.curSegment-1];
		start.x += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment].x;
		start.y += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment].y;
		start.x /= 2;
		start.y /= 2;
		mid = m_mcwpInfo.waypoints[m_mcwpInfo.curSegment];
		end = m_mcwpInfo.waypoints[m_mcwpInfo.curSegment];
		end.x += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+1].x;
		end.y += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+1].y;
		end.x /= 2;
		end.y /= 2;
		factor += 0.5;
	} else {
		start = m_mcwpInfo.waypoints[m_mcwpInfo.curSegment];
		start.x += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+1].x;
		start.y += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+1].y;
		start.x /= 2;
		start.y /= 2;
		mid = m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+1];
		end = m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+1];
		end.x += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+2].x;
		end.y += m_mcwpInfo.waypoints[m_mcwpInfo.curSegment+2].y;
		end.x /= 2;
		end.y /= 2;
		factor -= 0.5;
	}

	Coord3D result = start;
	result.x += factor*(end.x-start.x);
	result.y += factor*(end.y-start.y);
	result.x += (1-factor)*factor*(mid.x-end.x + mid.x-start.x);
	result.y += (1-factor)*factor*(mid.y-end.y + mid.y-start.y);
	result.z = 0;
/*
	static Real prevGround = 0;
	DEBUG_LOG(("Dx %.2f, dy %.2f, DeltaANgle = %.2f, %.2f DeltaGround %.2f\n", m_pos.x-result.x, m_pos.y-result.y, deltaAngle, m_groundLevel, m_groundLevel-prevGround));
	prevGround = m_groundLevel;
*/
	setPosition(&result);
	// Note - assuming that the scripter knows what he is doing, we adjust the constraints so that
	// the scripted action can occur.
	m_cameraConstraint.lo.x = minf(m_cameraConstraint.lo.x, result.x);
	m_cameraConstraint.hi.x = maxf(m_cameraConstraint.hi.x, result.x);
	m_cameraConstraint.lo.y = minf(m_cameraConstraint.lo.y, result.y);
	m_cameraConstraint.hi.y = maxf(m_cameraConstraint.hi.y, result.y);

}


// ------------------------------------------------------------------------------------------------
/** Add an impulse force to shake the camera.
 * The camera shake is a simple simulation of an oscillating spring/damper.
 * The idea is that some sort of shock has "pushed" the camera once, as an
 * impluse, after which the camera vibrates back to its rest position.
 * @todo This should be part of "View", not "W3DView". */
// ------------------------------------------------------------------------------------------------
// ?shake@W3DView@@ present-unmatched
void W3DView::shake( const Coord3D *epicenter, CameraShakeType shakeType )
{
	Real angle = GameClientRandomValueReal( 0, 2*PI );

	m_shakeAngleCos = (Real)cos( angle );
	m_shakeAngleSin = (Real)sin( angle );

	Real intensity = 0.0f;
	switch( shakeType )
	{
		case SHAKE_SUBTLE:
			intensity = TheGlobalData->m_shakeSubtleIntensity;
			break;

		case SHAKE_NORMAL:
			intensity = TheGlobalData->m_shakeNormalIntensity;
			break;

		case SHAKE_STRONG:
			intensity = TheGlobalData->m_shakeStrongIntensity;
			break;

		case SHAKE_SEVERE:
			intensity = TheGlobalData->m_shakeSevereIntensity;
			break;
		
		case SHAKE_CINE_EXTREME:
			intensity = TheGlobalData->m_shakeCineExtremeIntensity;
			break;

		case SHAKE_CINE_INSANE:
			intensity = TheGlobalData->m_shakeCineInsaneIntensity;
			break;
	}

	// intensity falls off with distance
	const Coord3D *viewPos = getPosition();
	Coord3D d;
	d.x = epicenter->x - viewPos->x;
	d.y = epicenter->y - viewPos->y;
	/// @todo make this 3D once we have the real "lookat" spot
	//d.z = epicenter->z - viewPos->z;

	Real dist = (Real)sqrt( d.x*d.x + d.y*d.y );

	if (dist > TheGlobalData->m_maxShakeRange)
		return;

	intensity *= 1.0f - (dist/TheGlobalData->m_maxShakeRange);

	// add intensity and clamp
	m_shakeIntensity += intensity;

	//const Real maxIntensity = 10.0f;
	const Real maxIntensity = 3.0f;
	if (m_shakeIntensity > TheGlobalData->m_maxShakeIntensity)
		m_shakeIntensity = maxIntensity;
}

//-------------------------------------------------------------------------------------------------
/** Transformt he screen pixel coord passed in, to a world coordinate at the specified
	* z value */
//-------------------------------------------------------------------------------------------------
void W3DView::screenToWorldAtZ( const ICoord2D *s, Coord3D *w, Real z )
{
	Vector3 rayStart, rayEnd;

	getPickRay(s, &rayStart, &rayEnd);
	if (rayStart.Z - z < 120.0f)
		z = rayStart.Z - 120.0f;
	w->x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
	w->y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
	w->z = z;
}

// ?cameraEnableSlaveMode@W3DView@@ present-unmatched
void W3DView::cameraEnableSlaveMode(const AsciiString & objectName, const AsciiString & boneName)
{
	m_isCameraSlaved = true;
	m_cameraSlaveObjectName = objectName;
	m_cameraSlaveObjectBoneName = boneName;
}

// ?cameraDisableSlaveMode@W3DView@@ present-unmatched
void W3DView::cameraDisableSlaveMode(void)	
{
	m_isCameraSlaved = false;
}

// ?cameraEnableRealZoomMode@W3DView@@ present-unmatched
void W3DView::cameraEnableRealZoomMode(void) //WST added 10/18/2002
{
	m_useRealZoomCam = true;
	m_FXPitch = 1.0f;	//Reset to default
	//m_zoom = 1.0f;
	updateView();
}

// ?cameraDisableRealZoomMode@W3DView@@ present-unmatched
void W3DView::cameraDisableRealZoomMode(void) //WST added 10/18/2002
{
	m_useRealZoomCam = false;
	m_FXPitch = 1.0f;	//Reset to default
	//m_zoom = 1.0f;
	m_FOV = 50.0f * PI/180.0f;
	setCameraTransform();
	updateView();
}

void W3DView::Add_Camera_Shake (const Coord3D & position,float radius,float duration,float power) //WST added 11/13/02
{
	Vector3 vpos;

	vpos.X = position.x;
	vpos.Y = position.y;
	vpos.Z = position.z;

	(*(CameraShakeSystemClass **)&CameraShakerSystem)->Add_Camera_Shake(
		vpos, radius, duration, power);
}
