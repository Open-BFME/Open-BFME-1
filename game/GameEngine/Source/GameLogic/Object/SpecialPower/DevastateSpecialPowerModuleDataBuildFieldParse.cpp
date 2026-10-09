// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport

// DevastateSpecialPowerModuleData::buildFieldParse, retail 0x0025A790, 30 bytes.
//
// The DevastateSpecialPower module data factory at 0x00121590 hands
// INI::initFromINIMultiProc this address, so this body is that module's field
// parse builder. The factory allocates 0x220 bytes and the table below reaches
// +0x21C, which agrees.
//
// ILT 0x0002AF8B jumps to SpecialPowerModuleData::buildFieldParse at
// 0x002683D0, whose retail reconstruction owns the existing ledger name.
// The appender is MultiIniFieldParse::add at 0x00850920.
//
// The receiver is spelled WideMulti because this file's own matched row is
// ?buildFieldParse@DevastateSpecialPowerModuleData@@SAXAAVWideMulti@@@Z;
// renaming the parameter type would rename the enclosing body and unmatch that
// row. The appender this body calls is retail's MultiIniFieldParse::add at
// 0x00850920, so the call goes through the defining class.

#include "Common/INI.h"

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)(INI *, void *, void *, const void *);
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
};

class SpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

class DevastateSpecialPowerModuleData
{
public:
	static void buildFieldParse(WideMulti &p);
};

static const WideFieldParse s_devastateFieldParse[] =
{
	{ "Radius",              INI::parseReal,          0, 0x210 },
	{ "FX",                  INI::parseFXList,        0, 0x214 },
	{ "TreeValueMultiplier", INI::parsePercentToReal, 0, 0x218 },
	{ "TreeValueTotalCap",   INI::parseReal,          0, 0x21C },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@DevastateSpecialPowerModuleData@@SAXAAVWideMulti@@@Z
void DevastateSpecialPowerModuleData::buildFieldParse(WideMulti &p)
{
	SpecialPowerModuleData::buildFieldParse(reinterpret_cast<MultiIniFieldParse &>(p));
	reinterpret_cast<MultiIniFieldParse &>(p).add(
		reinterpret_cast<const FieldParse *>(s_devastateFieldParse), 0);
}
