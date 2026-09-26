// ?rva001CDBE0@Object@@QBE_NXZ
// partial score=0.85 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// True when TheGameLogic is live, testStatus(0x25) is clear, and
// GameLogic::m_frame >= Object::m_safeOcclusionFrame at this+0x334.

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
	Bool testStatus(ObjectStatusTypes s) const;
	Bool rva001CDBE0() const;

private:
	unsigned char m_pad[0x334];
	UnsignedInt m_safeOcclusionFrame;
};

Bool Object::rva001CDBE0() const
{
	const GameLogic *gameLogic = TheGameLogic;
	if (gameLogic == 0)
		return false;
	const Object *self = this;
	Bool bad = self->testStatus(OBJECT_STATUS_BIT_25);
	if (!bad)
		bad = gameLogic->m_frame < self->m_safeOcclusionFrame;
	return bad ? false : true;
}
