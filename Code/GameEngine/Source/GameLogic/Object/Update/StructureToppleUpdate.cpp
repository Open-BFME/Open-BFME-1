// cl: /ICode/GameEngine/Include /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_copyctor_outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
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

// FILE: StructureToppleUpdate.cpp ///////////////////////////////////////////////////////////////////////
// Author:
// Desc:  
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/INI.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/FXList.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BoneFXUpdate.h"
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"

// Retail's AsciiString is a StringBase<char> with no members of its own, so its
// copy ctor at 0x0005EE50 only forwards to the base body at 0x00887B60, and
// retail inlines that forwarder here. asciistring_copyctor_outofline leaves the
// copy ctor undefined on purpose for the TUs that need the forwarder call;
// defining it here puts the delegation in front of the use in this TU alone.
#include "string_base.h"

inline AsciiString::AsciiString(const AsciiString &stringSrc)
{
	((StringBase<char> *)this)->StringBase<char>::StringBase(
		*(const StringBase<char> *)&stringSrc);
}


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

const Int MAX_IDX = 32;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateConstructor.cpp
// ??0StructureToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
StructureToppleUpdate::StructureToppleUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	
	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_delayBurstLocation.zero();
	m_structuralIntegrity = 0.0f;
	m_toppleDirection.x = m_toppleDirection.y = 0;
	//
	m_toppleFrame = 0;
	m_toppleState = TOPPLESTATE_STANDING;
	m_toppleVelocity = 0.0f;
	m_accumulatedAngle = 0.001f; // Need to give it a little nudge in the right direction
	m_lastCrushedLocation = 0.0f;
	m_nextBurstFrame = -1;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);

	//Get the extent height here, rather than after it dies -- when it switches to dead state
	//the rubble state has a tiny height.
	Object *building = getObject();
	m_buildingHeight = building->getGeometryInfo().getMaxHeightAbovePosition();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1StructureToppleUpdate@@MAE@XZ present-unmatched
StructureToppleUpdate::~StructureToppleUpdate( void )
{
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleObjectCreationLists.cpp
static void parseOCL( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	StructureToppleUpdateModuleData* self = (StructureToppleUpdateModuleData*)instance;
	StructureTopplePhaseType stphase = (StructureTopplePhaseType)INI::scanIndexList(ini->getNextToken(), TheStructureTopplePhaseNames);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls[stphase].push_back(ocl);
	}
}

//-------------------------------------------------------------------------------------------------
// BFME's StructureToppleUpdateModuleData is Zero Hour's shifted by 0x14: the INI table
// binds MinToppleDelay, StructuralIntegrity, ToppleStartFX and MinToppleBurstDelay at
// +0x34/+0x3C/+0x4C/+0x64 (field_names.csv) against Zero Hour's +0x20/+0x28/+0x38/+0x50,
// so angleFX sits at +0xA8 rather than +0x94.
struct BfmeStructureToppleAngleFXView
{
	char m_unmodelled000[0xA8];
	AngleFXInfoVector angleFX;
};

static void parseAngleFX(INI* ini, void *instance, void * /* store */, const void * /*userData*/)
{
	BfmeStructureToppleAngleFXView* self = (BfmeStructureToppleAngleFXView*)instance;
	AngleFXInfo info;
	INI::parseReal(ini, instance, &(info.angle), NULL);
	info.angle = info.angle * PI / 180.0f; // convert from degrees to radians.
	INI::parseFXList(ini, instance, &(info.fxList), NULL);
	self->angleFX.push_back(info);
}

//-------------------------------------------------------------------------------------------------
// Retail 0x002A4190 held this symbol until 2026-09-16, when the table it adds
// turned out to be the RubbleRise one at 0x010C2AB0. This copy is the Zero
// Hour source and its own retail address is not known yet.
// ?buildFieldParse@StructureToppleUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z present-unmatched
/*static*/ void StructureToppleUpdateModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "MinToppleDelay",						INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_minToppleDelay ) },
		{ "MaxToppleDelay",						INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_maxToppleDelay ) },
		{ "MinToppleBurstDelay",			INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_minToppleBurstDelay ) },
		{ "MaxToppleBurstDelay",			INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_maxToppleBurstDelay ) },
		{ "StructuralIntegrity",			INI::parseReal,										NULL, offsetof( StructureToppleUpdateModuleData, m_structuralIntegrity ) },
		{ "StructuralDecay",					INI::parseReal,										NULL, offsetof( StructureToppleUpdateModuleData, m_structuralDecay ) },
		{ "DamageFXTypes",						INI::parseDamageTypeFlags,				NULL, offsetof( StructureToppleUpdateModuleData, m_damageFXTypes ) },
		{ "TopplingFX",								INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleFXList ) },
		{ "ToppleDelayFX",						INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleDelayFXList ) },
		{ "ToppleStartFX",						INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleStartFXList ) },
		{ "ToppleDoneFX",							INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleDoneFXList ) },
		{ "CrushingFX",								INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_crushingFXList ) },
		{ "CrushingWeaponName",				INI::parseAsciiString,						NULL, offsetof( StructureToppleUpdateModuleData, m_crushingWeaponName ) },
		{ "OCL",											parseOCL,													NULL, 0 },
		{ "AngleFX",									parseAngleFX,											NULL, 0 },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
	p.add(DieMuxData::getFieldParse(), offsetof( StructureToppleUpdateModuleData, m_dieMuxData ));
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;
	Real boxMinorRadius() const;
};

struct BfmeStructureToppleUpdateView
{
	unsigned char m_padding00[4];
	const void *moduleData;
	Object *object;
	unsigned char m_padding0c[0x18];
	UnsignedInt toppleFrame;
	Coord2D toppleDirection;
	Int toppleState;
	Real toppleVelocity;
	Real accumulatedAngle;
	Real structuralIntegrity;
	Real lastCrushedLocation;
	Int nextBurstFrame;
	Coord3D delayBurstLocation;
	Real buildingHeight;
};

struct BfmeStructureToppleModuleDataView
{
	unsigned char m_padding00[0x34];
	Int minToppleDelay;
	Int maxToppleDelay;
	unsigned char m_padding3c[0x28];
	Int minToppleBurstDelay;
	Int maxToppleBurstDelay;
	unsigned char m_padding6c[0x48];
	Real toppleAngle;
};

struct BfmeStructureToppleDamageInfoView
{
	unsigned char m_padding00[8];
	Int sourceID;
};

struct BfmeStructureToppleGameLogicView
{
	unsigned char m_padding00[0x3c];
	UnsignedInt frame;
};

struct BfmeStructureToppleObjectView
{
	unsigned char m_padding00[0x38];
	Coord3D position;
	Real orientation;
	unsigned char m_padding48[0x64];
	BfmeGeometryInfo geometry;
};

class BfmeStructureToppleScriptEngineView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50();
	virtual void adjustToppleDirection(Object *, Coord2D *);
};

class BfmeStructureToppleTerrainView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual Real getGroundHeight(Real, Real, Coord3D *) const;
};

class BfmeStructureToppleGameLogicCall
{
public:
	Object *findObjectByID(Int);
};

class BfmeStructureToppleCoord2DCall
{
public:
	Real toAngle() const;
};

class BfmeStructureToppleUpdateCall
{
public:
	void doToppleStartFX(Object *, const DamageInfo *);
	void setWakeFrame(Object *, UpdateSleepTime);
};

extern Int bfmeStructureToppleRandom(Int, Int, char *, Int);
extern Real bfmeStructureToppleRandomReal(Real, Real, char *, Int);
extern Real bfmeStructureToppleNormalizeAngle(Real);

extern const float g_01075954;

void StructureToppleUpdate::beginStructureTopple(const DamageInfo *damageInfo)
{
	BfmeStructureToppleUpdateView *self =
		(BfmeStructureToppleUpdateView *)this;
	const BfmeStructureToppleModuleDataView *d =
		(const BfmeStructureToppleModuleDataView *)self->moduleData;

	if (d != 0)
	{
		UnsignedInt now =
			((BfmeStructureToppleGameLogicView *)TheGameLogic)->frame;
		self->toppleFrame = now + bfmeStructureToppleRandom(
			d->minToppleDelay, d->maxToppleDelay,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp",
			135);

		Object *attacker =
			((BfmeStructureToppleGameLogicCall *)TheGameLogic)->findObjectByID(
				((const BfmeStructureToppleDamageInfoView *)damageInfo)->sourceID);
		Object *building = self->object;
		BfmeStructureToppleObjectView *buildingView =
			(BfmeStructureToppleObjectView *)building;
		Real toppleAngle;

		if (d->toppleAngle != -9.876540184020996f)
		{
			toppleAngle = d->toppleAngle;
			toppleAngle *= *(volatile const Real *)&g_01075954;
			toppleAngle += buildingView->orientation;
			if (bfmeStructureToppleRandom(0, 2,
				(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp",
				145) < 1)
				toppleAngle += 2 * 3.14159265359f;
			toppleAngle = bfmeStructureToppleNormalizeAngle(toppleAngle);
		}
		else if (attacker == 0)
		{
			toppleAngle = bfmeStructureToppleRandomReal(
				0.0f, 2 * 3.14159265359f,
				(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp",
				151);
		}
		else
		{
			const Coord3D *attackerPos =
				&((BfmeStructureToppleObjectView *)attacker)->position;
			const Coord3D *buildingPos = &buildingView->position;
			self->toppleDirection.x = buildingPos->x - attackerPos->x;
			self->toppleDirection.y = buildingPos->y - attackerPos->y;
			toppleAngle =
				((const BfmeStructureToppleCoord2DCall *)&self->toppleDirection)->toAngle();
			toppleAngle += bfmeStructureToppleRandomReal(
				-3.14159265359f / 8, 3.14159265359f / 8,
				(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp",
				164);
		}

		self->toppleDirection.x = Cos(toppleAngle);
		self->toppleDirection.y = Sin(toppleAngle);
		((BfmeStructureToppleScriptEngineView *)TheScriptEngine)->
			adjustToppleDirection(self->object, &self->toppleDirection);

		Real majorRadius = buildingView->geometry.boxMajorRadius();
		Real minorRadius = buildingView->geometry.boxMinorRadius();
		Real averageRadius = (majorRadius + minorRadius) / 2;
		Real explosionRadius = averageRadius * *(const double *)0x010af378;
		self->delayBurstLocation.x = buildingView->position.x +
			explosionRadius * Cos(toppleAngle);
		self->delayBurstLocation.y = buildingView->position.y +
			explosionRadius * Sin(toppleAngle);
		self->delayBurstLocation.z =
			((BfmeStructureToppleTerrainView *)TheTerrainLogic)->getGroundHeight(
				self->delayBurstLocation.x, self->delayBurstLocation.y, 0);

		((BfmeStructureToppleUpdateCall *)this)->doToppleStartFX(
			building, damageInfo);
		self->nextBurstFrame = now + bfmeStructureToppleRandom(
			d->minToppleBurstDelay, d->maxToppleBurstDelay,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp",
			181);

		self->toppleState = 1;
		((BfmeStructureToppleUpdateCall *)this)->setWakeFrame(
			self->object, UPDATE_SLEEP_NONE);
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/StructureToppleUpdate_onDie_Thunk.cpp
// ?onDie@StructureToppleUpdate@@UAEXPBVDamageInfo@@@Z present-unmatched
void StructureToppleUpdate::onDie( const DamageInfo *damageInfo )
{
	const StructureToppleUpdateModuleData* d = getStructureToppleUpdateModuleData();
	if (!d->m_dieMuxData.isDieApplicable(getObject(), damageInfo))
		return;

	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if (ai)
		ai->markAsDead();

	// Deselect the object for all players.
	TheGameLogic->deselectObject(getObject(), PLAYERMASK_ALL, TRUE);

	beginStructureTopple(damageInfo);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?update@StructureToppleUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Body in StructureToppleUpdate_update.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doToppleDoneStuff@StructureToppleUpdate@@IAEXXZ
void StructureToppleUpdate::doToppleDoneStuff() 
{
	static NameKeyType key_BoneFXUpdate = NAMEKEY("BoneFXUpdate");
	BoneFXUpdate *bfxu = (BoneFXUpdate *)getObject()->findUpdateModule(key_BoneFXUpdate);
	if (bfxu != NULL) {
		bfxu->stopAllBoneFX();
	}

	Object *building = getObject();

	Real origAngle = building->getOrientation();
	building->setOrientation(origAngle);

	Real toppleAngle = m_toppleDirection.toAngle();

	Matrix3D xfrm = *building->getTransformMatrix();
	xfrm.In_Place_Pre_Rotate_Z(toppleAngle-origAngle);
	building->setTransformMatrix(&xfrm);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doAngleFX@StructureToppleUpdate@@IAEXMM@Z present-unmatched
void StructureToppleUpdate::doAngleFX(Real curAngle, Real newAngle) 
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	for (std::vector<AngleFXInfo>::const_iterator it = d->angleFX.begin(); it != d->angleFX.end(); ++it)
	{
		if ((it->angle > curAngle) && (it->angle <= newAngle)) 
		{
			if( lastDamageInfo == NULL || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
				FXList::doFXObj(it->fxList, getObject());
		}
	}

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// theta is the angle of the building with respect to the ground.
struct BfmeStructureToppleModuleData
{
	unsigned char padding[0x60];
	AsciiString crushingWeaponName;
};

void StructureToppleUpdate::applyCrushingDamage(Real theta) 
{
//	static const Real THETA_CEILING = PI/8; // This weapon won't do any damage until theta is less than this value.
	static const Real THETA_CEILING = PI/6; // This weapon won't do any damage until theta is less than this value.
	static const Real WEAPON_SPACING_PERPENDICULAR = 25;	// The spacing between weapon firing locations,
																												// distance is perpendicular to the direction the
																												// building is falling in.

	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	Object *building = getObject();
	Real orientationAngle;
	Real toppleAngle;
	Real angle;
	Real minorComponent;
	Real majorComponent;
	BfmeGeometryInfo *geometry;
	Real cosine;
	Real sine;
	Coord3D temp3D;
	Real facingWidth;
	const WeaponTemplate* wt;
	Real maxDistance;
	Real jcos;
	Real jsin;
	Real j;
	if (theta > THETA_CEILING) {
		return;
	}

	building = getObject();
	orientationAngle = building->getOrientation();
	toppleAngle = m_toppleDirection.toAngle();

	// Figure out the width of the projection of the boundary of the building along the topple direction.
	// Do this because the amount of ground that is affected will be different if the building falls
	// in different orientations.
	angle = orientationAngle - toppleAngle;
	geometry = reinterpret_cast<BfmeGeometryInfo *>(reinterpret_cast<char *>(building) + 0xac);
	cosine = Cos(angle);
	minorComponent = cosine * geometry->boxMinorRadius();
	sine = Sin(angle);
	majorComponent = sine * geometry->boxMajorRadius();

	temp3D.x = majorComponent;
	temp3D.y = minorComponent;
	temp3D.z = 0.0f;
	
	facingWidth = temp3D.length() / 2;

	// Get the crushing weapon.
	wt = TheWeaponStore->findWeaponTemplate(
		reinterpret_cast<BfmeStructureToppleModuleData *>(const_cast<StructureToppleUpdateModuleData *>(d))->crushingWeaponName);
	if (wt == NULL) {
		return;
	}

	// The furthest away from the base of the building to explode on.
	maxDistance = m_buildingHeight * (1.0 - Sin(theta));

	/*
	 * Fire explosions at regular intervals across the area that the building is currently
	 * crushing.  The explosions occur across the face and along the length of the building.
	 */
//	Coord3D target;
	for (j = m_lastCrushedLocation; j < maxDistance; j += WEAPON_SPACING_PERPENDICULAR) {
		jcos = j * Cos(toppleAngle);
		jsin = j * Sin(toppleAngle);
		doDamageLine(building, wt, jcos, jsin, facingWidth, toppleAngle);
	}


	jcos = maxDistance * Cos(toppleAngle);
	jsin = maxDistance * Sin(toppleAngle);
	doDamageLine(building, wt, jcos, jsin, facingWidth, toppleAngle);

	m_lastCrushedLocation = j;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doDamageLine@StructureToppleUpdate@@IAEXPAVObject@@PBVWeaponTemplate@@MMMM@Z
// Body in StructureToppleUpdate_doDamageLine.asm (exact 523B retail).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doToppleStartFX@StructureToppleUpdate@@IAEXPAVObject@@PBVDamageInfo@@@Z present-unmatched
void StructureToppleUpdate::doToppleStartFX(Object *building, const DamageInfo *damageInfo) 
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	if( lastDamageInfo == NULL || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )	
		FXList::doFXPos(d->m_toppleStartFXList, building->getPosition());

	doPhaseStuff(STPHASE_INITIAL, building->getPosition());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doToppleDelayBurstFX@StructureToppleUpdate@@IAEXXZ present-unmatched
void StructureToppleUpdate::doToppleDelayBurstFX() 
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	DEBUG_LOG(("Doing topple delay burst on frame %d\n", TheGameLogic->getFrame()));
	if( lastDamageInfo == NULL || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
		FXList::doFXPos(d->m_toppleDelayFXList, &m_delayBurstLocation);

	Object *building = getObject();
	Drawable *drawable = building->getDrawable();

	if( lastDamageInfo == NULL || getDamageTypeFlag( d->m_damageFXTypes, lastDamageInfo->in.m_damageType ) )
	{

		for (std::vector<FXBoneInfo>::const_iterator it = d->fxbones.begin(); it != d->fxbones.end(); ++it)
		{
			ParticleSystem *sys = TheParticleSystemManager->createParticleSystem(it->particleSystemTemplate);
			if (sys != NULL) 
			{
				Coord3D pos;
				if (drawable->getPristineBonePositions(it->boneName.str(), 0, &pos, NULL, 1) == 1) 
				{
					// got the bone position...
					sys->setPosition(&pos);

					// Attatch it to the object...
					sys->attachToDrawable(drawable);
				}
			}
		}
	}

	doPhaseStuff(STPHASE_DELAY, &m_delayBurstLocation);

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
inline Bool inList(Int value, Int count, const Int idxList[])
{
	for (Int j = 0; j < count; ++j)
	{
		if (idxList[j] == value)
			return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static void buildStructureToppleRandomIndexList(Int range, Int count, Int idxList[])
{
	for (Int i = 0; i < count; ++i)
	{
		Int idx;
		do
		{
			#line 536 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"
			idx = GameLogicRandomValue(0, range-1);
		} 
		while (inList(idx, i, idxList));
		idxList[i] = idx;
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
struct StructureToppleBfmeModuleDataLayout
{
	unsigned char m_beforeOcls[0x6c];
	OCLVec m_ocls[ST_PHASE_COUNT];
	UnsignedInt m_oclCount[ST_PHASE_COUNT];
};

class StructureCollapseOCLShim
{
public:
	Object *create(const Object *primaryObject, const Coord3D *primaryPosition,
		const Coord3D *secondaryPosition, UnsignedInt lifetimeFrames) const;
};

void StructureToppleUpdate::doPhaseStuff(StructureTopplePhaseType stphase, const Coord3D *target)
{
	const StructureToppleBfmeModuleDataLayout *d =
		reinterpret_cast<const StructureToppleBfmeModuleDataLayout *>(
			getStructureToppleUpdateModuleData());
	Int i, idx, count, listSize;
	Int idxList[MAX_IDX];

	listSize = d->m_ocls[stphase].size();
	if (listSize > 0)
	{
		count = d->m_oclCount[stphase];
		buildStructureToppleRandomIndexList(listSize, count, idxList);
		for (i = 0; i < count; ++i)
		{
			idx = idxList[i];
			const OCLVec& v = d->m_ocls[stphase];
			DEBUG_ASSERTCRASH(idx>=0&&idx<v.size(),("bad idx"));
			const ObjectCreationList* ocl = v[idx];
			if (ocl != NULL)
				reinterpret_cast<const StructureCollapseOCLShim *>(ocl)->create(
					getObject(), target, NULL, 0);
		}
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@StructureToppleUpdate@@MAEXPAVXfer@@@Z present-unmatched
void StructureToppleUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@StructureToppleUpdate@@MAEXPAVXfer@@@Z present-unmatched
void StructureToppleUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// topple frame
	xfer->xferUnsignedInt( &m_toppleFrame );

	// topple direction
	xfer->xferCoord2D( &m_toppleDirection );

	// topple state
	xfer->xferUser( &m_toppleState, sizeof( StructureToppleStateType ) );

	// topple velocity
	xfer->xferReal( &m_toppleVelocity );

	// accumulated angle
	xfer->xferReal( &m_accumulatedAngle );

	// structural integrity
	xfer->xferReal( &m_structuralIntegrity );

	// last crushed location
	xfer->xferReal( &m_lastCrushedLocation );

	// next burst frame
	xfer->xferInt( &m_nextBurstFrame );

	// delay burst location
	xfer->xferCoord3D( &m_delayBurstLocation );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@StructureToppleUpdate@@MAEXXZ present-unmatched
void StructureToppleUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
