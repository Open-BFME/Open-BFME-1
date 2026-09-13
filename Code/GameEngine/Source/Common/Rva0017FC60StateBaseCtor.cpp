// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva000250BDStateBase : public AIInternalMoveToState
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
	: AIInternalMoveToState( machine, name ),
	  m_field50( 0x0 ),
	  m_field54( 0x1 ),
	  m_field55( 0x0 ),
	  m_field58( 0xA )
{
}
