// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// Twin of ?getPowerName@SpecialPowerModule@@UBE?AVAsciiString@@XZ @0x00268A60
// with module data at this-0x20 instead of this-0xc (a wider preceding
// multiple-inheritance layout than SpecialPowerModule proper).

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate
{
public:
	AsciiString getName(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
struct Gen0026AC60ModuleData
{
	unsigned char m_unreconstructed_00[8];		// +0x00
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x08
};

// Wider iface: module data pointer at this-0x20 (compact SpecialPowerModule
// keeps it at this-0xc; this sibling has more preceding MI bases/interfaces).
class Gen0026AC60Owner
{
public:
	AsciiString getPowerName(void) const;

private:
	const Gen0026AC60ModuleData *getModuleData(void) const
	{
		return *(const Gen0026AC60ModuleData *const *)((const char *)this - 0x20);
	}
};

// ?getPowerName@Gen0026AC60Owner@@QBE?AVAsciiString@@XZ
AsciiString Gen0026AC60Owner::getPowerName(void) const
{
	return getModuleData()->m_specialPowerTemplate->getName();
}
