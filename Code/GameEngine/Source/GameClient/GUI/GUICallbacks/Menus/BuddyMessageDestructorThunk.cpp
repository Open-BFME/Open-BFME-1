// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BuddyMessage dtor. members @+0x08/+0x10/+0x14.

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	unsigned char m_pad[4];
};

class CountUpBuffer
{
public:
	~CountUpBuffer();
private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class BuddyMessage
{
public:
	~BuddyMessage();
private:
	unsigned char m_gap[8];
	BFMERetailAsciiString m_a; // +0x08
	unsigned char m_gap2[4]; // +0x0c
	BFMERetailAsciiString m_b; // +0x10
	CountUpBuffer m_c; // +0x14
};

// Destruction: 14, 10, 8 -> calls 8881d0, 887940, 887940
// ??1BuddyMessage@@QAE@XZ
BuddyMessage::~BuddyMessage()
{
}
