// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The ExperienceScalarTable block and its one field callback:
//
//   0x0037EF50  ExperienceScalarTable::ExperienceScalarTable
//   0x00380300  BfmeExperienceLevelSystem::addScalarTable
//   0x00380350  parseExperienceScalarTableScalars   the Scalars field
//   0x00380400  parseExperienceScalarTable          the block
//
// BFME-only; the INI block table in .data names the block, and the field table
// at 0x010EA91C names the callback as the parser for the table's variable-length
// Real vector. The block builds a table from the name, lets initFromINI fill it
// through that same field table, and appends it -- so the callback the block
// dispatches to was in the other file, one indirection away and no way to see it.
//
// The store is TheExperienceLevelSystem at 0x012F0888 -- GameEngine::init builds
// the literal "TheExperienceLevelSystem" into the AsciiString it hands the
// registrar in the instruction before that address is pushed -- and the tables
// go into a vector at +0x20 of it. Retail inlines the whole push_back fast path
// (compare finish against end_of_storage, copy-construct, bump finish) and only
// calls out to _M_insert_overflow, which is what says it is a vector and not a
// list.
//
// The table record is 0x10 bytes and the block reads none of it.
//
// _STLP_NO_EXCEPTIONS was defined by the field-callback file alone. It governs
// the whole TU once the two share one, so it was probed on the block file
// first -- define added, nothing else touched -- and all three of its bodies
// still matched before anything was merged.
///////////////////////////////////////////////////////////////////////////////
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/STLTypedefs.h"

class ExperienceScalarTable
{
public:
	ExperienceScalarTable( const AsciiString &name );

	static const FieldParse m_fieldParseTable[];		// 0x010EA91C

private:
	unsigned m_unmodelled_00;
	unsigned m_unmodelled_04;
	AsciiString m_unmodelled_08;
	AsciiString m_name;
};

class BfmeExperienceLevelSystem
{
public:
	// By value and inline: retail materialises the pointer into its stack slot
	// AFTER initFromINI returns, at the push_back itself, which is what a
	// by-value parameter whose address the inlined push_back then takes does. A
	// bare `m_scalarTables.push_back( table )' at the call site spills the
	// variable before the call instead.
	void addScalarTable( ExperienceScalarTable *table )
	{
		m_scalarTables.push_back( table );
	}

	unsigned char m_unmodelled_00[ 0x20 ];
	std::vector<ExperienceScalarTable *> m_scalarTables;	// +0x20
};

extern BfmeExperienceLevelSystem *TheExperienceLevelSystem;	// 0x012F0888

__declspec(noinline) ExperienceScalarTable::ExperienceScalarTable( const AsciiString &name ) :
	m_unmodelled_00( 0 ),
	m_unmodelled_04( 0 ),
	m_name( name )
{
}

// ?parseExperienceScalarTableScalars@@YAXPAVINI@@PAX1PBX@Z
void parseExperienceScalarTableScalars(INI *ini, void *, void *store, const void *)
{
	std::vector<Real> *values = (std::vector<Real> *)store;
	values->clear();
	for (const char *token = ini->getNextTokenOrNull(); token != NULL;
		token = ini->getNextTokenOrNull())
	{
		values->push_back(INI::scanReal(token));
	}
}

// ?parseExperienceScalarTable@@YAXPAVINI@@@Z
void parseExperienceScalarTable( INI *ini )
{
	if( !TheExperienceLevelSystem )
		return;

	AsciiString name( ini->getNextToken() );

	ExperienceScalarTable *table = new ExperienceScalarTable( name );

	ini->initFromINI( table, ExperienceScalarTable::m_fieldParseTable );

	TheExperienceLevelSystem->addScalarTable( table );
}
