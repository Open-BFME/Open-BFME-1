// cl: /DNDEBUG /MD /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva000250BDStateBase : public Rva0014F280StateBase
{
public:
	Rva000250BDStateBase( void *machine, AsciiString name );

private:
	char m_baseFields[ 0x4C ];
	int m_field50;
	unsigned char m_field54;
	unsigned char m_field55;
	char m_field56And57[ 2 ];
	int m_field58;
};

Rva000250BDStateBase::Rva000250BDStateBase( void *machine, AsciiString name )
	: Rva0014F280StateBase( machine, name ),
	  m_field50( 0x0 ),
	  m_field54( 0x1 ),
	  m_field55( 0x0 ),
	  m_field58( 0xA )
{
}
