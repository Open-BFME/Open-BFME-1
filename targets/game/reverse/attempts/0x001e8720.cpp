// ?reloadWithBonus@Weapon@@IAEXPBVObject@@ABVWeaponBonus@@_N@Z
// partial score=0.9596 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/weapon /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: Weapon.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Weapon descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
// This TU calls the independently witnessed matrix-copy variant at 0x132200.
// Rename the reference header declaration locally; the published setter is a different body.
#define setTransformMatrix rva00132200
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#undef setTransformMatrix

#define DEFINE_DEATH_NAMES
#define DEFINE_WEAPONBONUSCONDITION_NAMES
#define DEFINE_WEAPONBONUSFIELD_NAMES
#define DEFINE_WEAPONCOLLIDEMASK_NAMES
#define DEFINE_WEAPONAFFECTSMASK_NAMES
#define DEFINE_WEAPONRELOAD_NAMES
#define DEFINE_WEAPONPREFIRE_NAMES

#include "Common/CRC.h"
#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GameState.h"
#include "Common/INI.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
 
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ParticleSys.h"

#include "GameLogic/Damage.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/LaserUpdate.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/ProjectileStreamUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/TerrainLogic.h"


struct BfmeWeaponTemplateFireTimingView
{
	unsigned char m_prefix[0x4b0];
	Int m_minClipReloadTime;
	Int m_maxClipReloadTime;
	Int m_minDelayBetweenShots;
	Int m_maxDelayBetweenShots;
};

Int WeaponTemplate::getClipReloadTime(const WeaponBonus& bonus) const 
{
	const BfmeWeaponTemplateFireTimingView *self =
		(const BfmeWeaponTemplateFireTimingView *)this;
	Int reloadTime;
	if (self->m_minClipReloadTime == self->m_maxClipReloadTime)
		reloadTime = self->m_minClipReloadTime;
	else
		reloadTime = GetGameLogicRandomValue(
			self->m_minClipReloadTime,
			self->m_maxClipReloadTime,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Weapon.cpp",
			863);

	reloadTime -= reloadTime % 3;
	return fast_float2long_round((Real)floor((double)(
		(Real)reloadTime / bonus.getField(WeaponBonus::RATE_OF_FIRE))));
}


// BFME reload view: offsets witnessed directly by 001E8720 and 001E8670.
// The reference Weapon declaration remains canonical; this local view makes no
// claim that its older layout matches BFME's runtime storage.
class BfmeHostERT { public: char bfmeQueryERT(); };
class Rva001EB140 { public: bool get(); };
class Rva001E8670Weapon { public: void rebuildScatterTargets(); };
struct Rva001E8720Template {
 char at00[0x4ac];
 int at4ac;
 char at4b0[0x38];
 BfmeHostERT at4e8;
};
class Rva001E8720Contain {
public:
 virtual void unused00();
 virtual void unused01();
 virtual void unused02();
 virtual void unused03();
 virtual void unused04();
 virtual void unused05();
 virtual void unused06();
 virtual void unused07();
 virtual void unused08();
 virtual void unused09();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual void unused16();
 virtual void unused17();
 virtual void unused18();
 virtual void unused19();
 virtual void unused20();
 virtual void unused21();
 virtual void unused22();
 virtual void unused23();
 virtual void unused24();
 virtual void unused25();
 virtual void unused26();
 virtual void unused27();
 virtual void unused28();
 virtual void unused29();
 virtual void unused30();
 virtual void unused31();
 virtual void unused32();
 virtual void unused33();
 virtual void unused34();
 virtual void unused35();
 virtual void unused36();
 virtual void unused37();
 virtual void unused38();
 virtual void unused39();
 virtual void unused40();
 virtual void unused41();
 virtual void unused42();
 virtual void unused43();
 virtual void unused44();
 virtual void unused45();
 virtual void unused46();
 virtual void unused47();
 virtual void unused48();
 virtual void unused49();
 virtual void unused50();
 virtual void unused51();
 virtual void unused52();
 virtual void unused53();
 virtual void unused54();
 virtual void unused55();
 virtual void unused56();
 virtual void unused57();
 virtual void unused58();
 virtual void unused59();
 virtual void unused60();
 virtual void unused61();
 virtual void unused62();
 virtual void unused63();
 virtual unsigned at100(BfmeHostERT*);
};
struct Rva001E8720Object {
 char at00[0x1fc];
 Rva001E8720Contain* at1fc;
 Rva001E8720Contain* contain() const { return at1fc; }
};
void j_0001f253();
class Rva001E8720Lookup {};
typedef Object* (Rva001E8720Lookup::*Rva001E8720LookupCall)(ObjectID);
typedef char Rva001E8720LookupSize[sizeof(Rva001E8720LookupCall)==4 ? 1 : -1];
struct Rva001E8720Weapon {
 int at00;
 const Rva001E8720Template* at04;
 ObjectID at08;
 int at0c;
 int at10;
 unsigned at14,at18;
 char at1c[12];
 unsigned at28;
 __forceinline unsigned count() const {
  if(const_cast<BfmeHostERT*>(&at04->at4e8)->bfmeQueryERT()) {
   union { void (*raw)(); Rva001E8720LookupCall member; } call;
   call.raw=j_0001f253;
   Object *o=(((Rva001E8720Lookup*)TheGameLogic)->*call.member)(at08);
   Rva001E8720Contain *contain=o?((Rva001E8720Object*)o)->contain():0;
   if(contain) return contain->at100(const_cast<BfmeHostERT*>(&at04->at4e8));
  }
  return at14;
 }
 void status(int s) { if(at10!=s) at10=s; }
};
void Weapon::reloadWithBonus(const Object *sourceObj, const WeaponBonus& bonus, Bool loadInstantly)
{
 Rva001E8720Weapon *w=(Rva001E8720Weapon*)this;
 if(w->at04->at4ac>0 && w->count()==w->at04->at4ac && !((Rva001EB140*)((char*)sourceObj+0x264))->get()) return;
 w->at14=w->at04->at4ac;
 if(w->count()<=0) w->at14=0x7fffffff;
 w->status(3);
 Real reloadTime=loadInstantly?0:((const WeaponTemplate*)w->at04)->getClipReloadTime(bonus);
 w->at28=*(unsigned*)((char*)TheGameLogic+0x3c);
 w->at18=w->at28+reloadTime;
 if(((Rva001EB140*)((char*)sourceObj+0x264))->get()) {
  for(int slot=0;slot<4;++slot) {
   Rva001E8720Weapon *weapon=(Rva001E8720Weapon*)((const WeaponSet*)((char*)sourceObj+0x264))->getWeaponInWeaponSlot((WeaponSlotType)slot);
   if(weapon) {
    weapon->at18=w->at18;
    weapon->status(3);
   }
  }
 }
 ((Rva001E8670Weapon*)this)->rebuildScatterTargets();
}

