// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: GameMessage::allocArg, retail 0x0008AAE0, 83 bytes.
//
// The reference's body unchanged, redundant second tail store included: the
// else arm already sets the tail and the common code sets it again.
//
// The layout falls out of it. The argument count is a single byte at
// this+0x18 -- incremented in cl, not a register-width add -- with the list
// head at +0x1C and the tail at +0x20. An argument is 0x1C bytes with its next
// link at +0x04 behind the pool object's vptr, and nothing else in it is
// touched, so its constructor is just that vptr.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
struct GameMessageArgument
{
	virtual ~GameMessageArgument();				// pool object vptr, this+0x00

	GameMessageArgument *m_next;				// this+0x04
	char m_bfme_body[0x1C - 0x08];				// sizeof is the pushed 0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
protected:
	GameMessageArgument *allocArg(void);

	char m_slice_pad[0x18];					// retail this+0x00 .. +0x17, untouched
	UnsignedByte m_argCount;				// this+0x18
	char m_slice_padB[0x1C - 0x19];
	GameMessageArgument *m_argList;				// this+0x1C
	GameMessageArgument *m_argTail;				// this+0x20
};

GameMessageArgument *GameMessage::allocArg( void )
{
	// allocate a new argument
	GameMessageArgument *arg = new GameMessageArgument;

	// add to end of argument list
	if (m_argTail)
		m_argTail->m_next = arg;
	else
	{
		m_argList = arg;
		m_argTail = arg;
	}

	arg->m_next = 0;
	m_argTail = arg;

	m_argCount++;

	return arg;
}
