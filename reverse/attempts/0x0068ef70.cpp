// ?d_0068ef70@@YAXXZ
// partial score=0.24 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc

// ?decode@Rva0068EF70@@SA_NPAVGameInfo@@PAEI@Z
// Retail 0x0068EF70, 1881 bytes.  The body is the anonymous BFME serialized
// LAN-game-info decoder.  The wire order is independently witnessed by the
// inverse serializer: map path, port, three network-order dwords, then eight
// 0x44-byte GameSlot records.  A `P` record carries a 26-byte wide name and
// its connection pair; E/M/H/O/C records carry the corresponding AI/open/
// closed state and the four slot bytes.  The caller through the ILT is the
// BFME LAN parser, but it does not name this helper, so the address-derived
// owner is intentional.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef signed char SignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

template <typename T>
struct Rva0068EF70StringData
{
	int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

protected:
	void set(const StringBase<T> &other);
	void set(const T *text, Int length);
	void concat(const T *text);
	Int getLength() const
	{
		return m_data ? (Int)m_data->m_length : 0;
	}

	Rva0068EF70StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	Rva0068EF70StringData<char> *data() const
	{
		return m_data;
	}

	Int getLength() const
	{
		return StringBase<char>::getLength();
	}

	private:
	friend class StringBase<char>;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}

	void concat(const WideChar *text)
	{
		StringBase<WideChar>::concat(text);
	}

	Rva0068EF70StringData<WideChar> *data() const
	{
		return m_data;
	}
};

extern UnsignedByte *readAsciiFieldFromBuffer(UnsignedByte *buffer,
	StringBase<char> *out, UnsignedByte *end);
extern UnsignedByte *readByteFromBuffer(UnsignedByte *buffer,
	UnsignedByte *out, UnsignedByte *end);
extern UnsignedByte *readByteFromBuffer_0068D9C0(UnsignedByte *buffer,
	UnsignedByte *out, UnsignedByte *end);
extern UnsignedByte *readByteFromBuffer_0068D9F0(UnsignedByte *buffer,
	UnsignedByte *out, UnsignedByte *end);
extern UnsignedByte *rva68d830(UnsignedByte *buffer,
	UnsignedShort *out, UnsignedByte *end);
extern UnsignedByte *rva68d7e0(UnsignedByte *buffer,
	UnsignedByte *out, UnsignedInt size, UnsignedByte *end);
extern const UnsignedByte *bfmeReadKM(const UnsignedByte *buffer,
	UnsignedInt *out, const UnsignedByte *end);
extern const UnsignedByte *bfmeReadKJ(const UnsignedByte *buffer,
	UnsignedInt *out, const UnsignedByte *end);

extern AsciiString _Rva00621350GameInfoMapPath(const AsciiString &input,
	Bool option);

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &other);
	~GameSlot();
	virtual void reset();

	void setAccept()
	{
		m_isAccepted = true;
	}
	void unAccept();
	void setMapAvailability(Bool hasMap);
	void setState(SlotState state, UnicodeString name,
		const GameSlotConnectInfo *connectInfo);
	void setPlayerTemplate(Int playerTemplate);

	void setColor(Int color)
	{
		m_color = color;
	}
	void setStartPos(Int startPos)
	{
		m_startPos = startPos;
	}
	void setTeamNumber(Int teamNumber)
	{
		m_teamNumber = teamNumber;
	}
	void setLastFrameInGame(UnsignedInt frame)
	{
		m_lastFrameInGame = frame;
	}

	SlotState m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
	Int m_origColor;
	Int m_origStartPos;
	Int m_origPlayerTemplate;
	UnicodeString m_name;
	UnsignedInt m_IP;
	GameSlotConnectInfo m_connectInfo;
	UnsignedInt m_lastFrameInGame;
	Bool m_disconnected;
	UnsignedByte m_bfmeTail[7];
};

class GameInfo
{
public:
	void setSlot(Int slot, GameSlot slotInfo);
	void setMap(AsciiString mapName);
	void setMapCRC(UnsignedInt mapCRC);
	void setMapSize(UnsignedInt mapSize);
};

class MultiplayerSettings
{
public:
	Int getNumColors() const;
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() const;
};

extern MultiplayerSettings *TheMultiplayerSettings;
extern PlayerTemplateStore *ThePlayerTemplateStore;

// These two callees only expose address-derived body contracts in the target:
// one stores an Int at GameInfo+0x48 and the other stores a raw dword at +0x4c.
// Keep the address in both names until a caller or layout witness identifies
// their semantic fields.
class Rva0061E9C0GameInfo
{
public:
	void store(Int value);
};

class Rva0061E9D0GameInfo
{
public:
	void store(UnsignedInt value);
};

class Rva0068EF70
{
public:
	static Bool decode(GameInfo *game, UnsignedByte *buffer, UnsignedInt size);
};

Bool Rva0068EF70::decode(GameInfo *game, UnsignedByte *buffer,
	UnsignedInt size)
{
	if (!game || !buffer)
		return false;

	UnsignedByte *end = buffer + size;
	AsciiString mapName;
	UnsignedByte *cursor;
	UnsignedByte *previous;
	UnsignedShort port;
	UnsignedInt mapCRC;
	UnsignedInt mapSize;
	UnsignedInt gameOptions;

	previous = buffer;
	cursor = readAsciiFieldFromBuffer(buffer,
		reinterpret_cast<StringBase<char> *>(&mapName), end);
	if (cursor <= previous || cursor > end)
		return false;

	mapName = _Rva00621350GameInfoMapPath(mapName, true);
	if (mapName.data() == 0 || mapName.data()->m_length == 0)
		return false;

	previous = cursor;
	cursor = rva68d830(cursor, &port, end);
	if (cursor <= previous || cursor > end)
		return false;

	previous = cursor;
	cursor = const_cast<UnsignedByte *>(bfmeReadKM(cursor, &mapCRC, end));
	if (cursor <= previous || cursor > end)
		return false;

	previous = cursor;
	cursor = const_cast<UnsignedByte *>(bfmeReadKM(cursor, &mapSize, end));
	if (cursor <= previous || cursor > end)
		return false;

	previous = cursor;
	cursor = const_cast<UnsignedByte *>(bfmeReadKJ(cursor, &gameOptions, end));
	if (cursor <= previous || cursor > end)
		return false;

	GameSlot slots[8];
	GameSlot *slot = slots;
	Int slotIndex = 0;
	for (; slotIndex < 8; ++slotIndex)
	{
		UnsignedByte type;
		UnsignedByte flags;
		SignedByte colorByte;
		SignedByte templateByte;
		SignedByte startByte;
		SignedByte teamByte;
		SignedByte lastFrameByte;
		cursor = readByteFromBuffer(cursor, &type, end);
		if (cursor <= previous || cursor > end)
			return false;
		previous = cursor;

		if (type == 'P')
		{
			UnicodeString name;
			WideChar nameBuffer[13];
			UnsignedInt connectValue;
			UnsignedShort connectPort;

			previous = cursor;
			cursor = rva68d7e0(cursor,
				reinterpret_cast<UnsignedByte *>(nameBuffer), 0x1a, end);
			if (cursor <= previous || cursor > end)
				return false;
			name.concat(nameBuffer);
			if (name.data() == 0 || name.data()->m_length == 0)
				return false;

			previous = cursor;
			cursor = const_cast<UnsignedByte *>(bfmeReadKM(
				cursor, &connectValue, end));
			if (cursor <= previous || cursor > end)
				return false;

			previous = cursor;
			cursor = rva68d830(cursor, &connectPort, end);
			if (cursor <= previous || cursor > end)
				return false;

			GameSlotConnectInfo connectInfo;
			connectInfo.m_nat = connectValue;
			connectInfo.m_port = connectPort;
			slot[slotIndex].setState(SLOT_PLAYER, name, &connectInfo);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9C0(cursor, &flags, end);
			if (cursor <= previous || cursor > end)
				return false;
			if ((flags & 1) != 0)
				slot[slotIndex].setAccept();
			else
				slot[slotIndex].unAccept();
			slot[slotIndex].setMapAvailability((flags >> 1) & 1);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&colorByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			if (colorByte < -1 ||
				colorByte >= TheMultiplayerSettings->getNumColors())
				return false;
			slot[slotIndex].setColor(colorByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&templateByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			if (templateByte < -2 ||
				templateByte >= ThePlayerTemplateStore->getPlayerTemplateCount())
				return false;
			slot[slotIndex].setPlayerTemplate(templateByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&startByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			if (startByte < -1 || startByte >= 8)
				return false;
			slot[slotIndex].setStartPos(startByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&teamByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			if (teamByte < -1 || teamByte >= 4)
				return false;
			slot[slotIndex].setTeamNumber(teamByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&lastFrameByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			if (lastFrameByte < 0 || lastFrameByte > 0x80)
				return false;
			slot[slotIndex].setLastFrameInGame(lastFrameByte);
		}
		else
		{
			if (type == 'E')
			{
				GameSlotConnectInfo connectInfo = { 0, 0 };
				slot[slotIndex].setState(SLOT_EASY_AI,
					UnicodeString::TheEmptyString, &connectInfo);
			}
			else if (type == 'M')
			{
				GameSlotConnectInfo connectInfo = { 0, 0 };
				slot[slotIndex].setState(SLOT_MED_AI,
					UnicodeString::TheEmptyString, &connectInfo);
			}
			else if (type == 'H')
			{
				GameSlotConnectInfo connectInfo = { 0, 0 };
				slot[slotIndex].setState(SLOT_BRUTAL_AI,
					UnicodeString::TheEmptyString, &connectInfo);
			}
			else if (type == 'O')
			{
				GameSlotConnectInfo connectInfo = { 0, 0 };
				slot[slotIndex].setState(SLOT_OPEN,
					UnicodeString::TheEmptyString, &connectInfo);
			}
			else if (type == 'C')
			{
				GameSlotConnectInfo connectInfo = { 0, 0 };
				slot[slotIndex].setState(SLOT_CLOSED,
					UnicodeString::TheEmptyString, &connectInfo);
			}
			else
				return false;

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&colorByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			slot[slotIndex].setColor(colorByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&templateByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			slot[slotIndex].setPlayerTemplate(templateByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&startByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			slot[slotIndex].setStartPos(startByte);

			previous = cursor;
			cursor = readByteFromBuffer_0068D9F0(cursor,
				reinterpret_cast<UnsignedByte *>(&teamByte), end);
			if (cursor <= previous || cursor > end)
				return false;
			slot[slotIndex].setTeamNumber(teamByte);
		}
	}

	for (slotIndex = 0; slotIndex < 8; ++slotIndex)
		game->setSlot(slotIndex, slot[slotIndex]);

	game->setMap(mapName);
	game->setMapCRC(mapCRC);
	game->setMapSize(mapSize);
	Rva0061E9C0GameInfo *portTarget =
		reinterpret_cast<Rva0061E9C0GameInfo *>(game);
	portTarget->store((short)port);
	Rva0061E9D0GameInfo *optionsTarget =
		reinterpret_cast<Rva0061E9D0GameInfo *>(game);
	optionsTarget->store(gameOptions);
	return true;
}
