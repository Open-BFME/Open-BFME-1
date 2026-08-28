// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameSpyGroupRoom dtor. AsciiString @+0 then UnicodeString @+4.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();

private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyGroupRoom
{
public:
	~GameSpyGroupRoom();

private:
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

// ??1GameSpyGroupRoom@@QAE@XZ
GameSpyGroupRoom::~GameSpyGroupRoom()
{
}
