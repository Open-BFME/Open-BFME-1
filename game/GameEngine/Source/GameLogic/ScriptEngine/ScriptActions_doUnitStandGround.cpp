// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME's UNIT_STAND_GROUND action.  executeAction jump-table arm 499 passes
// the UNIT and BOOLEAN ScriptActionParameter objects directly to this helper.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_STAND_GROUND = 67
};

enum KindOfType
{
	KINDOF_HORDE = 108
};

template<int NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

// ScriptActionParameter's integer/boolean payload is the dword at +0x08.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptActionParameter
{
public:
	Int getInt() const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[(UnsignedInt)kind >> 5]
			& (1u << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_beforeKindOf[0xc8 - 8];
	UnsignedInt m_kindOf[6];
};

class Object;

// HordeContainInterface slot 60 (+0xF0) fills the caller-owned list with the
// horde's actual Object members.
class HordeContainInterface
{
public:
#define HORDE_SLOT(N) virtual void _horde_slot_##N() = 0
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55);
	HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58); HORDE_SLOT(59);
#undef HORDE_SLOT
	virtual void getMembers(_STL::list<Object *> *members) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(
				thingTemplate->m_nextOverride->getFinalOverride());
		return thingTemplate->isKindOf(kind);
	}

protected:
	virtual ~Thing();
	const ThingTemplate *m_template;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);

	// Proven Object+0x1FC -> Contain slot 26 body at 0x001BFE20.  Its existing
	// neutral pin keeps this TU from inventing a second interface identity.
	void *unidentified_001BFE20() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
#define SCRIPT_ENGINE_SLOT(N) virtual void _script_engine_slot_##N() = 0
	SCRIPT_ENGINE_SLOT(00); SCRIPT_ENGINE_SLOT(01); SCRIPT_ENGINE_SLOT(02);
	SCRIPT_ENGINE_SLOT(03); SCRIPT_ENGINE_SLOT(04); SCRIPT_ENGINE_SLOT(05);
	SCRIPT_ENGINE_SLOT(06); SCRIPT_ENGINE_SLOT(07); SCRIPT_ENGINE_SLOT(08);
	SCRIPT_ENGINE_SLOT(09); SCRIPT_ENGINE_SLOT(10); SCRIPT_ENGINE_SLOT(11);
	SCRIPT_ENGINE_SLOT(12); SCRIPT_ENGINE_SLOT(13); SCRIPT_ENGINE_SLOT(14);
	SCRIPT_ENGINE_SLOT(15); SCRIPT_ENGINE_SLOT(16); SCRIPT_ENGINE_SLOT(17);
	SCRIPT_ENGINE_SLOT(18); SCRIPT_ENGINE_SLOT(19); SCRIPT_ENGINE_SLOT(20);
	SCRIPT_ENGINE_SLOT(21); SCRIPT_ENGINE_SLOT(22); SCRIPT_ENGINE_SLOT(23);
	SCRIPT_ENGINE_SLOT(24); SCRIPT_ENGINE_SLOT(25);
#undef SCRIPT_ENGINE_SLOT
	virtual Object *resolveUnit(ScriptActionParameter *parameter) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doUnitStandGround(ScriptActionParameter *unitParameter,
		ScriptActionParameter *standGroundParameter);
};

void ScriptActions::doUnitStandGround(ScriptActionParameter *unitParameter,
	ScriptActionParameter *standGroundParameter)
{
	Object *object = TheScriptEngine->resolveUnit(unitParameter);
	if (object == 0)
		return;

	object->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_STAND_GROUND),
		standGroundParameter->getInt() != 0);

	if (object->isKindOf(KINDOF_HORDE))
	{
		HordeContainInterface *horde =
			reinterpret_cast<HordeContainInterface *>(
				object->unidentified_001BFE20());
		if (horde != 0)
		{
			_STL::list<Object *> members;
			horde->getMembers(&members);
			for (_STL::list<Object *>::iterator iter = members.begin();
				iter != members.end(); ++iter)
			{
				Object *member = *iter;
				member->setStatus(
					MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_STAND_GROUND),
					standGroundParameter->getInt() != 0);
			}
		}
	}
}
