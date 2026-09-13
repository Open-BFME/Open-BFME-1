// cl: /DNDEBUG /MD /EHsc

// Three destructible members and no vptr -- the name says QAE, so the destructor
// is not virtual and the class has no base with a table.
//
// They go in reverse declaration order with the unwind state counting down 1, 0,
// -1: the wide string at +0x3A0, then the array at +0x58, then the narrow string
// at +0x3C. The middle one is destroyed through the vector destructor iterator,
// whose four arguments spell the array out completely -- element destructor,
// count 8, element size 0x68, and the base address.
//
// Both strings inline their destructor down to the private releaseBuffer of the
// StringBase they derive from, wide and narrow reaching different ones.
template <class T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();

	T *m_data;
};

class BFMERetailAsciiString : public StringBase<char>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	~LANPlayer();

private:
	unsigned char m_body[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	~LANGameInfo();

private:
	unsigned char m_gap0[0x3C];
	BFMERetailAsciiString m_name;
	unsigned char m_gap1[0x18];
	LANPlayer m_players[8];
	unsigned char m_gap2[0x08];
	UnicodeString m_text;
};

// ??1LANGameInfo@@QAE@XZ
LANGameInfo::~LANGameInfo()
{
}
