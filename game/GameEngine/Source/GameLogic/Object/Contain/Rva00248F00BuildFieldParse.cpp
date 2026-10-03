// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport

// Retail 0x00248F00 is the field-parse builder that the module-data factory
// 0x00116140 hands to initFromINIMultiProc, and ModuleFactory::init registers
// that factory under "HordeGarrisonContain". It extends OpenContain's builder
// (ILT 0x00019772) with two tables. The module-data class name is not in the
// image, so the owner stays address-derived; the vocabulary is
// WideBuildFieldParse.cpp's.
//
// The receiver is spelled WideMulti because this file's own matched row is
// ?buildFieldParse@Rva00248F00@@SAXAAVWideMulti@@@Z; renaming the parameter
// type would rename the enclosing body and unmatch that row. The appender these
// bodies call is retail's MultiIniFieldParse::add at 0x00850920, so the calls go
// through the defining class.

#include "Common/INI.h"

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)();
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
};

// Retail 0x248F06 calls ILT 0x19772 -> the existing 0x2284A0 builder.
// Both bodies pass the same MultiIniFieldParse address under cdecl; no result.
class Rva002284A0FieldParseBuilder
{
public:
	static void build( MultiIniFieldParse &p );
};

extern const WideFieldParse WideTbl00248F00A[];
extern const WideFieldParse WideTbl00248F00B[];

class Rva00248F00
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00248F00::buildFieldParse( WideMulti &p )
{
	Rva002284A0FieldParseBuilder::build( reinterpret_cast<MultiIniFieldParse &>( p ) );
	MultiIniFieldParse &m = reinterpret_cast<MultiIniFieldParse &>( p );
	m.add( reinterpret_cast<const FieldParse *>( WideTbl00248F00A ), 0 );
	m.add( reinterpret_cast<const FieldParse *>( WideTbl00248F00B ), 0 );
}
