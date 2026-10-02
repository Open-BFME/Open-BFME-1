// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport

// FloatUpdateModuleData::buildFieldParse, retail 0x00294F70, 17 bytes.
//
// The FloatUpdate module data factory at 0x00118580 hands
// INI::initFromINIMultiProc this address, so this body is FloatUpdate's field
// parse builder. FloatUpdateModuleData's constructor sits directly before it at
// 0x00294F60 and is already matched, which puts both in the same class.
//
// The body pushes one table and the offset 0 and calls
// MultiIniFieldParse::add. The table at 0x010BF35C holds one row, "Enabled"
// parsed by INI::parseBool into the member at +0x08, then a null row.
//
// The receiver is spelled WideMulti because this file's own matched row is
// ?buildFieldParse@FloatUpdateModuleData@@SAXAAVWideMulti@@@Z; renaming the
// parameter type would rename the enclosing body and unmatch that row. The
// appender this body calls is retail's MultiIniFieldParse::add at 0x00850920,
// so the call goes through the defining class. The table is written out here
// rather than declared external, the way Rva0022A450Parse.cpp writes its own,
// because the operand is a relocation and the byte check masks it.

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

class FloatUpdateModuleData
{
public:
	static void buildFieldParse(WideMulti &p);
};

static const WideFieldParse s_floatUpdateFieldParse[] =
{
	{ "Enabled", INI::parseBool, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@FloatUpdateModuleData@@SAXAAVWideMulti@@@Z
void FloatUpdateModuleData::buildFieldParse(WideMulti &p)
{
	reinterpret_cast<MultiIniFieldParse &>(p).add(
		reinterpret_cast<const FieldParse *>(s_floatUpdateFieldParse), 0);
}
