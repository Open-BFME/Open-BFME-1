// cl: /DNDEBUG /MD /EHsc

// LANGameSlot::setLogin(AsciiString), 0x006853C0, 75 bytes.
//
// One line, and the offset is the whole identification: it translates the
// by-value AsciiString into the UnicodeString at this+0x48. In the
// LANGameSlot layout the destructor and copy constructor pin, +0x44 is
// LANPlayer m_user and +0x48 is that player's m_login, so this is the
// reference's `inline void setLogin(AsciiString name) { m_user.setLogin(name); }`
// with LANPlayer::setLogin -- itself a one-liner -- inlined into it. The
// reference declares a UnicodeString overload beside it; that one would not
// call translate.
//
// The inner setter takes a const reference here rather than the reference's
// by-value AsciiString. That is not cosmetic either: by value MSVC has to
// build a second copy of the parameter and reserves a frame slot for it, which
// costs the body twenty-six bytes it does not have. Nothing outside this file
// sees the difference -- the inner setter is inlined and emits no symbol.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();				// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	void translate(const AsciiString &src);		// retail 0x008891F0

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	void setLogin(const AsciiString &name) { m_login.translate(name); }

	UnicodeString m_name;				// this+0x00
	UnicodeString m_login;				// this+0x04
	UnicodeString m_host;				// this+0x08
	UnsignedByte m_bfmeTail[0x1C - 0x0C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	UnsignedByte m_bfmeBody[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	void setLogin(AsciiString name);

private:
	LANPlayer m_user;				// this+0x44
	void *m_serial;					// this+0x60
	UnsignedInt m_lastHeard;			// this+0x64
};

// ?setLogin@LANGameSlot@@QAEXVAsciiString@@@Z
void LANGameSlot::setLogin(AsciiString name)
{
	m_user.setLogin(name);
}
