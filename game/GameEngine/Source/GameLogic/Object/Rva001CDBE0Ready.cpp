// cl: /DNDEBUG /MD /EHsc
// Retail 0x001CDBE0 (56 bytes, ret at +0x37, INT3 padding from +0x38).
// True when TheGameLogic is live, object status bit 0x25 is clear and the
// current logic frame has reached the frame stored at this+0x334.  Called as a
// bool const Object member from CommandXlatVoice.cpp (voice-response gate).
// The address-derived name keeps the caller's pinned mangled name; the field
// at +0x334 is the one ZH calls the safe-occlusion frame, but that identity is
// not proven for BFME, so the member keeps its offset name.

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
	const GameLogic *gameLogic = TheGameLogic;
	if (gameLogic == 0)
		return false;
	const Object *self = this;
	// Two named bool locals: a combined && / ternary or an early return lets
	// VC7.1 swap ESI/EDI or fold the compare into sbb/inc.
	Bool busy = self->testStatusRva001CC880(OBJECT_STATUS_BIT_25);
	Bool early = gameLogic->m_frame < self->field334;
	return (busy || early) ? 0 : 1;
}
