// cl: /DNDEBUG /MD /EHsc

class Object;
class GiantBirdGuardReturnState;

// callees.py: the constructor call goes through ILT 0x0001C292 to
// 0x002C05C0, the matched GiantBirdGuardMachine(Object *) constructor
// (GiantBirdGuardMachineCtor.cpp), not to a GiantBirdGuardReturnState
// constructor. The row's name and return type are kept as ledgered.
class GiantBirdGuardMachine
{
public:
	GiantBirdGuardMachine( Object *owner );

private:
	unsigned char m_unreconstructed[ 0x78 ];
};

class Rva002C1BC0Factory
{
public:
	GiantBirdGuardReturnState *createGuardReturnState();

private:
	unsigned char m_unreconstructed00[ 0x10 ];
	Object *m_owner;
};

GiantBirdGuardReturnState *Rva002C1BC0Factory::createGuardReturnState()
{
	return (GiantBirdGuardReturnState *)new GiantBirdGuardMachine( m_owner );
}
