// cl: /DNDEBUG /MD /EHsc

// Retail 0x00517720 (268 B with its jump table): the debug name of a LAN
// lobby client state, CS_INIT through CS_GAME_STARTED, returned by value and
// defaulting to "Unknown state".  Nothing calls it through its ILT thunk at
// 0x0002E05A, so the owner is unknown and the name is the address's.
//
// The four string calls are the shared StringBase<char> bodies: the
// const char * and copy constructors and releaseBuffer (the inline
// destructor), plus AsciiString::operator=(const char *) through its ILT.

template <class T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *s);
	StringBase(const StringBase &other);
	void releaseBuffer();

	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }

	AsciiString &operator=(const char *s);
};

enum Rva00517720ClientState
{
	CS_INIT,
	CS_LOBBY_ACTIVE,
	CS_HOST_SETUP_REQUEST,
	CS_HOST_SETUP_WAIT,
	CS_HOST_SETUP_ACTIVE,
	CS_HOST_START_REQUEST,
	CS_HOST_START_WAIT,
	CS_JOIN_SETUP_REQUEST,
	CS_JOIN_SETUP_WAIT,
	CS_JOIN_ACTIVE,
	CS_JOIN_ACCEPT_WAIT,
	CS_GAME_STARTED,
};

AsciiString Rva00517720ClientStateName(Rva00517720ClientState state)
{
	AsciiString name("Unknown state");
	switch (state)
	{
		case CS_INIT: name = "CS_INIT"; break;
		case CS_LOBBY_ACTIVE: name = "CS_LOBBY_ACTIVE"; break;
		case CS_HOST_SETUP_REQUEST: name = "CS_HOST_SETUP_REQUEST"; break;
		case CS_HOST_SETUP_WAIT: name = "CS_HOST_SETUP_WAIT"; break;
		case CS_HOST_SETUP_ACTIVE: name = "CS_HOST_SETUP_ACTIVE"; break;
		case CS_HOST_START_REQUEST: name = "CS_HOST_START_REQUEST"; break;
		case CS_HOST_START_WAIT: name = "CS_HOST_START_WAIT"; break;
		case CS_JOIN_SETUP_REQUEST: name = "CS_JOIN_SETUP_REQUEST"; break;
		case CS_JOIN_SETUP_WAIT: name = "CS_JOIN_SETUP_WAIT"; break;
		case CS_JOIN_ACTIVE: name = "CS_JOIN_ACTIVE"; break;
		case CS_JOIN_ACCEPT_WAIT: name = "CS_JOIN_ACCEPT_WAIT"; break;
		case CS_GAME_STARTED: name = "CS_GAME_STARTED"; break;
	}
	return name;
}
