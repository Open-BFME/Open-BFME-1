// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DDebrisDraw.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Default w3d draw module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "Common/FileSystem.h"	// this is only here to pull in LOAD_TEST_ASSETS
#include "Common/GlobalData.h"
#include "Common/ThingTemplate.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameClient/Shadow.h"
#include "GameClient/FXList.h"
#include "GameLogic/TerrainLogic.h"

#include "WW3D2/HAnim.h"
#include "WW3D2/HLod.h"
#include "WW3D2/RendObj.h"
#include "W3DDevice/GameClient/Module/W3DDebrisDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"

HAnimClass *Get_HAnim(const char *name);

// BFME's render interfaces predate the Zero Hour headers used to build this
// source tree.  Keep the retail virtual slots and the extended shadow
// descriptor local to this translation unit.
class BfmeSceneView
{
public:
	__forceinline void addRenderObject(RenderObjClass *renderObject)
	{
		typedef void (BfmeSceneView::*Method)(RenderObjClass *);
		(this->*(*(Method *)&(*(void ***)this)[2]))(renderObject);
	}
};

class BfmeRenderObjectView
{
public:
	__forceinline void setTransform(const Matrix3D &transform)
	{
		typedef void (BfmeRenderObjectView::*Method)(const Matrix3D &);
		(this->*(*(Method *)&(*(void ***)this)[21]))(transform);
	}

	__forceinline void setUserData(void *value, Bool recursive)
	{
		typedef void (BfmeRenderObjectView::*Method)(void *, Bool);
		(this->*(*(Method *)&(*(void ***)this)[85]))(value, recursive);
	}
};

struct BfmeShadowTypeInfo
{
	char m_shadowNames[128];
	ShadowType m_type;
	Bool m_allowUpdates;
	Bool m_allowWorldAlign;
	unsigned char m_padding86[2];
	Real m_sizeX;
	Real m_sizeY;
	Real m_offsetX;
	Real m_offsetY;
	Real m_unmodelled98;
	Real m_unmodelled9c;
	Bool m_unmodelleda0;
};

// Retail exposes the scaled/recoloured BFME factory as a cdecl wrapper.  Its
// 0x00901F80 body is also reached by ModelConditionInfo's named validation
// caller and implements this exact three-argument ABI.
RenderObjClass *Create_Render_Obj(const char *name, Real scale, Int color);

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0W3DDebrisDraw@@ is implemented by the exact retail thunk in
// W3DDebrisDrawCtorThunk.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DDebrisDraw@@MAE@XZ present-unmatched
W3DDebrisDraw::~W3DDebrisDraw(void)
{
	if (TheW3DShadowManager && m_shadow)
	{	
		TheW3DShadowManager->removeShadow(m_shadow);
		m_shadow = NULL;
	}
	if (m_renderObject)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(m_renderObject);
  	REF_PTR_RELEASE(m_renderObject);
 		m_renderObject = NULL; 	
	}
	for (int i = 0; i < STATECOUNT; ++i)
	{
		REF_PTR_RELEASE(m_anims[i]);
		m_anims[i] = NULL;
	}
}

//-------------------------------------------------------------------------------------------------
// ?setShadowsEnabled@W3DDebrisDraw@@UAEX_N@Z present-unmatched
void W3DDebrisDraw::setShadowsEnabled(Bool enable)
{
	if (m_shadow)
		m_shadow->enableShadowRender(enable);
}

//-------------------------------------------------------------------------------------------------
// ?setFullyObscuredByShroud@W3DDebrisDraw@@UAEX_N@Z present-unmatched
void W3DDebrisDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (m_shadow)
		m_shadow->enableShadowInvisible(fullyObscured);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void W3DDebrisDraw::setModelName(AsciiString name, Color color, ShadowType t)
{
  if (m_renderObject == NULL && !name.isEmpty())
	{
		Matrix3D transform;
		BfmeShadowTypeInfo shadowInfo;
		Int hexColor = 0;
		if (color != 0)
			hexColor = color | 0xFF000000;
		m_renderObject = Create_Render_Obj(name.str(), getDrawable()->getScale(), hexColor);
		DEBUG_ASSERTCRASH(m_renderObject, ("Debris model %s not found!\n",name.str()));
		if (m_renderObject)
		{
			reinterpret_cast<BfmeSceneView *>(W3DDisplay::m_3DScene)->addRenderObject(m_renderObject);

			reinterpret_cast<BfmeRenderObjectView *>(m_renderObject)->setUserData(
				reinterpret_cast<unsigned char *>(getDrawable()) + 0x240, false);
			
			///@todo: Change back to identity once we figure out why objects show up at 0,0,0
			/// OBJECT_PILE
//			transform.Set(Vector3(0,0,9999));
			transform.Set(Vector3(0,0,0));
			reinterpret_cast<BfmeRenderObjectView *>(m_renderObject)->setTransform(transform);
		}
		
		if (t != SHADOW_NONE)
		{
			shadowInfo.m_unmodelled9c = 20.0f;
			shadowInfo.m_unmodelleda0 = false;
			shadowInfo.m_type = t;
			shadowInfo.m_sizeX=0;
			shadowInfo.m_sizeY=0;
			shadowInfo.m_unmodelled98 = 0.0f;
			m_shadow = TheW3DShadowManager->addShadow(m_renderObject,
				reinterpret_cast<Shadow::ShadowTypeInfo *>(&shadowInfo));
		}
		else
		{
			if (TheW3DShadowManager && m_shadow)
			{	
				TheW3DShadowManager->removeShadow(m_shadow);
				m_shadow = NULL;
			}
		}

		// save the model name and color
		m_modelName = name;
		m_modelColor = color;

	}
}

//-------------------------------------------------------------------------------------------------
void W3DDebrisDraw::setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList* finalFX)
{
	int i;
	for (i = 0; i < STATECOUNT; ++i)
	{
		if (m_anims[i] != NULL)
		{
			m_anims[i]->Release_Ref();
			m_anims[i] = NULL;
		}
		m_anims[i] = NULL;
	}

	m_anims[INITIAL] = initial.isEmpty() ? NULL : Get_HAnim(initial.str());
	m_anims[FLYING] = flying.isEmpty() ? NULL : Get_HAnim(flying.str());
	if (stricmp(final.str(), "STOP") == 0)
	{
		m_finalStop = true;
		final = flying;
	}
	else
	{
		m_finalStop = false;
	}
	m_anims[FINAL] = final.isEmpty() ? NULL : Get_HAnim(final.str());
	m_state = 0;
	m_frames = 0;
	m_fxFinal = finalFX;

	m_animInitial = initial;
	m_animFlying = flying;
	m_animFinal = final;

}

//-------------------------------------------------------------------------------------------------
static Bool isAnimationComplete(RenderObjClass* r)
{
	if (r->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)r;
		return hlod->Is_Animation_Complete();
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
static Bool isNearlyZero(const Coord3D* vel)
{
	const Real TINY = 0.01f;
	return fabs(vel->x) < TINY && fabs(vel->y) < TINY && fabs(vel->z) < TINY;
}

// ------------------------------------------------------------------------------------------------
// ?reactToTransformChange@W3DDebrisDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z present-unmatched
void W3DDebrisDraw::reactToTransformChange( const Matrix3D *oldMtx, 
																						const Coord3D *oldPos, 
																						Real oldAngle )
{

	if( m_renderObject )
		m_renderObject->Set_Transform( *getDrawable()->getTransformMatrix() );

}

//-------------------------------------------------------------------------------------------------
// ?doDrawModule@W3DDebrisDraw@@ present-unmatched
void W3DDebrisDraw::doDrawModule(const Matrix3D* transformMtx)
{
	if (m_renderObject)
	{

		Matrix3D scaledTransform;
		if (getDrawable()->getInstanceScale() != 1.0f)
		{	//do custom scaling of the W3D model.
			scaledTransform=*transformMtx;
			scaledTransform.Scale(getDrawable()->getInstanceScale());
			transformMtx = &scaledTransform;
			m_renderObject->Set_ObjectScale(getDrawable()->getInstanceScale());
		}
		m_renderObject->Set_Transform(*transformMtx);

		static const RenderObjClass::AnimMode TheAnimModes[STATECOUNT] = 
		{
			RenderObjClass::ANIM_MODE_ONCE,
			RenderObjClass::ANIM_MODE_LOOP,
			RenderObjClass::ANIM_MODE_ONCE
		};
		
		Int oldState = m_state;
		Object* obj = getDrawable()->getObject();
		const Int MIN_FINAL_FRAMES = 3;
		if (m_state != FINAL && obj != NULL && !obj->isAboveTerrain() && m_frames > MIN_FINAL_FRAMES)
		{
			m_state = FINAL;
		}
		else if (m_state < FINAL && (isAnimationComplete(m_renderObject)))
		{
			++m_state;
		}
		HAnimClass* hanim = m_anims[m_state];
		if (hanim != NULL && (hanim != m_renderObject->Peek_Animation() || oldState != m_state))
		{
			RenderObjClass::AnimMode m = TheAnimModes[m_state];
			if (m_state == FINAL)
			{
				FXList::doFXPos(m_fxFinal, getDrawable()->getPosition(), getDrawable()->getTransformMatrix(), 0, NULL, 0.0f);
				if (m_finalStop)
					m = RenderObjClass::ANIM_MODE_MANUAL;
			}
			m_renderObject->Set_Animation(hanim, 0, m);
		}
		++m_frames;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DDebrisDraw@@MAEXPAVXfer@@@Z present-unmatched
void W3DDebrisDraw::crc( Xfer *xfer )
{

	// extend base class
	DrawModule::crc( xfer );

}  // end crc

// The exact xfer body lives in W3DDebrisDrawXfer.cpp, which declares BFME's
// retail Xfer and by-value string layouts.

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DDebrisDraw@@MAEXXZ present-unmatched
void W3DDebrisDraw::loadPostProcess( void )
{

	// extend base class
	DrawModule::loadPostProcess();

}  // end loadPostProcess
