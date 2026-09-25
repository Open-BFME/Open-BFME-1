// BFME RecorderClass::updateRecord reconstruction.
// cl: /ICode/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

struct _iobuf;
typedef _iobuf FILE;

typedef int Int;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl fclose(FILE *file);
extern "C" __declspec(dllimport) int __cdecl fflush(FILE *file);

class AsciiString
{
public:
	AsciiString() { base()->StringBase<char>::StringBase(); }
	AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
	AsciiString(const char *text) { base()->StringBase<char>::StringBase(text); }
	~AsciiString() { base()->releaseBuffer(); }
	void clear() { base()->releaseBuffer(); }

private:
	StringBase<char> *base() { return (StringBase<char> *)this; }
	const StringBase<char> *base() const { return (const StringBase<char> *)this; }
	StringBase<char>::Header *m_data;
};

union GameMessageArgumentType
{
	Int integer;
	char payload[12];
};

class GameMessage
{
public:
	enum Type
	{
		MSG_CLEAR_GAME_DATA = 0x1d,
		MSG_NEW_GAME = 0x1e,
		MSG_BEGIN_NETWORK_MESSAGES = 0x3e8,
		MSG_END_NETWORK_MESSAGES = 0x7cf
	};

	virtual ~GameMessage();
	GameMessage *next() const { return m_next; }
	Type getType() const { return m_type; }
	UnsignedByte getArgumentCount() const { return m_argCount; }
	const GameMessageArgumentType *getArgument(Int index) const;

private:
	GameMessage *m_next;
	GameMessage *m_prev;
	void *m_list;
	Type m_type;
	Int m_playerIndex;
	UnsignedByte m_argCount;
	char m_padding[3];
	Int m_reserved1;
	Int m_reserved2;
};

class CommandList
{
public:
	virtual void slot0();
	Int m_state;
	GameMessage *m_firstMessage;
	GameMessage *m_lastMessage;

	GameMessage *getFirstMessage() const { return m_firstMessage; }
};

extern CommandList *TheCommandList;

class NetworkInterface;
extern NetworkInterface *TheNetwork;

class RecorderClass
{
public:
	void updateRecord();

protected:
	void writeToFile(GameMessage *message);
	void logGameEnd();
	void Rva0009B6C0RecorderStart(Int difficulty, Int gameMode, Int rankPoints, Int maxFPS);

private:
	char m_prefix[0x0c];
	FILE *m_file;
	AsciiString m_fileName;
	char m_gap[0x29c - 0x14];
	Int m_originalGameMode;
	char m_gap2[0x2ac - 0x2a0];
	Int m_gameMode;
};

enum
{
	GAME_LAN = 1,
	GAME_SHELL = 4,
	GAME_INTERNET = 5,
	DIFFICULTY_NORMAL = 1
};

void RecorderClass::updateRecord()
{
	Bool needFlush = false;
	static Int lastFrame = -1;
	GameMessage *message = TheCommandList->getFirstMessage();
	while (message != 0) {
		if (message->getType() == GameMessage::MSG_NEW_GAME) {
			Int gameMode = message->getArgument(0)->integer;
			if (gameMode == GAME_SHELL)
				return;
			if (gameMode != GAME_LAN && gameMode != GAME_INTERNET)
				return;
			m_gameMode = message->getArgument(0)->integer;
			lastFrame = 0;
			Int difficulty = DIFFICULTY_NORMAL;
			if (message->getArgumentCount() >= 2)
				difficulty = message->getArgument(1)->integer;
			Int rankPoints = 0;
			if (message->getArgumentCount() >= 3)
				rankPoints = message->getArgument(2)->integer;
			Int maxFPS = 0;
			if (message->getArgumentCount() >= 4)
				maxFPS = message->getArgument(3)->integer;
			Rva0009B6C0RecorderStart(difficulty, m_gameMode, rankPoints, maxFPS);
		} else if (message->getType() == GameMessage::MSG_CLEAR_GAME_DATA) {
			if (m_file != 0) {
				lastFrame = -1;
				writeToFile(message);
				logGameEnd();
				if (TheNetwork != 0)
					m_originalGameMode = -1;
				if (m_file != 0) {
					fclose(m_file);
					m_file = 0;
				}
				m_fileName.clear();
			}
			m_fileName.clear();
		} else {
			if (m_file != 0) {
				if (message->getType() > GameMessage::MSG_BEGIN_NETWORK_MESSAGES
						&& message->getType() < GameMessage::MSG_END_NETWORK_MESSAGES) {
					writeToFile(message);
					needFlush = true;
				}
			}
		}
		message = message->next();
	}
	if (!needFlush)
		return;
	fflush(m_file);
}
