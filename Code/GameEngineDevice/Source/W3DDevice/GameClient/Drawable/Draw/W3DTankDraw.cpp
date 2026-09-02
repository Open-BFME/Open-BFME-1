// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: W3DTankDraw.cpp //////////////////////////////////////////////////////////////////////////
// Draw turreted tanks
// Michael S. Booth, October 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <math.h>
#include "Common/Thing.h"
#include "Common/ThingFactory.h"
#include "Common/GameAudio.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "W3DDevice/GameClient/W3DGameClient.h"
#include "W3DDevice/GameClient/Module/W3DTankDraw.h"
#include "WW3D2/matinfo.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

class Matrix3D;

// Retail W3D vtable slots used by updateTreadObjects.  The vendored ZH
// headers have a shorter base, so the ordinary member calls dispatch to
// different slots in this one BFME body.
struct BfmeTankRenderObjectThunk
{
	virtual void Slot0() = 0;
	virtual void Slot1() = 0;
	virtual void Slot2() = 0;
	virtual void Slot3() = 0;
	virtual void Slot4() = 0;
	virtual void Slot5() = 0;
	virtual void Slot6() = 0;
	virtual void Slot7() = 0;
	virtual void Slot8() = 0;
	virtual void Slot9() = 0;
	virtual void Slot10() = 0;
	virtual void Slot11() = 0;
	virtual void Slot12() = 0;
	virtual void Slot13() = 0;
	virtual void Slot14() = 0;
	virtual void Slot15() = 0;
	virtual void Slot16() = 0;
	virtual void Slot17() = 0;
	virtual void Slot18() = 0;
	virtual void Slot19() = 0;
	virtual void Slot20() = 0;
	virtual void Slot21() = 0;
	virtual void Slot22() = 0;
	virtual void Slot23() = 0;
	virtual void Slot24() = 0;
	virtual void Slot25() = 0;
	virtual void Slot26() = 0;
	virtual void Slot27() = 0;
	virtual void Slot28() = 0;
	virtual void Slot29() = 0;
	virtual void Slot30() = 0;
	virtual void Slot31() = 0;
	virtual void Slot32() = 0;
	virtual void Slot33() = 0;
	virtual void Slot34() = 0;
	virtual void Slot35() = 0;
	virtual void Slot36() = 0;
	virtual void Slot37() = 0;
	virtual void Slot38() = 0;
	virtual void Slot39() = 0;
	virtual void Slot40() = 0;
	virtual void Slot41() = 0;
	virtual void Slot42() = 0;
	virtual void Slot43() = 0;
	virtual void Slot44() = 0;
	virtual void Slot45() = 0;
	virtual RenderObjClass *GetRenderObject() = 0;
};

struct BfmeTankRenderObjThunk
{
	virtual void Slot0() = 0;
	virtual void Slot1() = 0;
	virtual void Slot2() = 0;
	virtual void Slot3() = 0;
	virtual void Slot4() = 0;
	virtual void Slot5() = 0;
	virtual void Slot6() = 0;
	virtual void Slot7() = 0;
	virtual void Slot8() = 0;
	virtual void Slot9() = 0;
	virtual void Slot10() = 0;
	virtual void Slot11() = 0;
	virtual void Slot12() = 0;
	virtual void Slot13() = 0;
	virtual void Slot14() = 0;
	virtual void Slot15() = 0;
	virtual void Slot16() = 0;
	virtual void Slot17() = 0;
	virtual void Slot18() = 0;
	virtual void Slot19() = 0;
	virtual void Slot20() = 0;
	virtual void Slot21() = 0;
	virtual void Slot22() = 0;
	virtual void Slot23() = 0;
	virtual void Slot24() = 0;
	virtual void Slot25() = 0;
	virtual void Slot26() = 0;
	virtual Int GetNumSubObjects() = 0;
	virtual void Slot27() = 0;
	virtual RenderObjClass *GetSubObject(Int) = 0;
	virtual void Slot30() = 0;
	virtual void Slot31() = 0;
	virtual void Slot32() = 0;
	virtual void Slot33() = 0;
	virtual void Slot34() = 0;
	virtual void Slot35() = 0;
	virtual void Slot36() = 0;
	virtual void Slot37() = 0;
	virtual void Slot38() = 0;
	virtual void Slot39() = 0;
	virtual void Slot40() = 0;
	virtual void Slot41() = 0;
	virtual void Slot42() = 0;
	virtual void Slot43() = 0;
	virtual void Slot44() = 0;
	virtual void Slot45() = 0;
	virtual void Slot46() = 0;
	virtual void Slot47() = 0;
	virtual void Slot48() = 0;
	virtual void Slot49() = 0;
	virtual void Slot50() = 0;
	virtual void Slot51() = 0;
	virtual void Slot52() = 0;
	virtual void Slot53() = 0;
	virtual void Slot54() = 0;
	virtual void Slot55() = 0;
	virtual void Slot56() = 0;
	virtual void Slot57() = 0;
	virtual void Slot58() = 0;
	virtual void Slot59() = 0;
	virtual void Slot60() = 0;
	virtual void Slot61() = 0;
	virtual void Slot62() = 0;
	virtual void Slot63() = 0;
	virtual void Slot64() = 0;
	virtual void Slot65() = 0;
	virtual void Slot66() = 0;
	virtual void Slot67() = 0;
	virtual void Slot68() = 0;
	virtual void Slot69() = 0;
	virtual void Slot70() = 0;
	virtual void Slot71() = 0;
	virtual void Slot72() = 0;
	virtual void Slot73() = 0;
	virtual void Slot74() = 0;
	virtual void Slot75() = 0;
	virtual void Slot76() = 0;
	virtual void Slot77() = 0;
	virtual void Slot78() = 0;
	virtual void Slot79() = 0;
	virtual void Slot80() = 0;
	virtual void Slot81() = 0;
	virtual void Slot82() = 0;
	virtual void Slot83() = 0;
	virtual MaterialInfoClass *GetMaterialInfo() = 0;
	virtual void SetUserData(void *, Bool) = 0;
};

struct BfmeTankSubObjectIdentityThunk
{
	virtual void Slot0() = 0;
	virtual void Slot1() = 0;
	virtual void Slot2() = 0;
	virtual Int Class_ID() = 0;
	virtual void Slot4() = 0;
	virtual void Slot5() = 0;
	virtual const char *GetName() = 0;
};


//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDrawModuleDataCtor.cpp
// ??0W3DTankDrawModuleData@@ present-unmatched
W3DTankDrawModuleData::W3DTankDrawModuleData() :
	m_treadDebrisNameLeft("TrackDebrisDirtLeft"),
	m_treadDebrisNameRight("TrackDebrisDirtRight"),
	m_treadAnimationRate(0.0f),
	m_treadPivotSpeedFraction(0.6f),
	m_treadDriveSpeedFraction(0.3f)
{
}

//-------------------------------------------------------------------------------------------------
// ??1W3DTankDrawModuleData@@ present-unmatched
W3DTankDrawModuleData::~W3DTankDrawModuleData()
{
}

//-------------------------------------------------------------------------------------------------
// ?buildFieldParse@W3DTankDrawModuleData@@ present-unmatched
void W3DTankDrawModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  W3DModelDrawModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "TreadDebrisLeft", INI::parseAsciiString, NULL, offsetof(W3DTankDrawModuleData, m_treadDebrisNameLeft) },
		{ "TreadDebrisRight", INI::parseAsciiString, NULL, offsetof(W3DTankDrawModuleData, m_treadDebrisNameRight) },
		{ "TreadAnimationRate", INI::parseVelocityReal, NULL, offsetof(W3DTankDrawModuleData, m_treadAnimationRate) },
		{ "TreadPivotSpeedFraction", INI::parseReal, NULL, offsetof(W3DTankDrawModuleData, m_treadPivotSpeedFraction) },
		{ "TreadDriveSpeedFraction", INI::parseReal, NULL, offsetof(W3DTankDrawModuleData, m_treadDriveSpeedFraction) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0W3DTankDraw@@ present-unmatched
W3DTankDraw::W3DTankDraw( Thing *thing, const ModuleData* moduleData )
: W3DModelDraw( thing, moduleData ),m_prevRenderObj(NULL), m_treadDebrisLeft(NULL), m_treadDebrisRight(NULL)
{
	m_treadDebrisLeft = NULL;
	m_treadDebrisRight = NULL;

	for (Int i=0; i<MAX_TREADS_PER_TANK; i++)
		m_treads[i].m_robj = NULL;

	m_treadCount=0;
	//Assume all things face along x axis when created.
	m_lastDirection.x=1.0f;
	m_lastDirection.y=0.0f;
	m_lastDirection.z=0.0f;

	createEmitters();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?tossEmitters@W3DTankDraw@@ present-unmatched
void W3DTankDraw::tossEmitters( void )
{
	if (m_treadDebrisLeft)
	{
		m_treadDebrisLeft->attachToObject(NULL);
		m_treadDebrisLeft->destroy();
		m_treadDebrisLeft = NULL;
	}
	if (m_treadDebrisRight)
	{
		m_treadDebrisRight->attachToObject(NULL);
		m_treadDebrisRight->destroy();
		m_treadDebrisRight = NULL;
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?createEmitters@W3DTankDraw@@ present-unmatched
void W3DTankDraw::createEmitters( void )
{
	if (!m_treadDebrisLeft)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(getW3DTankDrawModuleData()->m_treadDebrisNameLeft);
		if (sysTemplate)
		{
			m_treadDebrisLeft = TheParticleSystemManager->createParticleSystem( sysTemplate );
			m_treadDebrisLeft->attachToDrawable(getDrawable());
			// important: mark it as do-not-save, since we'll just re-create it when we reload.
			m_treadDebrisLeft->setSaveable(FALSE);
			// they come into being stopped.
	  	m_treadDebrisLeft->stop();
		}
	}
	if (!m_treadDebrisRight)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(getW3DTankDrawModuleData()->m_treadDebrisNameRight);
		if (sysTemplate)
		{
			m_treadDebrisRight = TheParticleSystemManager->createParticleSystem( sysTemplate );
			m_treadDebrisRight->attachToDrawable(getDrawable());
			// important: mark it as do-not-save, since we'll just re-create it when we reload.
			m_treadDebrisRight->setSaveable(FALSE);
			// they come into being stopped.
	  	m_treadDebrisRight->stop();
		}
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DTankDraw@@ present-unmatched
W3DTankDraw::~W3DTankDraw()
{
	for (Int i=0; i<MAX_TREADS_PER_TANK; i++)
		if (m_treads[i].m_robj)
			REF_PTR_RELEASE(m_treads[i].m_robj);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**

 * Start creating debris from the tank treads
 */
// ?startMoveDebris@W3DTankDraw@@ present-unmatched
void W3DTankDraw::startMoveDebris( void )
{
	if (getDrawable()->isDrawableEffectivelyHidden())
		return;
	if (m_treadDebrisLeft)
    m_treadDebrisLeft->start();
	if (m_treadDebrisRight)
    m_treadDebrisRight->start();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * Stop creating debris from the tank treads
 */
// ?stopMoveDebris@W3DTankDraw@@ present-unmatched
__declspec(noinline) void W3DTankDraw::stopMoveDebris( void )
{
  if (m_treadDebrisLeft)
  	m_treadDebrisLeft->stop();
  if (m_treadDebrisRight)
  	m_treadDebrisRight->stop();
}

//-------------------------------------------------------------------------------------------------
// ?setHidden@W3DTankDraw@@ present-unmatched
void W3DTankDraw::setHidden(Bool h)
{
	W3DModelDraw::setHidden(h);
	if (h)
	{
		stopMoveDebris();
	}
}

//-------------------------------------------------------------------------------------------------
// BFME stores DrawModule's shroud flag at physical offset +0x2d.
void W3DTankDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (fullyObscured != *(const Bool *)((const char *)this + 0x2d))
	{
		if (fullyObscured)
			stopMoveDebris();
	}
	W3DModelDraw::setFullyObscuredByShroud(fullyObscured);
}

/**Update uv coordinates on each tread object to simulate movement*/
void W3DTankDraw::updateTreadPositions(Real uvDelta)
{
	// BFME's W3DTankDraw carries ~0x20c bytes of extra interior fields before
	// m_treads/m_treadCount that the ZH reference header doesn't declare
	// (unreconstructed base-class drift, out of this track's scope) - proven
	// from this function's own retail body (RVA 0x77E0C0): m_treads at
	// this+0x298 (ZH header type puts it at this+0x8c), m_treadCount right
	// after the 4-element array at this+0x2e8 (ZH: this+0xdc). Read via the
	// proven retail offsets directly instead of through the drifted members.
	unsigned char *self = (unsigned char *)this;
	TreadObjectInfo *pTread = (TreadObjectInfo *)(self + 0x298);

	Real offset_u;

	for (Int i=0; i<*(Int *)(self + 0x2e8); i++)
	{
		if (pTread->m_type == TREAD_LEFT)	//this tread needs to scroll forwards
			offset_u = pTread->m_materialSettings.customUVOffset.X + uvDelta;
		else
		if (pTread->m_type == TREAD_RIGHT)	//this tread needs to scroll backwards
			offset_u = pTread->m_materialSettings.customUVOffset.X - uvDelta;
				
		// ensure coordinates of offset are in [0, 1] range:
		offset_u = offset_u - WWMath::Floor(offset_u);
		pTread->m_materialSettings.customUVOffset.Set(offset_u,0);
		pTread++;
	}
}

/**Grab pointers to the sub-meshes for each tread*/ 
void W3DTankDraw::updateTreadObjects(void)
{
	// The BFME W3DModelDraw base has a different layout from the ZH reference
	// header.  This function's retail body proves the render-object virtual
	// slot and the offsets of the tread state, so keep those accesses local to
	// this reconstruction rather than changing the shared header.
	struct BfmeTankLayout
	{
		void *vptr;
		const ModuleData *moduleData;
		unsigned char unknown[0x28C];
		RenderObjClass *prevRenderObj;
		TreadObjectInfo treads[4];
		Int treadCount;
	};
	BfmeTankLayout *tank = (BfmeTankLayout *)this;
	RenderObjClass *robj = reinterpret_cast<BfmeTankRenderObjectThunk *>(tank)->GetRenderObject();

	//clear all previous tread pointers
	for (Int i=0; i<tank->treadCount; i++)
	{
		if (tank->treads[i].m_robj)
			REF_PTR_RELEASE(tank->treads[i].m_robj);
	}
	tank->treadCount = 0;

	//Make sure this object has defined a speed for tread scrolling.
	const W3DTankDrawModuleData *moduleData = (const W3DTankDrawModuleData *)tank->moduleData;
	if (moduleData && *(Real *)((unsigned char *)moduleData + 0x164) && robj)
	{
		BfmeTankRenderObjThunk *retailRobj = reinterpret_cast<BfmeTankRenderObjThunk *>(robj);
		for (Int i=0; i < retailRobj->GetNumSubObjects() && tank->treadCount < MAX_TREADS_PER_TANK; i++)
		{
			RenderObjClass *subObj=retailRobj->GetSubObject(i);
			BfmeTankSubObjectIdentityThunk *subObjIdentity = reinterpret_cast<BfmeTankSubObjectIdentityThunk *>(subObj);
			const char *meshName;
			//Check if subobject name starts with "TREADS".
			if (subObj && subObjIdentity->Class_ID() == RenderObjClass::CLASSID_MESH && subObjIdentity->GetName()
				&& ( (meshName=strchr(subObjIdentity->GetName(),'.') ) != 0 && *(meshName++))
				&&_strnicmp(meshName,"TREADS", 6) == 0)
			{	//check if sub-object has the correct material to do texture scrolling.
				MaterialInfoClass *mat=reinterpret_cast<BfmeTankRenderObjThunk *>(subObj)->GetMaterialInfo();
				if (mat)
				{	for (Int j=0; j<mat->Vertex_Material_Count(); j++)
					{
						VertexMaterialClass *vmaterial=mat->Peek_Vertex_Material(j);
						LinearOffsetTextureMapperClass *mapper=(LinearOffsetTextureMapperClass *)vmaterial->Peek_Mapper();
						if (mapper && mapper->Mapper_ID() == TextureMapperClass::MAPPER_ID_LINEAR_OFFSET)
						{	mapper->Set_UV_Offset_Delta(Vector2(0,0));	//disable automatic scrolling
							subObj->Add_Ref();	//increase reference since we're storing the pointer
							tank->treads[tank->treadCount].m_robj=subObj;
							tank->treads[tank->treadCount].m_type = TREAD_MIDDLE;	//default type
							reinterpret_cast<BfmeTankRenderObjThunk *>(subObj)->SetUserData(&tank->treads[tank->treadCount].m_materialSettings, FALSE);	//tell W3D about custom material settings
							tank->treads[tank->treadCount].m_materialSettings.customUVOffset=Vector2(0,0);
							switch (meshName[6])	//check next character after 'TREADS'
							{
								case 'L':
								case 'l':	tank->treads[tank->treadCount].m_type = TREAD_LEFT;
										break;
								case 'R':
								case 'r':	tank->treads[tank->treadCount].m_type = TREAD_RIGHT;
										break;
							}
							tank->treadCount++;
						}
					}
					REF_PTR_RELEASE(mat);
				}
			}
			REF_PTR_RELEASE(subObj);
		}
	}

	tank->prevRenderObj = robj;
}

//-------------------------------------------------------------------------------------------------
// ?onRenderObjRecreated@W3DTankDraw@@ present-unmatched
void W3DTankDraw::onRenderObjRecreated(void)
{
	updateTreadObjects();
}

//-------------------------------------------------------------------------------------------------
/** Map behavior states into W3D animations. */
//-------------------------------------------------------------------------------------------------
// ?doDrawModule@W3DTankDraw@@ present-unmatched
void W3DTankDraw::doDrawModule(const Matrix3D* transformMtx)
{
	const Real DEBRIS_THRESHOLD = 0.00001f;

 	Bool frozen = TheTacticalView->isTimeFrozen() && !TheTacticalView->isCameraMovementFinished();
 	frozen = frozen || TheScriptEngine->isTimeFrozenDebug() || TheScriptEngine->isTimeFrozenScript();
	if (frozen)
		return;
	if (getRenderObject()==NULL) return;
	if (getRenderObject() != m_prevRenderObj) {
		updateTreadObjects();
	}

	// get object from logic
	Object *obj = getDrawable()->getObject();
	if (obj == NULL)
		return;

	// get object physics state
	PhysicsBehavior *physics = obj->getPhysics();
	if (physics == NULL)
		return;

	const Coord3D *vel = physics->getVelocity();

	// if tank is moving, kick up dust and debris
	Real velMag = vel->x*vel->x + vel->y*vel->y;		// only care about moving on the ground

	if (velMag > DEBRIS_THRESHOLD && !getDrawable()->isDrawableEffectivelyHidden() && !getFullyObscuredByShroud())
		startMoveDebris();
	else
		stopMoveDebris();

	// kick debris higher the faster we move
	Coord3D velMult;
	velMag = (Real)sqrt( velMag );

	velMult.x = 0.5f * velMag + 0.1f;
	if (velMult.x > 1.0f)
		velMult.x = 1.0f;

	velMult.y = velMult.x;

	velMult.z = velMag + 0.1f;
	if (velMult.z > 1.0f)
		velMult.z = 1.0f;

	m_treadDebrisLeft->setVelocityMultiplier( &velMult );
	m_treadDebrisRight->setVelocityMultiplier( &velMult );

	m_treadDebrisLeft->setBurstCountMultiplier( velMult.z );
	m_treadDebrisRight->setBurstCountMultiplier( velMult.z );

	//Update movement of treads
	if (m_treadCount)
	{
		PhysicsTurningType turn=physics->getTurning();
		Real offset_u;
		Real treadScrollSpeed=getW3DTankDrawModuleData()->m_treadAnimationRate;
		TreadObjectInfo *pTread=m_treads;
		Real maxSpeed=obj->getAIUpdateInterface()->getCurLocomotorSpeed();

		//For optimization sake, we only do complex tread scrolling when tank
		//is mostly stationary and turning
		if (turn != TURN_NONE && physics->getVelocityMagnitude()/maxSpeed < getW3DTankDrawModuleData()->m_treadPivotSpeedFraction)
		{
				//Check if we have turned enough since last draw to require animation
				Coord3D dir;
				obj->getUnitDirectionVector2D(dir);
				Real angleToGoal = dir.x * m_lastDirection.x + dir.y * m_lastDirection.y;
				
				if (fabs(1.0f-angleToGoal) > 0.00001f)	//check if difference in angle cosines is greater than some cutoff.
				{
					if (turn == TURN_NEGATIVE)	//turning right
						updateTreadPositions(-treadScrollSpeed);
					else	//turning left
						updateTreadPositions(treadScrollSpeed);
				}
				m_lastDirection=dir;	//update for next frame
		}
		else
		if (physics->isMotive() && physics->getVelocityMagnitude()/maxSpeed >= getW3DTankDrawModuleData()->m_treadDriveSpeedFraction)
		{	//do simple scrolling based only on speed when tank is moving straight at high speed.
			//we stop scrolling when tank slows down to reduce the appearance of sliding
			//tread scrolling speed was not directly tied into tank velocity because it looked odd
			//under certain situations when tank moved sideways.
			for (Int i=0; i<m_treadCount; i++)
			{
				offset_u = pTread->m_materialSettings.customUVOffset.X - treadScrollSpeed;
				// ensure coordinates of offset are in [0, 1] range:
				offset_u = offset_u - WWMath::Floor(offset_u);
				pTread->m_materialSettings.customUVOffset.Set(offset_u,0);
				pTread++;
			}
		}
	}

	W3DModelDraw::doDrawModule(transformMtx);
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DTankDraw@@ present-unmatched
void W3DTankDraw::crc( Xfer *xfer )
{

	// extend base class
	W3DModelDraw::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@W3DTankDraw@@ present-unmatched
void W3DTankDraw::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	W3DModelDraw::xfer( xfer );

	// John A and Mark W say there is no data to save here

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DTankDraw@@ present-unmatched
void W3DTankDraw::loadPostProcess( void )
{

	// extend base class
	W3DModelDraw::loadPostProcess();

	// toss any existing ones and re-create 'em (since this module expects 'em to always be around)
	tossEmitters();
	createEmitters();

}  // end loadPostProcess
