// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ScriptActions::doNamedSetRepulsor, retail 0x002FD510, 67 bytes.
//
// Identity: executeAction's jump table arm 235 reaches this body, which is ZH
// NAMED_SET_REPULSOR at 231 under the +4 arm shift the four matched
// override-relation bodies fix for this band.  The ZH line is one call each to
// getUnitNamed and setStatus, and retail is that line.
//
// Two BFME departures make this its own TU rather than a body in
// ScriptActions.cpp, which compiles against the reference headers:
//
//   - getUnitNamed sits at ScriptEngine vtable slot 26 (+0x68), not the
//     reference's 23.
//   - setStatus takes the mask by const reference and the flag count is 86,
//     not the reference's by-value BitFlags<45>.  The one-bit mask is therefore
//     built in a 12-byte local and its address passed.  OBJECT_STATUS_REPULSOR
//     is bit 8 -- word 0, mask 0x100 -- counted without the reference's
//     OBJECT_STATUS_NONE, which is not a bit.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_REPULSOR = 8
};

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

private:
	_STL::bitset<NUMBITS>	m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;			// 86: the setStatus body sanitizes its top word with 0x3FFFFF

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);	// ILT 0x000307E7
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Object *getUnitNamed(const AsciiString &name) = 0;		// slot 26, +0x68
};

extern ScriptEngine *TheScriptEngine;					// 0x012F076C

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptActions
{
protected:
	void doNamedSetRepulsor(const AsciiString& unitName, Bool repulsor);
};

void ScriptActions::doNamedSetRepulsor(const AsciiString& unitName, Bool repulsor)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theSrcUnit) {
		return;
	}
	theSrcUnit->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_REPULSOR ), repulsor );
}
