// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// readable body of ??0GrantUpgradeCreateModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp

// GrantUpgradeCreateModuleData::GrantUpgradeCreateModuleData, 0x0024FA80, 99 bytes.
//
// The reference body is one line, `m_upgradeName = "";`, over a module data
// whose only other member is the exempt-status mask. Retail spells the
// assignment as the two-argument setter -- `set("", 0)` -- which is the same
// shape WaterTransparencySetting's constructor uses at 0x30.
//
// A prior pass solved the structure and lost on the encoding: every hand-written
// spelling of the three-dword mask hoisted one `xor eax,eax` to the top of the
// body and wrote the fields off `this` with disp8, twelve bytes short of retail,
// which instead takes `lea edx,[esi+0x0C]` and writes [edx], [edx+4], [edx+8]
// while keeping the zero in eax live long enough to `push eax` as the setter's
// length argument. That shape is not something a field-by-field spelling can
// produce: it is an inlined memset over an array, which is what STLport's
// _Base_bitset<3> default constructor does (`_M_do_reset()` is
// `memset(_M_w, 0, _Nw * sizeof(_WordT))`). So the mask comes from the vendored
// <bitset> rather than from a reconstruction, exactly as the __true_type tag in
// parseFX had to.
//
// Declaration order is what puts the memset between the string's constructor
// and the setter call, and that is what keeps the zero live across the argument
// pushes.
//
// The exception frame counts two states, 0 then 1, the same way
// WaterTransparencySetting's does: state 0 is the base subobject and state 1 is
// the string. Flattening the base into one class loses state 0 entirely, so the
// base has to be a real polymorphic class with a declared destructor -- and its
// constructor has to be inline and empty, which is what leaves a single vftable
// store (the base's is a dead store the optimizer drops) and what puts the
// `mov [esp+4],esi` registration of `this` ahead of everything else.

#include <bitset>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( void ) { m_data = 0; }
	~AsciiString( void );

	void set( const char *text, int length );

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModuleData
{
public:
	CreateModuleData( void ) { }
	virtual ~CreateModuleData( void );

private:
	int m_moduleDataBase_04;							// +0x04, untouched by this constructor
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h
class GrantUpgradeCreateModuleData : public CreateModuleData
{
public:
	GrantUpgradeCreateModuleData();

private:
	AsciiString m_upgradeName;							// +0x08
	_STL::bitset<96> m_exemptStatus;					// +0x0C
};

// ??0GrantUpgradeCreateModuleData@@QAE@XZ
GrantUpgradeCreateModuleData::GrantUpgradeCreateModuleData()
{
	m_upgradeName.set("", 0);
}
