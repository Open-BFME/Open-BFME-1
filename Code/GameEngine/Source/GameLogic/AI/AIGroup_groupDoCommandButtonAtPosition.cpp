// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupDoCommandButtonAtPosition, retail 0x00150F40, 54 bytes.
//
// The reference's body with one BFME change: the per-object command carries a
// fourth argument, and this loop passes it false.
//
// m_memberList is at this+0x04 -- the walk is over the STLport sentinel node
// ([this+4] is the node pointer, its next is begin, itself is end) and the
// member object is the node's payload at +0x08.  cmdSource and pos are loop
// invariant and live in ebx/ebp; the button is reloaded each turn because the
// call clobbers eax.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

class CommandButton;
struct Coord3D;
enum CommandSourceType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void doCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource, Bool bfmeFlag);	// ILT 0x00026EF4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupDoCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::groupDoCommandButtonAtPosition( const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource )
{
	_STL::list<Object *>::iterator i;
	Object *source;

	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{

		// get object
		source = *i;

		source->doCommandButtonAtPosition( commandButton, pos, cmdSource, false );
	}  // end for, i
}
