// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char * );
};

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class ThingTemplate;

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		const ThingTemplate *m_unit;
		int m_flags;
		AsciiString m_name;
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();

	void addUnitPrereq( AsciiString unit, bool orUnitWithPrevious );

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<int> m_prereqSciences;
	_STL::vector<int> m_unused;
};

// ?parsePrerequisiteUnit@@YAXPAVINI@@PAX1PBX@Z
void __cdecl parsePrerequisiteUnit( INI *ini, void *instance, void *, const void * )
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>( instance );

	ProductionPrerequisite prerequisite;
	bool orUnitWithPrevious = false;
	for( const char *token = ini->getNextToken( 0 ); token != 0;
		token = ini->getNextTokenOrNull( 0 ) )
	{
		prerequisite.addUnitPrereq( AsciiString( token ), orUnitWithPrevious );
		orUnitWithPrevious = true;
	}

	prerequisites->push_back( prerequisite );
}
