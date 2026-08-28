// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The string-valued members of the NetCommandMsg family.
//
// These are split out from NetCommandMsg_ctors.cpp because they need a real
// StringBase declaration, and the constructors there deliberately model the
// string fields as opaque pointers -- every one of them only ever zeroes the
// field, so a pointer is enough and a real class would drag the copy
// constructor into bodies that never call it.
//
// BFME's UnicodeString and AsciiString ARE StringBase<unsigned short> and
// StringBase<char>, not wrappers around them: the getters below call the
// StringBase copy constructor at 0x00888400 (and its char twin at 0x00887B60)
// directly, where a wrapper would have gone through UnicodeString's own at
// 0x000682C0. So the return type is the template instantiation and the
// mangled names carry ?$StringBase@G rather than UnicodeString.
//
// StringBase's copy constructor, default constructor and destructor are all
// private -- that is the AAE in their mangled names -- so every class holding
// one has to be a friend. The friend list is an artefact of that, not something
// modelled from retail.
//
// The setters call ?set@?$StringBase@D@@QAEXABV1@@Z at 0x00887C90 rather than
// operator=, which is the 19-byte forwarder at 0x008881B0. Retail really does
// write m_x.set(s), not m_x = s.

template <typename T>
class StringBase
{
	friend class NetDisconnectChatCommandMsg;
	friend class NetChatCommandMsg;
	friend class BFMENetRequestGameSpyStatsAuthKeyCommandMsg;
	friend class BFMENetGameSpyStatsAuthKeyCommandMsg;
	friend class NetFileCommandMsg;
	friend class NetFileAnnounceCommandMsg;

public:
	void clear();
	void set(const StringBase<T> &src);

	// Inline, and it really is inline in retail: assignment through it lands
	// straight on set() at 0x00887C90, never on the out-of-line operator=
	// forwarder at 0x008881B0.
	StringBase<T> &operator=(const StringBase<T> &src) { set(src); return *this; }

private:
	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &src);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

typedef StringBase<unsigned short> UnicodeString;
typedef StringBase<char> AsciiString;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandMsg()
	{
		m_executionFrame = -1;
		m_id = 0;
		m_playerID = 0;
		m_timestamp = 0;
		m_referenceCount = 1;
		m_commandType = NETCOMMANDTYPE_UNKNOWN;
	}

	virtual ~NetCommandMsg() {}

protected:
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	NetCommandType m_commandType;					// this+0x14
	Int m_referenceCount;							// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	UnicodeString getText();
	void setText(UnicodeString text);

	UnicodeString m_text;							// this+0x1C

protected:
	virtual ~NetDisconnectChatCommandMsg();
};

NetDisconnectChatCommandMsg::~NetDisconnectChatCommandMsg()
{
}

void NetDisconnectChatCommandMsg::setText(UnicodeString text)
{
	m_text = text;
}

UnicodeString NetDisconnectChatCommandMsg::getText()
{
	return m_text;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetChatCommandMsg : public NetCommandMsg
{
public:
	UnicodeString getText();
	void setText(UnicodeString text);

	UnicodeString m_text;							// this+0x1C
	Int m_playerMask;								// this+0x20

protected:
	virtual ~NetChatCommandMsg();
};

NetChatCommandMsg::~NetChatCommandMsg()
{
}

void NetChatCommandMsg::setText(UnicodeString text)
{
	m_text = text;
}

UnicodeString NetChatCommandMsg::getText()
{
	return m_text;
}

// Command types 5 and 6 are BFME's own -- the reference's NetworkDefs.h has no
// GameSpy stats-authkey types at all, and its NetCommandMsg.h has no class for
// them. Retail ships without RTTI, so the class names below are built from the
// constant each constructor stamps, in the BFMENet* style the rest of this tree
// uses for BFME-only additions.
//
// The field names are deliberately offset-suffixed. What the two strings on the
// type-6 command mean is not recoverable from the image: the caller at 0x00665AD0
// fills the first from a locally built string and the second from a virtual call
// on the global at 0x012F71B4, and neither site carries a literal that names
// them. The repo already uses this convention where semantics are unrecoverable
// (copyState6C, findList90, pushQueue0). The offsets themselves are exact.

class BFMENetRequestGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg();

	AsciiString getText1C();
	void setText1C(AsciiString text);

	AsciiString m_text1C;							// this+0x1C

protected:
	// MAE, not UAE: retail's destructor is protected, the same as the base's at
	// 0x006737E0. The family is reference-counted through detach(), so nothing
	// outside deletes one directly.
	virtual ~BFMENetRequestGameSpyStatsAuthKeyCommandMsg();
};

BFMENetRequestGameSpyStatsAuthKeyCommandMsg::BFMENetRequestGameSpyStatsAuthKeyCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY;
}

BFMENetRequestGameSpyStatsAuthKeyCommandMsg::~BFMENetRequestGameSpyStatsAuthKeyCommandMsg()
{
}

AsciiString BFMENetRequestGameSpyStatsAuthKeyCommandMsg::getText1C()
{
	return m_text1C;
}

void BFMENetRequestGameSpyStatsAuthKeyCommandMsg::setText1C(AsciiString text)
{
	m_text1C = text;
}

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();

	AsciiString getText1C();
	void setText1C(AsciiString text);
	AsciiString getText20();
	void setText20(AsciiString text);

	AsciiString m_text1C;							// this+0x1C
	AsciiString m_text20;							// this+0x20
};

BFMENetGameSpyStatsAuthKeyCommandMsg::BFMENetGameSpyStatsAuthKeyCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY;
}

AsciiString BFMENetGameSpyStatsAuthKeyCommandMsg::getText1C()
{
	return m_text1C;
}

void BFMENetGameSpyStatsAuthKeyCommandMsg::setText1C(AsciiString text)
{
	m_text1C = text;
}

AsciiString BFMENetGameSpyStatsAuthKeyCommandMsg::getText20()
{
	return m_text20;
}

void BFMENetGameSpyStatsAuthKeyCommandMsg::setText20(AsciiString text)
{
	m_text20 = text;
}


// Both file commands store only the portable form of the map path and convert on
// the way out, exactly as the reference does. The pair of converters lives on
// GameState, reached through the global at 0x012EF190, and is called directly
// rather than virtually.
//
// The assignment in setRealFilename goes to ?set@?$StringBase@D@@QAEXABV1@@Z, not
// to operator=: retail inlines AsciiString's operator= down to the set() call,
// where this tree's operator= is the 19-byte forwarder at 0x008881B0. Writing
// set() here reproduces retail; writing = would add that hop.
void __cdecl operator delete[](void *block) throw();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
	AsciiString portableMapPathToRealMapPath(const AsciiString &path) const;
	AsciiString realMapPathToPortableMapPath(const AsciiString &path) const;
};

GameState *TheGameState;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileCommandMsg : public NetCommandMsg
{
public:
	NetFileCommandMsg();
	AsciiString getRealFilename();
	void setRealFilename(AsciiString filename);

	AsciiString m_portableFilename;					// this+0x1C
	UnsignedByte *m_data;							// this+0x20
	UnsignedInt m_dataLength;						// this+0x24

protected:
	virtual ~NetFileCommandMsg();
};

NetFileCommandMsg::NetFileCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_FILE;
	m_data = 0;
	m_portableFilename.clear();
	m_dataLength = 0;
}

NetFileCommandMsg::~NetFileCommandMsg()
{
	if (m_data != 0) {
		::operator delete[](m_data);
		m_data = 0;
	}
}

AsciiString NetFileCommandMsg::getRealFilename()
{
	return TheGameState->portableMapPathToRealMapPath(m_portableFilename);
}

void NetFileCommandMsg::setRealFilename(AsciiString filename)
{
	m_portableFilename = TheGameState->realMapPathToPortableMapPath(filename);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	NetFileAnnounceCommandMsg();

	AsciiString getRealFilename();
	void setRealFilename(AsciiString filename);

	AsciiString m_portableFilename;					// this+0x1C
	UnsignedShort m_fileID;							// this+0x20
	UnsignedByte m_playerMask;						// this+0x22

protected:
	virtual ~NetFileAnnounceCommandMsg();
};

NetFileAnnounceCommandMsg::NetFileAnnounceCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_FILEANNOUNCE;
	m_portableFilename.clear();
	m_fileID = 0;
	m_playerMask = 0;
}

NetFileAnnounceCommandMsg::~NetFileAnnounceCommandMsg()
{
}

AsciiString NetFileAnnounceCommandMsg::getRealFilename()
{
	return TheGameState->portableMapPathToRealMapPath(m_portableFilename);
}

void NetFileAnnounceCommandMsg::setRealFilename(AsciiString filename)
{
	m_portableFilename = TheGameState->realMapPathToPortableMapPath(filename);
}
