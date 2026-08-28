// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupDoCommandButton, retail 0x00150F00, 49 bytes.
//
// The reference's body with one BFME change: the per-object command carries a
// third argument, and this loop passes it zero -- the same shape the two
// AtPosition/AtObject loops just below it have, one argument narrower.
//
// The callee is spelled with two ints because that is the decorated name the
// ledger already pins on ILT 0x000063CF.
//
// m_memberList is at this+0x04 -- the walk is over the STLport sentinel node
// ([this+4] is the node pointer, its next is begin, itself is end) and the
// member object is the node's payload at +0x08.  Both arguments are loop
// invariant and live in ebx/ebp.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;

class CommandButton;
enum CommandSourceType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void doCommandButton(const CommandButton *commandButton, Int cmdSource, Int bfmeArg);	// ILT 0x000063CF
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupDoCommandButton(const CommandButton *commandButton, CommandSourceType cmdSource);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::groupDoCommandButton( const CommandButton *commandButton, CommandSourceType cmdSource )
{
	_STL::list<Object *>::iterator i;
	Object *source;

	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{

		// get object
		source = *i;

		source->doCommandButton( commandButton, cmdSource, 0 );
	}  // end for, i
}
