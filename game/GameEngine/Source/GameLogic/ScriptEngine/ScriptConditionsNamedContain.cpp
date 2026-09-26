// cl: /DNDEBUG /DWIN32 /MD /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?evaluateNamedContainEmpty@ScriptConditions@@IAEEPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateNamedHasFreeContainerSlots@ScriptConditions@@IAE_NPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The two ScriptConditions conditions that ask what is inside a named unit:
//
//   0x003226E0  evaluateNamedContainEmpty          is it carrying nobody
//   0x00323CD0  evaluateNamedHasFreeContainerSlots  has it room for one more
//
// Both name the unit through getUnitNamed, take a module pointer off it and
// ask that module for a count. Neither compiles with /EHsc, so they share a
// TU the rest of ScriptConditions cannot.
//
// Putting them together is what shows that they do NOT read the same pointer,
// which is the whole reason this file has two module fields:
//
//   +0x1FC  the contain module, asked for its count through a virtual at
//           slot 64 -- the offset the bfmeobject shim pins as m_contain
//   +0x210  an unidentified module, asked for its count through a non-virtual
//           call at 0x000347E3 and compared against the Int at its +0x28
//
// Each file named its own pointer "m_contain" and neither could see the
// other's, so the same field name stood for two different offsets. The +0x210
// one is not the contain module: evaluateUnitHealth (0x00324020, still its own
// file) reads that identical pointer and that identical +0x28 and calls it the
// body module, and evaluateNamedDestroyedByType reads the body module at
// +0x200. What +0x210 actually is remains unproven; only the count getter's
// pinned name, BfmeNamedContain::getContainCount, is fixed, so the class keeps
// that name here rather than inventing a better one.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "ascii_string.h"

class Parameter;

#define BFME_SLOT(N) virtual void slot##N() = 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;	// slot 64, vtable+0x100
};

#undef BFME_SLOT

// The unidentified module at Object+0x210; named for its pinned count getter,
// not for anything proven about the class.
class BfmeNamedContain
{
public:
	Int getContainCount(void) const;			// retail 0x000347E3
	Int getContainMax(void) const { return m_max; }

private:
	unsigned char m_pad[0x28];
	Int m_max;						// this+0x28
};

// upstream layout: inputs/reference/shims/bfmeobject/GameLogic/Object.h
class Object
{
public:
	unsigned char m_beforeContain[0x1FC];
	ContainModuleInterface *m_contain;			// this+0x1FC
	unsigned char m_pad200[0x210 - 0x200];
	BfmeNamedContain *m_module210;				// this+0x210
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual void _se_17() = 0;
	virtual void _se_18() = 0;
	virtual void _se_19() = 0;
	virtual void _se_20() = 0;
	virtual void _se_21() = 0;
	virtual void _se_22() = 0;
	virtual void _se_23() = 0;
	virtual void _se_24() = 0;
	virtual void _se_25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;	// slot 26, vtable+0x68
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	unsigned char evaluateNamedContainEmpty(Parameter *pItemParm);
	Bool evaluateNamedHasFreeContainerSlots(Parameter *pUnitParm);
};

// ?evaluateNamedContainEmpty@ScriptConditions@@IAEEPAVParameter@@@Z
unsigned char ScriptConditions::evaluateNamedContainEmpty(Parameter *pItemParm)
{
	Object *obj = TheScriptEngine->getUnitNamed(
		*reinterpret_cast<const AsciiString *>(pItemParm));
	if (obj == 0) {
		return 0;
	} else {
		ContainModuleInterface *contain = obj->m_contain;
		if (contain == 0)
			return 0;
		return (unsigned char)(contain->getContainCount(false) <= 0);
	}
}

// ?evaluateNamedHasFreeContainerSlots@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateNamedHasFreeContainerSlots(Parameter *pUnitParm)
{
	if (!pUnitParm) {
		return false;
	}

	Object *pUnit = TheScriptEngine->getUnitNamed(
		*reinterpret_cast<const AsciiString *>(pUnitParm));
	if (!pUnit) {
		return false;
	}

	BfmeNamedContain *contain = pUnit->m_module210;
	if (contain) {
		Int max = contain->getContainMax();
		Int cur = contain->getContainCount();
		if (max > cur) {
			return true;
		}
	}
	return false;
}
