// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: GameMessage copy constructor, retail 0x0008AF70, 672 bytes; not in Zero Hour.
// Layout as in GameMessage_allocArg.cpp: count byte +0x18, argument list +0x1C, tail +0x20.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

struct GameMessageLocationRaw { Real x, y, z; };
struct GameMessagePixelRaw { Int x, y; };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
union GameMessageArgumentType
{
	Int integer;
	Real real;
	Bool boolean;
	UnsignedInt id;
	GameMessageLocationRaw location;
	GameMessagePixelRaw pixel;
	struct { Int left, top, right, bottom; } pixelRegion;
	WideChar wideChar;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
struct GameMessageArgument
{
	virtual ~GameMessageArgument();						// pool object vptr, this+0x00
	GameMessageArgument *m_next;				// this+0x04
	GameMessageArgumentType m_data;				// this+0x08
	Int m_type;						// this+0x18, BFME ordinals: SQUADID at 6
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage;

class GameMessageList
{
public:
	virtual ~GameMessageList();
	virtual void init();
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	virtual bool unidentifiedSlot06(int arg);
	virtual void unidentifiedSlot07();
	virtual void unidentifiedSlot08(int arg);
	virtual void appendMessage(GameMessage *message);
	virtual void insertMessage(GameMessage *message, GameMessage *after);
	virtual void removeMessage(GameMessage *message);
};

class GameMessage
{
public:
	typedef GameMessageArgument Argument;

	GameMessage(const GameMessage &source);
	void rva0008B2C0(const GameMessage &source);
	virtual __forceinline ~GameMessage()
	{
		GameMessageArgument *argument, *next;
		for (argument = m_argList; argument != 0; argument = next)
		{
			next = argument->m_next;
			delete argument;
		}

		m_argList = 0;
		if (m_list != 0)
			m_list->removeMessage(this);
	}

	const GameMessageArgumentType *getArgument(Int argIndex) const;

	// ?getArgumentTypeInline@GameMessage@@QBEHH@Z absent-from-retail
	__forceinline Int getArgumentTypeInline(Int argIndex) const
	{
		// getArgumentDataType (0x0008A380) inlined; 12 is BFME's ARGUMENTDATATYPE_UNKNOWN
		if (argIndex >= m_argCount)
			return 12;
		Int i = 0;
		Argument *a;
		for (a = m_argList; a && (i < argIndex); a = a->m_next, ++i);
		if (a != 0)
			return a->m_type;
		return 12;
	}

protected:
	GameMessageArgument *allocArg(void);

private:
	GameMessage *m_next;					// this+0x04
	GameMessage *m_prev;					// this+0x08
	GameMessageList *m_list;						// this+0x0C
	Int m_type;						// this+0x10
	Int m_playerIndex;					// this+0x14
	UnsignedByte m_argCount;				// this+0x18
	Argument *m_argList;					// this+0x1C
	Argument *m_argTail;					// this+0x20
};

GameMessage::GameMessage(const GameMessage &source)
{
	m_playerIndex = source.m_playerIndex;
	m_type = source.m_type;
	m_argList = 0;
	m_argTail = 0;
	m_argCount = 0;
	m_list = 0;
	m_next = 0;
	m_prev = 0;

	for (Int i = 0; i < source.m_argCount; ++i)
	{
		switch (source.getArgumentTypeInline(i))
		{
		case 0: { Int value = source.getArgument(i)->integer; Argument *arg = allocArg(); arg->m_data.integer = value; arg->m_type = 0; break; }
		case 1: { Real value = source.getArgument(i)->real; Argument *arg = allocArg(); arg->m_data.real = value; arg->m_type = 1; break; }
		case 2: { Bool value = source.getArgument(i)->boolean; Argument *arg = allocArg(); arg->m_data.boolean = value; arg->m_type = 2; break; }
		case 3: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 3; break; }
		case 4: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 4; break; }
		case 5: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 5; break; }
		case 6: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 6; break; }
		case 7:
		{
			// member-wise copy keeps all three words in the frame, as retail does
			const GameMessageLocationRaw &from = source.getArgument(i)->location;
			GameMessageLocationRaw value;
			value.x = from.x;
			value.y = from.y;
			value.z = from.z;
			Argument *arg = allocArg();
			arg->m_data.location = value;
			arg->m_type = 7;
			break;
		}
		case 8: { GameMessagePixelRaw value = source.getArgument(i)->pixel; Argument *arg = allocArg(); arg->m_data.pixel = value; arg->m_type = 8; break; }
		case 9: { const GameMessageArgumentType *value = source.getArgument(i); Argument *arg = allocArg(); arg->m_data.pixelRegion = value->pixelRegion; arg->m_type = 9; break; }
		case 10: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 10; break; }
		case 11: { const GameMessageArgumentType *value = source.getArgument(i); Argument *arg = allocArg(); arg->m_data.wideChar = value->wideChar; arg->m_type = 11; break; }
		}
	}
}
void GameMessage::rva0008B2C0(const GameMessage &source)
{
	m_playerIndex = source.m_playerIndex;
	m_type = source.m_type;
	m_argList = 0;
	m_argTail = 0;
	m_argCount = 0;
	m_list = 0;
	m_next = 0;
	m_prev = 0;

	for (Int i = 0; i < source.m_argCount; ++i)
	{
		switch (source.getArgumentTypeInline(i))
		{
		case 0: { Int value = source.getArgument(i)->integer; Argument *arg = allocArg(); arg->m_data.integer = value; arg->m_type = 0; break; }
		case 1: { Real value = source.getArgument(i)->real; Argument *arg = allocArg(); arg->m_data.real = value; arg->m_type = 1; break; }
		case 2: { Bool value = source.getArgument(i)->boolean; Argument *arg = allocArg(); arg->m_data.boolean = value; arg->m_type = 2; break; }
		case 3: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 3; break; }
		case 4: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 4; break; }
		case 5: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 5; break; }
		case 6: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 6; break; }
		case 7:
		{
			// member-wise copy keeps all three words in the frame, as retail does
			const GameMessageLocationRaw &from = source.getArgument(i)->location;
			GameMessageLocationRaw value;
			value.x = from.x;
			value.y = from.y;
			value.z = from.z;
			Argument *arg = allocArg();
			arg->m_data.location = value;
			arg->m_type = 7;
			break;
		}
		case 8: { GameMessagePixelRaw value = source.getArgument(i)->pixel; Argument *arg = allocArg(); arg->m_data.pixel = value; arg->m_type = 8; break; }
		case 9: { const GameMessageArgumentType *value = source.getArgument(i); Argument *arg = allocArg(); arg->m_data.pixelRegion = value->pixelRegion; arg->m_type = 9; break; }
		case 10: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 10; break; }
		case 11: { const GameMessageArgumentType *value = source.getArgument(i); Argument *arg = allocArg(); arg->m_data.wideChar = value->wideChar; arg->m_type = 11; break; }
		}
	}
}
