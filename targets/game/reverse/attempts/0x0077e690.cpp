// ?doDrawModule@W3DTankDraw@@UAEXPBVMatrix3D@@@Z
// partial score=0.9923857868020305 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// RVA 0077E690, 788 bytes. Resumed from the bank, retaining its complete body.
// Identity: landed 0077F050 constructor installs VA01125AB0; slot9 routes
// through ILT00010A9B here. Hub 0077B3F0 proves the unadjusted receiver and
// incoming Matrix3D pointer for the final draw call (see analyst report).
// Improvements: inline freezePair receiver lifetime; module-data accessors
// reload BFME offset4 rather than the ZH Module offset8; null-locomotor merge;
// guard-scoped tread pointer. Last residue: EBX/EBP swap in six particle-copy
// operand bytes (+14E +153 +165 +16B +19E +1A4).
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
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
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

// Target: ?doDrawModule@W3DTankDraw@@UAEXPBVMatrix3D@@@Z
//
// BFME's View vtable carries 5 more slots than the vendored ZH header before
// isCameraMovementFinished/isTimeFrozen (retail calls [vt+0x74]/[vt+0xd4];
// the ZH-header slots would be 0x60/0xc0). Confirmed directly: the base View
// class's own default bodies -- mov al,1/ret (isCameraMovementFinished
// returns TRUE) and xor al,al/ret (isTimeFrozen returns false) -- sit at
// exactly RVA 0x0045BB00 and 0x0045BC80, which are slots 29 and 53 of the
// matched View vtable at VA 0x010F6940 (Code/GameEngine/Source/GameClient/
// ViewConstructorBfme.cpp). Route both calls through a slot-padded shim
// instead of the real View class so the compiler emits the retail offsets.
struct BfmeViewThunk
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
	virtual Bool isCameraMovementFinished() = 0;  // retail slot 29 (+0x74)
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
	virtual Bool isTimeFrozen() = 0;  // retail slot 53 (+0xd4)
};

// BFME's ScriptEngine carries one extra Bool freeze predicate the ZH reference
// header doesn't declare, read through a real out-of-line call (not inlined --
// retail's call site is a genuine `call`, not a folded field load) at
// this+0x17624. The body is already landed as Rva00336EF0ByteField::get()
// (Code/GameEngine/Source/Common/DispByteFieldGetters.cpp, RVA 0x00336EF0:
// mov al,[ecx+0x17624]; ret), but THIS caller's retail bytes route through the
// incremental-link ILT stub at RVA 0x00027318 rather than that real address
// (the same shape as the ScriptEngine isTimeFrozenDebug/isTimeFrozenScript
// calls just above, both pinned at their own ILT addresses). Give this
// accessor a distinct TU-local name pinned straight at that ILT RVA
// (reverse/symbols.csv) instead of reusing the real symbol, whose matched
// functions.csv row points at the out-of-line body address instead.
class BfmeScriptEngineFreezeExtra
{
public:
	unsigned char get() const;
	char m_lead[0x17624];
	unsigned char m_value;
};

// isTimeFrozenDebug@ScriptEngine and isTimeFrozenScript@ScriptEngine are real
// ZH names already matched to their out-of-line bodies (RVA 0x00336F20 /
// 0x00336F50) elsewhere, so calling them by their real names here would link
// straight to those addresses. This caller's retail bytes instead route
// through the incremental-link ILT stubs at RVA 0x0003F23D / 0x00003783 (the
// same two thunks other already-landed callers use), so give them distinct
// TU-local names pinned at those ILT RVAs instead of reusing the claimed
// symbols.
class BfmeScriptEngineDebugFreezeIlt
{
public:
	Bool isTimeFrozenDebugIlt();
	Bool freezePair();
};
class BfmeScriptEngineScriptFreezeIlt
{
public:
	Bool isTimeFrozenScriptIlt();
};
inline Bool BfmeScriptEngineDebugFreezeIlt::freezePair()
{
	return isTimeFrozenDebugIlt()
		|| reinterpret_cast<BfmeScriptEngineScriptFreezeIlt *>(this)->isTimeFrozenScriptIlt();
}

extern ParticleSystem *emptyParticleSystem(void);

class BfmeTankParticleIlt
{
public:
	void setVelocityMultiplier(const Coord3D *value)
	{
		*(Coord3D *)((char *)this + 0x134) = *value;
	}

	void setBurstCountMultiplier(Real value)
	{
		*(Real *)((char *)this + 0x140) = value;
	}
};

struct BfmeTankParticleHandle
{
	BfmeTankParticleIlt *system;
	void *previous;
	void *next;

	operator bool(void) const
	{
		return system != 0;
	}

	BfmeTankParticleIlt *operator->(void) const
	{
		if (!system)
			return reinterpret_cast<BfmeTankParticleIlt *>(emptyParticleSystem());
		return system;
	}
};

struct BfmeTankModuleDataFields;
struct BfmeTankDrawFields
{
	void *vtable;
	void *moduleData;
	const BfmeTankModuleDataFields *data() const { return reinterpret_cast<const BfmeTankModuleDataFields *>(moduleData); }
	void *drawable;
	unsigned char m_pad00c[0x270];
	BfmeTankParticleHandle treadDebrisLeft;
	BfmeTankParticleHandle treadDebrisRight;
	RenderObjClass *prevRenderObj;
	unsigned char m_treads[0x50];
	int treadCount;
	Coord3D lastDirection;
};

struct BfmeTankModuleDataFields
{
	unsigned char m_pad000[0x164];
	Real treadAnimationRate;
	Real treadPivotSpeedFraction;
	Real treadDriveSpeedFraction;
};

struct BfmeTankDrawableFields
{
	unsigned char m_pad000[0xfc];
	void *object;
};

struct BfmeTankObjectFields
{
	unsigned char m_pad000[0x204];
	void *ai;
	void *required;
};

struct BfmeTankAiFields
{
	unsigned char m_pad000[0x1cc];
	void *locomotor;
};

struct BfmeTankLocomotorFields
{
	unsigned char m_pad000[0xa4];
	int turning;
};

struct BfmeTankTreadScrollFields
{
	Real customUVOffsetX;
	Real customUVOffsetY;
	unsigned char m_pad008[0xc];
};

class BfmeTankObjectHeightIlt
{
public:
	Real get() const;
};

class BfmeTankDrawableHiddenIlt
{
public:
	Bool get() const;
};

void W3DTankDraw::doDrawModule(const Matrix3D* transformMtx)
{
	BfmeTankDrawFields *tank = reinterpret_cast<BfmeTankDrawFields *>(this);

	if (reinterpret_cast<BfmeViewThunk *>(TheTacticalView)->isTimeFrozen()
		&& !reinterpret_cast<BfmeViewThunk *>(TheTacticalView)->isCameraMovementFinished())
		return;
	if (reinterpret_cast<BfmeScriptEngineDebugFreezeIlt *>(TheScriptEngine)->freezePair())
		return;
	if (reinterpret_cast<const BfmeScriptEngineFreezeExtra *>(TheScriptEngine)->get())
		return;

	if (reinterpret_cast<BfmeTankRenderObjectThunk *>(this)->GetRenderObject() == 0)
		return;
	if (reinterpret_cast<BfmeTankRenderObjectThunk *>(this)->GetRenderObject() != tank->prevRenderObj)
	{
		updateTreadObjects();
	}

	BfmeTankDrawableFields *drawable =
		reinterpret_cast<BfmeTankDrawableFields *>(tank->drawable);
	BfmeTankObjectFields *obj =
		reinterpret_cast<BfmeTankObjectFields *>(drawable->object);
	if (obj == 0 || obj->required == 0)
		return;

	BfmeTankObjectHeightIlt *heightObject =
		reinterpret_cast<BfmeTankObjectHeightIlt *>(obj);
	Real debrisSpeed = heightObject->get();
	if (debrisSpeed > *(const Real *)0x0112100C)
	{
		if (!((reinterpret_cast<BfmeTankDrawableHiddenIlt *>(tank->drawable)->get)())
			&& *(unsigned char *)((char *)this + 0x2d) == 0)
		{
			startMoveDebris();
		}
		else
		{
			stopMoveDebris();
		}
	}
	else
	{
		stopMoveDebris();
	}

	Coord3D velocityMultiplier;
	Real speed = (Real)sqrt(debrisSpeed);
	velocityMultiplier.x = speed * *(const Real *)0x0107533C
		+ *(const Real *)0x01075C70;
	if (velocityMultiplier.x > *(const Real *)0x01075334)
		velocityMultiplier.x = 1.0f;
	velocityMultiplier.y = velocityMultiplier.x;
	velocityMultiplier.z = speed + *(const Real *)0x01075C70;
	if (velocityMultiplier.z > *(const Real *)0x01075334)
		velocityMultiplier.z = 1.0f;

	if (tank->treadDebrisLeft)
	{
		tank->treadDebrisLeft->setVelocityMultiplier(&velocityMultiplier);
		tank->treadDebrisLeft->setBurstCountMultiplier(velocityMultiplier.z);
	}
	if (tank->treadDebrisRight)
	{
		tank->treadDebrisRight->setVelocityMultiplier(&velocityMultiplier);
		tank->treadDebrisRight->setBurstCountMultiplier(velocityMultiplier.z);
	}

	if (tank->treadCount)
	{
		BfmeTankAiFields *ai = reinterpret_cast<BfmeTankAiFields *>(obj->ai);
		BfmeTankLocomotorFields *locomotor;
		if (ai != 0)
			locomotor = reinterpret_cast<BfmeTankLocomotorFields *>(ai->locomotor);
		else
			locomotor = 0;
		// Keep the independently witnessed null-result merge at retail +1D8..+1E4.
		_ReadWriteBarrier();
		if (locomotor == 0)
			return;
		const BfmeTankModuleDataFields *moduleData =
			reinterpret_cast<const BfmeTankModuleDataFields *>(tank->moduleData);
		int turning = locomotor->turning;
		Real treadScrollSpeed = moduleData->treadAnimationRate;
		Real maxSpeed = reinterpret_cast<AIUpdateInterface *>(ai)->getCurLocomotorSpeed();

		if (turning != 0
		&& (heightObject->get() / maxSpeed < tank->data()->treadPivotSpeedFraction))
		{
			Coord3D direction;
			reinterpret_cast<Thing *>(obj)->getUnitDirectionVector2D(direction);
			Real angleToGoal = direction.x * tank->lastDirection.x
				+ direction.y * tank->lastDirection.y;
			if (fabs(*(const Real *)0x01075334 - angleToGoal) > *(const Real *)0x0112100C)
			{
				if (turning == -1)
					updateTreadPositions(-treadScrollSpeed);
				else
					updateTreadPositions(treadScrollSpeed);
			}
			tank->lastDirection = direction;
		}
		else if (heightObject->get() / maxSpeed >= tank->data()->treadDriveSpeedFraction)
		{
			BfmeTankTreadScrollFields *tread;
			int i = 0;
			if (i < tank->treadCount) {
				tread = reinterpret_cast<BfmeTankTreadScrollFields *>((char *)this + 0x2a4);
				do
				{
				Real offset = tread->customUVOffsetX - treadScrollSpeed;
				offset = offset - floorf(offset);
				tread->customUVOffsetX = offset;
				tread->customUVOffsetY = 0.0f;
				++tread;
			} while (++i < tank->treadCount);
			}
		}
	}

	W3DModelDraw::doDrawModule(transformMtx);
}

