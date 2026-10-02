// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport
// Open-BFME6: 0x0022A450. Call the base builder, once-fill two extra
// FieldParse records, then append that table.
#include "Common/INI.h"

class WideFieldParse
{
public:
	const char *m_token;
	unsigned int m_offset;
	void (*m_parse)();
	const void *m_userData;
};

// The receiver spelling stays WideMulti because this file's own matched row
// is ?buildFieldParse@Rva0022A450@@SAXAAVWideMulti@@@Z; renaming the
// parameter type would rename the enclosing body and unmatch the row. The
// appender it calls is retail's MultiIniFieldParse::add at 0x00850920, so the
// call goes through the defining class.
class WideMulti
{
};

class Rva0022B3B0
{
public:
	static void buildFieldParse(WideMulti &p);
};

extern const char g_bfmeTokA450[];
extern void bfmeParseA450();
extern const char g_bfmeUserA450[];

class Rva0022A450
{
public:
	static void buildFieldParse(WideMulti &p);
};

static unsigned s_onceA450;
static WideFieldParse s_tableA450[2];
static unsigned s_tailA450[2];

void Rva0022A450::buildFieldParse(WideMulti &p)
{
	Rva0022B3B0::buildFieldParse(p);
	if ((s_onceA450 & 1) == 0)
	{
		s_onceA450 |= 1;
		s_tableA450[0].m_token = g_bfmeTokA450;
		s_tableA450[0].m_offset = 0x310;
		s_tableA450[0].m_parse = bfmeParseA450;
		s_tableA450[0].m_userData = g_bfmeUserA450;
		s_tableA450[1].m_token = 0;
		s_tableA450[1].m_offset = 0x314;
		s_tableA450[1].m_parse = 0;
		s_tableA450[1].m_userData = 0;
		s_tailA450[0] = 0;
		s_tailA450[1] = 0;
	}
	reinterpret_cast<MultiIniFieldParse &>(p).add(
		reinterpret_cast<const FieldParse *>(s_tableA450), 0);
}
