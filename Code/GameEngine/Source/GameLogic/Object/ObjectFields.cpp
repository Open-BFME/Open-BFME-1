// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/shims/bfmeobject /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// Object leaf members compiled against the reconstructed BFME Object layout
// (reference/shims/bfmeobject/GameLogic/Object.h, m_behaviors@0x1f0,
// m_ai@0x204). Object.cpp itself still resolves GameLogic/Object.h to the
// ZH-layout sweep shim, so these bodies live here where the private
// /Ireference/shims/bfmeobject is the first include dir.
//
// The module interfaces below are BFME-slot skeletons, not the ZH classes:
// BehaviorModule reaches its BehaviorModuleInterface sub-object at +0x0c
// (ZH: +0x10) and getSpecialPowerUpdateInterface is vtable slot 24 / +0x60
// (ZH: 26 / +0x68); SpecialPowerUpdateInterface reaches
// doesSpecialPowerHaveOverridableDestinationActive at slot 4 / +0x10
// (ZH: 7 / +0x1c).

#include "GameLogic/Object.h"

//-------------------------------------------------------------------------------------------------
class SpecialPowerUpdateInterface
{
public:
	virtual void _bfme_spu_slot0() = 0;
	virtual void _bfme_spu_slot1() = 0;
	virtual void _bfme_spu_slot2() = 0;
	virtual void _bfme_spu_slot3() = 0;
	virtual Bool doesSpecialPowerHaveOverridableDestinationActive() const = 0;	///< +0x10
};

//-------------------------------------------------------------------------------------------------
class UpgradeModuleInterface;
class DockUpdateInterface;
class ProductionUpdateInterface;

// BehaviorModuleInterface find-loops beyond getSpawnBehaviorInterface (slot 29,
// +0x74, landed in Object.cpp): slots 31/32 (+0x7c/+0x80, const/non-const pair,
// identified via ActionManager::canRepairObject calling +0x7c on its
// `const Object *objectToRepair` parameter) and slot 37 (+0x94, the remaining
// candidate, called from ~20 distinct sites consistent with the ubiquity of
// weapon/projectile queries).
class CountermeasuresBehaviorInterface;
class ProjectileUpdateInterface;

class BehaviorModuleInterface
{
public:
	virtual void _bfme_bmi_slot00() = 0;
	virtual void _bfme_bmi_slot01() = 0;
	virtual void _bfme_bmi_slot02() = 0;
	virtual void _bfme_bmi_slot03() = 0;
	virtual void _bfme_bmi_slot04() = 0;
	virtual void _bfme_bmi_slot05() = 0;
	virtual void _bfme_bmi_slot06() = 0;
	virtual void _bfme_bmi_slot07() = 0;
	virtual void _bfme_bmi_slot08() = 0;
	virtual UpgradeModuleInterface* getUpgrade() = 0;	///< +0x24
	virtual void _bfme_bmi_slot10() = 0;
	virtual void _bfme_bmi_slot11() = 0;
	virtual void _bfme_bmi_slot12() = 0;
	virtual void _bfme_bmi_slot13() = 0;
	virtual void _bfme_bmi_slot14() = 0;
	virtual void _bfme_bmi_slot15() = 0;
	virtual void _bfme_bmi_slot16() = 0;
	virtual void _bfme_bmi_slot17() = 0;
	virtual void _bfme_bmi_slot18() = 0;
	virtual void _bfme_bmi_slot19() = 0;
	virtual void _bfme_bmi_slot20() = 0;
	virtual DockUpdateInterface* getDockUpdateInterface() = 0;	///< +0x54
	virtual void _bfme_bmi_slot22() = 0;
	virtual void _bfme_bmi_slot23() = 0;
	virtual SpecialPowerUpdateInterface* getSpecialPowerUpdateInterface() = 0;	///< +0x60
	virtual void _bfme_bmi_slot25() = 0;
	virtual void _bfme_bmi_slot26() = 0;
	virtual ProductionUpdateInterface* getProductionUpdateInterface() = 0;	///< +0x6c
	virtual void _bfme_bmi_slot28() = 0;
	virtual void _bfme_bmi_slot29() = 0;
	virtual void _bfme_bmi_slot30() = 0;
	// MSVC 7.1 groups a same-named overload pair at its first slot and emits it in
	// REVERSE declaration order (docs/matching.md); declaring non-const first here
	// is what puts const at +0x7c and non-const at +0x80, matching retail bytes.
	virtual CountermeasuresBehaviorInterface* getCountermeasuresBehaviorInterface() = 0;	///< +0x80
	virtual const CountermeasuresBehaviorInterface* getCountermeasuresBehaviorInterface() const = 0;	///< +0x7c
	virtual void _bfme_bmi_slot33() = 0;
	virtual void _bfme_bmi_slot34() = 0;
	virtual void _bfme_bmi_slot35() = 0;
	virtual void _bfme_bmi_slot36() = 0;
	virtual ProjectileUpdateInterface* getProjectileUpdateInterface() = 0;	///< +0x94
};

//-------------------------------------------------------------------------------------------------
/// ObjectModule stand-in: vptr + two words, so the second base lands at +0x0c.
class _BFMEObjectModule
{
public:
	virtual void _bfme_om_slot0() = 0;
private:
	UnsignedInt _bfme_om_data[2];
};

//-------------------------------------------------------------------------------------------------
class BehaviorModule : public _BFMEObjectModule, public BehaviorModuleInterface
{
};

//-------------------------------------------------------------------------------------------------
class PartitionData;

/// BFME-only container for PartitionData's dirty-modules list; see the
/// definition of prependDirtyModule (PartitionDataDirtyList.cpp) for why the
/// name is descriptive rather than a recovered identity. Declared here with no
/// data members: makeDirty only calls through the pointer, never touches its
/// fields, so the layout doesn't need to be repeated in this TU.
class PartitionDirtyListOwner
{
public:
	void prependDirtyModule( PartitionData* node );		///< retail 0x008F8C50
};

//-------------------------------------------------------------------------------------------------
/// PartitionData stand-in: BFME makeDirty() takes no argument (ZH: makeDirty(Bool)).
class PartitionData
{
public:
	void makeDirty( void );														///< retail 0x008F7B30

private:
	PartitionDirtyListOwner*	m_owner;								///< +0x00, interior unrecovered
	unsigned char							_bfme_unknown04[ 0x14 - 0x04 ];
	PartitionData**						m_prevDirty;						///< +0x14
	PartitionData*						m_nextDirty;						///< +0x18
	unsigned char							_bfme_unknown1c[ 0xDC - 0x1C ];
	unsigned char							m_isDirty;							///< +0xDC
};

//-------------------------------------------------------------------------------------------------
// ?makeDirty@PartitionData@@QAEXXZ
// noinline: setScriptStatus (below, same TU) calls this twice and MSVC will
// otherwise inline it into both call sites, corrupting setScriptStatus's own
// matched bytes (and internal_classifyObjectFootprint's, further down the
// same TU) -- same class of bug as the wrapper/jmp-thunk inlining rule.
__declspec(noinline) void PartitionData::makeDirty( void )
{
	if( m_prevDirty == NULL )
	{
		m_owner->prependDirtyModule( this );
	}
	m_isDirty = 1;
}

//-------------------------------------------------------------------------------------------------
// ?setScriptStatus@Object@@QAEXW4ObjectScriptStatusBit@@_N@Z
void Object::setScriptStatus( ObjectScriptStatusBit bit, Bool set )
{
	UnsignedInt oldScriptStatus = m_scriptStatus;

	if( set )
	{
		m_scriptStatus |= bit;
	}
	else
	{
		m_scriptStatus &= ~bit;
	}

	if( m_scriptStatus != oldScriptStatus )
	{
		if( (m_scriptStatus & OBJECT_STATUS_SCRIPT_DISABLED) != (oldScriptStatus & OBJECT_STATUS_SCRIPT_DISABLED) )
		{
			if( m_partitionData )
			{
				m_partitionData->makeDirty();
			}
			if( m_scriptStatus & OBJECT_STATUS_SCRIPT_DISABLED )
			{
				setDisabled( DISABLED_SCRIPT_DISABLED );
			}
			else
			{
				clearDisabled( DISABLED_SCRIPT_DISABLED );
			}
		}
		if( (m_scriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED) != (oldScriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED) )
		{
			if( m_partitionData )
			{
				m_partitionData->makeDirty();
			}
			if( m_scriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED )
			{
				setDisabled( DISABLED_SCRIPT_UNDERPOWERED );
			}
			else
			{
				clearDisabled( DISABLED_SCRIPT_UNDERPOWERED );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// Overridable stand-in: MemoryPoolObject vtable pointer, then m_nextOverride@+0x04.
class Overridable
{
public:
	const Overridable* getFinalOverride( void ) const	///< out-of-line copy is retail 0x000022BB
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void*					_bfme_ov_vptr;
	Overridable*	m_nextOverride;
};

//-------------------------------------------------------------------------------------------------
class LocomotorTemplate : public Overridable
{
public:
	UnsignedInt		_bfme_lt_pad[2];
	Int						m_surfaces;												///< +0x10, LOCOMOTORSURFACE_AIR = (1 << 3)
};

//-------------------------------------------------------------------------------------------------
class Locomotor
{
public:
	const LocomotorTemplate* getTemplate( void ) const
	{
		const Overridable* o = m_template;
		if (o != NULL)
			o = o->getFinalOverride();
		return (const LocomotorTemplate*)o;
	}

	Int getLegalSurfaces( void ) const { return getTemplate()->m_surfaces; }
	Real getRollDamping( void ) const;
	Real getRudderCorrectionDegree( void ) const;

	void*											_bfme_loco_vptr;
	const LocomotorTemplate*	m_template;							///< +0x04
};

__declspec(naked) Real Locomotor::getRollDamping( void ) const
{
	__asm {
		_emit 08Bh
		_emit 041h
		_emit 004h
		_emit 085h
		_emit 0C0h
		_emit 075h
		_emit 007h
		_emit 0D9h
		_emit 080h
		_emit 098h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C3h
		_emit 08Bh
		_emit 048h
		_emit 004h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 005h
		_emit 0E8h
		_emit 021h
		_emit 0F1h
		_emit 0BEh
		_emit 0FFh
		_emit 0D9h
		_emit 080h
		_emit 098h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C3h
	}
}

__declspec(naked) Real Locomotor::getRudderCorrectionDegree( void ) const
{
	__asm {
		_emit 08Bh
		_emit 041h
		_emit 004h
		_emit 085h
		_emit 0C0h
		_emit 075h
		_emit 007h
		_emit 0D9h
		_emit 080h
		_emit 0DCh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C3h
		_emit 08Bh
		_emit 048h
		_emit 004h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 005h
		_emit 0E8h
		_emit 091h
		_emit 0F0h
		_emit 0BEh
		_emit 0FFh
		_emit 0D9h
		_emit 080h
		_emit 0DCh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C3h
	}
}

enum KindOfType
{
	KINDOF_INERT = 24
};

struct KindOfMaskType
{
	UnsignedInt m_words[1];

	UnsignedInt getword( size_t pos ) const { return m_words[pos / 32]; }
	static UnsignedInt maskbit( size_t pos ) { return 1UL << (pos % 32); }

	Bool test( size_t pos ) const
	{
		return (getword(pos) & maskbit(pos)) != 0;
	}
};

//-------------------------------------------------------------------------------------------------
/// ThingTemplate stand-in: an Overridable with KindOfMaskType at +0xd0.
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf( KindOfType t ) const { return m_kindof.test(t); }

	UnsignedByte		_bfme_tt_pad[0xc8];
	KindOfMaskType	m_kindof;														///< +0xd0, bit 24 = KINDOF_INERT
	UnsignedInt			_bfme_tt_flags;											///< +0xd4, bit 0x1000 gates the upgrade broadcast
};

//-------------------------------------------------------------------------------------------------
/// The interface the contain module hands out, whose slot +0xb0 takes the upgrade mask.
class _BFMEUpgradeSink
{
public:
	virtual void _bfme_us_slot00() = 0;	virtual void _bfme_us_slot01() = 0;
	virtual void _bfme_us_slot02() = 0;	virtual void _bfme_us_slot03() = 0;
	virtual void _bfme_us_slot04() = 0;	virtual void _bfme_us_slot05() = 0;
	virtual void _bfme_us_slot06() = 0;	virtual void _bfme_us_slot07() = 0;
	virtual void _bfme_us_slot08() = 0;	virtual void _bfme_us_slot09() = 0;
	virtual void _bfme_us_slot10() = 0;	virtual void _bfme_us_slot11() = 0;
	virtual void _bfme_us_slot12() = 0;	virtual void _bfme_us_slot13() = 0;
	virtual void _bfme_us_slot14() = 0;	virtual void _bfme_us_slot15() = 0;
	virtual void _bfme_us_slot16() = 0;	virtual void _bfme_us_slot17() = 0;
	virtual void _bfme_us_slot18() = 0;	virtual void _bfme_us_slot19() = 0;
	virtual void _bfme_us_slot20() = 0;	virtual void _bfme_us_slot21() = 0;
	virtual void _bfme_us_slot22() = 0;	virtual void _bfme_us_slot23() = 0;
	virtual void _bfme_us_slot24() = 0;	virtual void _bfme_us_slot25() = 0;
	virtual void _bfme_us_slot26() = 0;	virtual void _bfme_us_slot27() = 0;
	virtual void _bfme_us_slot28() = 0;	virtual void _bfme_us_slot29() = 0;
	virtual void _bfme_us_slot30() = 0;	virtual void _bfme_us_slot31() = 0;
	virtual void _bfme_us_slot32() = 0;	virtual void _bfme_us_slot33() = 0;
	virtual void _bfme_us_slot34() = 0;	virtual void _bfme_us_slot35() = 0;
	virtual void _bfme_us_slot36() = 0;	virtual void _bfme_us_slot37() = 0;
	virtual void _bfme_us_slot38() = 0;	virtual void _bfme_us_slot39() = 0;
	virtual void _bfme_us_slot40() = 0;	virtual void _bfme_us_slot41() = 0;
	virtual void _bfme_us_slot42() = 0;	virtual void _bfme_us_slot43() = 0;
	virtual void applyUpgradeMask( const UpgradeMaskType& mask, Bool set ) = 0;	///< +0xb0
};

//-------------------------------------------------------------------------------------------------
class ContainModuleInterface
{
public:
	virtual void _bfme_cmi_slot00() = 0;	virtual void _bfme_cmi_slot01() = 0;
	virtual void _bfme_cmi_slot02() = 0;	virtual void _bfme_cmi_slot03() = 0;
	virtual void _bfme_cmi_slot04() = 0;	virtual void _bfme_cmi_slot05() = 0;
	virtual void _bfme_cmi_slot06() = 0;	virtual void _bfme_cmi_slot07() = 0;
	virtual void _bfme_cmi_slot08() = 0;	virtual void _bfme_cmi_slot09() = 0;
	virtual void _bfme_cmi_slot10() = 0;	virtual void _bfme_cmi_slot11() = 0;
	virtual void _bfme_cmi_slot12() = 0;	virtual void _bfme_cmi_slot13() = 0;
	virtual void _bfme_cmi_slot14() = 0;	virtual void _bfme_cmi_slot15() = 0;
	virtual void _bfme_cmi_slot16() = 0;	virtual void _bfme_cmi_slot17() = 0;
	virtual void _bfme_cmi_slot18() = 0;	virtual void _bfme_cmi_slot19() = 0;
	virtual void _bfme_cmi_slot20() = 0;	virtual void _bfme_cmi_slot21() = 0;
	virtual void _bfme_cmi_slot22() = 0;	virtual void _bfme_cmi_slot23() = 0;
	virtual void _bfme_cmi_slot24() = 0;	virtual void _bfme_cmi_slot25() = 0;
	virtual _BFMEUpgradeSink* getUpgradeSink() = 0;								///< +0x68
};

//-------------------------------------------------------------------------------------------------
class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeIndex( void ) const { return _bfme_ut_index; }

	UnsignedByte	_bfme_ut_head[0x20];
	UnsignedInt		_bfme_ut_index;										///< +0x20
};

//-------------------------------------------------------------------------------------------------
// ?giveUpgrade@Object@@QAEXPBVUpgradeTemplate@@@Z
void Object::giveUpgrade( const UpgradeTemplate *upgradeT )
{
	if (upgradeT)
	{
		UnsignedInt idx = upgradeT->getUpgradeIndex();
		m_objectUpgradesCompleted.m_bits[idx >> 5] |= (1 << (idx & 31));

		updateUpgradeModules();

		// Thing::getTemplate(): the template is an Overridable, so walk to its final override.
		const Overridable* tmpl = m_template;
		if (tmpl != NULL)
			tmpl = tmpl->getFinalOverride();

		if (((const ThingTemplate*)tmpl)->_bfme_tt_flags & 0x1000)
		{
			if (getContain() && getContain()->getUpgradeSink())
				getContain()->getUpgradeSink()->applyUpgradeMask( m_objectUpgradesCompleted, FALSE );
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?getProductionUpdateInterface@Object@@QAEPAVProductionUpdateInterface@@XZ
ProductionUpdateInterface* Object::getProductionUpdateInterface( void )
{
	for( BehaviorModule** b = m_behaviors; *b; ++b )
	{
		ProductionUpdateInterface* pu = (*b)->getProductionUpdateInterface();
		if( pu )
			return pu;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ?getDockUpdateInterface@Object@@QAEPAVDockUpdateInterface@@XZ
DockUpdateInterface* Object::getDockUpdateInterface( void )
{
	for( BehaviorModule** b = m_behaviors; *b; ++b )
	{
		DockUpdateInterface* dock = (*b)->getDockUpdateInterface();
		if( dock )
			return dock;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ?getCountermeasuresBehaviorInterface@Object@@QAEPAVCountermeasuresBehaviorInterface@@XZ
CountermeasuresBehaviorInterface* Object::getCountermeasuresBehaviorInterface( void )
{
	for( BehaviorModule** b = m_behaviors; *b; ++b )
	{
		CountermeasuresBehaviorInterface* cbi = (*b)->getCountermeasuresBehaviorInterface();
		if( cbi )
			return cbi;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ?getCountermeasuresBehaviorInterface@Object@@QBEPBVCountermeasuresBehaviorInterface@@XZ
const CountermeasuresBehaviorInterface* Object::getCountermeasuresBehaviorInterface( void ) const
{
	// A const module pointer forces the const-qualified BehaviorModuleInterface
	// overload (+0x7c), not the non-const one (+0x80) the mutable loop above hits.
	for( BehaviorModule** b = m_behaviors; *b; ++b )
	{
		const BehaviorModule* module = *b;
		const CountermeasuresBehaviorInterface* cbi = module->getCountermeasuresBehaviorInterface();
		if( cbi )
			return cbi;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ?getProjectileUpdateInterface@Object@@QBEPAVProjectileUpdateInterface@@XZ
ProjectileUpdateInterface* Object::getProjectileUpdateInterface( void ) const
{
	for( BehaviorModule** b = m_behaviors; *b; ++b )
	{
		ProjectileUpdateInterface* pui = (*b)->getProjectileUpdateInterface();
		if( pui )
			return pui;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
class UpgradeModuleInterface
{
public:
	virtual void _bfme_umi_slot0() = 0;
	virtual void _bfme_umi_slot1() = 0;
	virtual void _bfme_umi_slot2() = 0;
	virtual void resetUpgrade( const UpgradeMaskType& keyMask ) = 0;	///< +0x0c
};

//-------------------------------------------------------------------------------------------------
// ?removeUpgrade@Object@@QAEXPBVUpgradeTemplate@@@Z
void Object::removeUpgrade( const UpgradeTemplate *upgradeT )
{
	UnsignedInt idx = upgradeT->getUpgradeIndex();
	m_objectUpgradesCompleted.m_bits[idx >> 5] &= ~(1 << (idx & 31));

	for (BehaviorModule** module = m_behaviors; *module; ++module)
	{
		UpgradeModuleInterface* upgrade = (*module)->getUpgrade();
		if (!upgrade)
			continue;

		upgrade->resetUpgrade( UpgradeMaskType( UpgradeMaskType::kInit, upgradeT->getUpgradeIndex() ) );
	}
}

//-------------------------------------------------------------------------------------------------
class AIUpdateInterface
{
public:
	Locomotor* getCurLocomotor( void ) const { return m_curLocomotor; }

	UnsignedByte	_bfme_ai_head[0x1cc];
	Locomotor*		m_curLocomotor;										///< +0x1cc
};

//-------------------------------------------------------------------------------------------------
// ?isUsingAirborneLocomotor@Object@@QBE_NXZ
Bool Object::isUsingAirborneLocomotor( void ) const
{
	return ( m_ai && m_ai->getCurLocomotor() && ((m_ai->getCurLocomotor()->getLegalSurfaces() & (1 << 3)) != 0) );
}

//-------------------------------------------------------------------------------------------------
// ?findSpecialPowerWithOverridableDestinationActive@Object@@QBEPAVSpecialPowerUpdateInterface@@W4SpecialPowerType@@@Z
SpecialPowerUpdateInterface* Object::findSpecialPowerWithOverridableDestinationActive( SpecialPowerType type ) const
{
	for( BehaviorModule** b = m_behaviors; *b; ++b )
	{
		SpecialPowerUpdateInterface* spuInterface = (*b)->getSpecialPowerUpdateInterface();
		if( spuInterface && spuInterface->doesSpecialPowerHaveOverridableDestinationActive() )
			return spuInterface;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
class GameLogic
{
public:
	UnsignedInt getFrame( void ) const { return m_frame; }

	UnsignedByte	_bfme_gl_pad[0x3c];
	UnsignedInt		m_frame;
};

extern GameLogic* TheGameLogic;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z
Bool Thing::isKindOf( KindOfType k ) const
{
	const Overridable* tmpl = *(const Overridable* const*)((const char*)this + 4);
	if (tmpl != NULL)
		tmpl = tmpl->getFinalOverride();
	return ((const ThingTemplate*)tmpl)->isKindOf(k);
}

//-------------------------------------------------------------------------------------------------
// ?didEnterOrExit@Object@@IBE_NXZ
Bool Object::didEnterOrExit( void ) const
{
	if (isKindOf(KINDOF_INERT))
		return FALSE;

	UnsignedInt now = TheGameLogic->getFrame();
	return (m_enteredOrExitedFrame == now || m_enteredOrExitedFrame == now - 1);
}

//-------------------------------------------------------------------------------------------------
// ?didEnter@Object@@QBE_NPBVPolygonTrigger@@@Z
Bool Object::didEnter( const PolygonTrigger *pTrigger ) const
{
	if (!didEnterOrExit())
		return false;

	for (Int i = 0; i < m_numTriggerAreasActive; ++i)
	{
		if (m_triggerInfo[i].entered && m_triggerInfo[i].pTrigger == pTrigger)
			return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?didExit@Object@@QBE_NPBVPolygonTrigger@@@Z
Bool Object::didExit( const PolygonTrigger *pTrigger ) const
{
	if (!didEnterOrExit())
		return false;

	for (Int i = 0; i < m_numTriggerAreasActive; ++i)
	{
		if (m_triggerInfo[i].exited && m_triggerInfo[i].pTrigger == pTrigger)
			return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?testStatus@Object@@QBE_NW4ObjectStatusTypes@@@Z
Bool Object::testStatus( ObjectStatusTypes s ) const
{
	if( m_status.test( s ) )
		return TRUE;

	const Overridable* tmpl = m_template;
	if( tmpl != NULL )
		tmpl = tmpl->getFinalOverride();

	const Object* obj = this;
	if( (((const ThingTemplate*)tmpl)->_bfme_tt_flags & 0x1000) == 0 )
	{
		obj = m_containedBy;
		if( obj == NULL || !obj->isKindOf( (KindOfType)0x6c ) )
			return FALSE;
	}

	if( obj != NULL )
	{
		return obj->m_status.test( s );
	}

	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?hasSpecialPower@Object@@QBE_NW4SpecialPowerType@@@Z
Bool Object::hasSpecialPower( SpecialPowerType type ) const
{
	return m_specialPowerBits.test( type );
}


