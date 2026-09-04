// cl: /DNDEBUG /MD /EHsc
//
// Address-derived recovery of the state-machine factory at retail RVA
// 0x002C1260.  The literal and the owner slot are fixed by the retail body.

#include "../../../../../../../reference/shims/stringinline/StringInline.h"

class Rva002C1260StateMachine
{
public:
	Rva002C1260StateMachine( void *owner, AsciiString name );
private:
	unsigned char m_unreconstructed000[ 0x70 ];
};

#pragma comment(linker, "/alternatename:??0Rva002C1260StateMachine@@QAE@PAXVAsciiString@@@Z=?j_00022f5c@@YAXXZ")

class Rva002C1260Factory
{
public:
	Rva002C1260StateMachine *create();

private:
	unsigned char m_unreconstructed000[ 8 ];
	void *m_owner;
};

// ?create@Rva002C1260Factory@@QAEPAVRva002C1260StateMachine@@XZ
Rva002C1260StateMachine *Rva002C1260Factory::create()
{
	return new Rva002C1260StateMachine( m_owner,
		AsciiString( "GiantBirdAIStateMachine" ) );
}
