// ?rva001CDBE0@Object@@QBE_NXZ
// partial score=0.8393 date=2026-10-04
// cl: /DNDEBUG /MD /EHsc
// True when TheGameLogic is live, testStatusRva001CC880(0x25) is clear, and
// GameLogic::m_frame >= Object::field334 at this+0x334.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_BIT_25 = 0x25
};

class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Bool testStatusRva001CC880(ObjectStatusTypes s) const;
	Bool rva001CDBE0() const;

private:
	unsigned char m_pad[0x334];
	UnsignedInt field334;
};

Bool Object::rva001CDBE0() const
{
	const Object *self = this;
	const GameLogic *gameLogic = TheGameLogic;
	if (gameLogic == 0)
		return false;
	return !self->testStatusRva001CC880(OBJECT_STATUS_BIT_25) && gameLogic->m_frame >= self->field334;
}
