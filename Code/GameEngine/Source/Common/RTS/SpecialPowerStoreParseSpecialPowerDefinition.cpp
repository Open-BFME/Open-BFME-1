// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/iniexception /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?parseSpecialPowerDefinition@SpecialPowerStore@@SAXPAVINI@@@Z
// Retail 0x000EBE90, 639 bytes: the SpecialPower INI block parser.
//
// Identity: the body reads "DefaultSpecialPower" (0x01085D1C) and throws
// "Special power '%s' already defined" (0x01085CF0), goes through
// TheSpecialPowerStore (0x012ED80C) to findSpecialPowerTemplatePrivate
// (0x000EBA20) and findSpecialPowerTemplate (0x000BA930), and hands every
// template to INI::initFromINI with the field table at 0x012A8FA0 whose first
// entry is "ReloadTime" -- the Zero Hour SpecialPowerStore twin, line for line.
//
// BFME differences from the twin: the template is a plain `new` (0x11C bytes)
// rather than a pool instance, the duplicate throws a formatted INIException
// instead of the bare INI_INVALID_DATA, every copy assignment is bracketed by
// the override-copy byte at 0x012ED611 (same as CrateSystem and ControlBar
// overrides), and the final `if (specialPower)` guard is gone.

#include <vector>

#include "Common/INIException.h"
#include "string_base.h"

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct FieldParse;

// Raised only while an override is being copied over its original.
extern Bool TheBfmeOverrideCopyInProgress;			// 0x012ED611

// ascii_string.h forwards str() out of line; retail inlines it here, so this
// TU keeps the StringBase<char> forwarders inline itself (StringInline.h shape).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *s ) : StringBase<char>( s ) {}
	AsciiString( const AsciiString &that ) : StringBase<char>( that ) {}
	~AsciiString() {}
	AsciiString &operator=( const AsciiString &that ) { set( that ); return *this; }
	const char *str() const { return m_data ? m_data->data : ""; }
};

// BFME keeps the load type at INI+0x08.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
	int getLoadType() const { return m_loadType; }

private:
	int m_unmodelled00;
	int m_unmodelled04;
	int m_loadType;
};

enum { INI_LOAD_CREATE_OVERRIDES = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	void setNextOverride( Overridable *nextOverride ) { m_nextOverride = nextOverride; }
	void markAsOverride() { m_isOverride = true; }

private:
	Overridable *m_nextOverride;				// +0x04
	Bool m_isOverride;					// +0x08
};

// The template's copy assignment (0x000EB2B0), ledgered under its address.
class Rva000EB2B0
{
public:
	Rva000EB2B0 &operator=( const Rva000EB2B0 &other );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerTemplate();

	static const FieldParse *getFieldParse() { return m_specialPowerFieldParse; }
	void friend_setNameAndID( const AsciiString &name, UnsignedInt id )
	{
		m_name = name;
		m_id = id;
	}

private:
	static const FieldParse m_specialPowerFieldParse[];

	AsciiString m_name;					// +0x0C
	UnsignedInt m_id;					// +0x10
	char m_unmodelled14[ 0x11C - 0x14 ];			// sizeof is the pushed 0x11C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

protected:
	AsciiString m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore : public SubsystemInterface
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate( AsciiString name );
	static void parseSpecialPowerDefinition( INI *ini );

protected:
	SpecialPowerTemplate *findSpecialPowerTemplatePrivate( AsciiString name );

	std::vector<SpecialPowerTemplate *> m_specialPowerTemplates;	// +0x08
	UnsignedInt m_nextSpecialPowerID;				// +0x14
};

extern SpecialPowerStore *TheSpecialPowerStore;

void SpecialPowerStore::parseSpecialPowerDefinition( INI *ini )
{
	// read the name
	AsciiString name = ini->getNextToken();

	SpecialPowerTemplate* specialPower = TheSpecialPowerStore->findSpecialPowerTemplatePrivate( name );

	if ( ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES )
	{
		if (specialPower)
		{
			SpecialPowerTemplate* child = (SpecialPowerTemplate*)specialPower->friend_getFinalOverride();
			specialPower = new SpecialPowerTemplate;
			TheBfmeOverrideCopyInProgress = true;
			*(Rva000EB2B0 *)specialPower = *(Rva000EB2B0 *)child;
			TheBfmeOverrideCopyInProgress = false;
			child->setNextOverride(specialPower);
			specialPower->markAsOverride();
		}
		else
		{
			specialPower = new SpecialPowerTemplate;
			const SpecialPowerTemplate *defaultTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( "DefaultSpecialPower" );
			if( defaultTemplate )
			{
				TheBfmeOverrideCopyInProgress = true;
				*(Rva000EB2B0 *)specialPower = *(const Rva000EB2B0 *)defaultTemplate;
				TheBfmeOverrideCopyInProgress = false;
			}
			specialPower->friend_setNameAndID(name, ++TheSpecialPowerStore->m_nextSpecialPowerID);
			specialPower->markAsOverride();
			TheSpecialPowerStore->m_specialPowerTemplates.push_back(specialPower);
		}
	}
	else
	{
		if (specialPower)
		{
			throw INIException( 3, "Special power '%s' already defined", name.str() );
		}
		else
		{
			specialPower = new SpecialPowerTemplate;
			const SpecialPowerTemplate *defaultTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( "DefaultSpecialPower" );
			if( defaultTemplate )
			{
				TheBfmeOverrideCopyInProgress = true;
				*(Rva000EB2B0 *)specialPower = *(const Rva000EB2B0 *)defaultTemplate;
				TheBfmeOverrideCopyInProgress = false;
			}
			specialPower->friend_setNameAndID(name, ++TheSpecialPowerStore->m_nextSpecialPowerID);
			TheSpecialPowerStore->m_specialPowerTemplates.push_back(specialPower);
		}
	}

	// parse the ini definition
	ini->initFromINI( specialPower, specialPower->getFieldParse() );
}
