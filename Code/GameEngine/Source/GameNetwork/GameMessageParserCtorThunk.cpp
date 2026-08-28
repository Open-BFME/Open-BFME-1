// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the GameMessageParser(GameMessage *) MASM dump to clean C++.
//
// Zero Hour's body is GameMessageParser.cpp:38 and BFME kept it unchanged: run-
// length encode the message's argument types, emitting one addArgType per run.
// BFME's object has one more field than the reference -- +4, +8 and +0xC are all
// zeroed, and it is +0xC that addArgType's counter increments.
//
// getArgumentCount is inlined to a byte load from the message at +0x18, so it is
// modelled as an inline accessor rather than a call; getArgumentDataType and
// addArgType are unnamed in the ledger and pinned at their ILT thunks.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	unsigned char getArgumentCount(void) const { return m_argCount; }

	int getArgumentDataType(int index);			///< ILT 0x0001A3D4

	unsigned char m_unreconstructed_00[0x18];
	unsigned char m_argCount;					///< retail msg+0x18
};

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_UNKNOWN = 12
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParser
{
public:
	GameMessageParser(GameMessage *msg);
	virtual ~GameMessageParser();

protected:
	void addArgType(int type, int count);		///< ILT 0x0000B569

	void *m_first;								///< retail this+0x04
	void *m_last;								///< retail this+0x08
	int m_argTypeCount;							///< retail this+0x0C
};

// ??0GameMessageParser@@QAE@PAVGameMessage@@@Z
GameMessageParser::GameMessageParser(GameMessage *msg)
{
	m_first = 0;
	m_last = 0;
	m_argTypeCount = 0;

	unsigned char argCount = msg->getArgumentCount();
	int lasttype = ARGUMENTDATATYPE_UNKNOWN;
	int thisTypeCount = 0;

	for (unsigned char i = 0; i < argCount; ++i)
	{
		int type = msg->getArgumentDataType(i);

		if (type != lasttype)
		{
			if (thisTypeCount > 0)
			{
				addArgType(lasttype, thisTypeCount);
				++m_argTypeCount;
			}

			lasttype = type;
			thisTypeCount = 0;
		}

		++thisTypeCount;
	}

	if (thisTypeCount > 0)
	{
		addArgType(lasttype, thisTypeCount);
		++m_argTypeCount;
	}
}
