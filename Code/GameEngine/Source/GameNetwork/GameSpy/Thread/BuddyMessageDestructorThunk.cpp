// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BuddyMessage dtor. members @+0x08/+0x10/+0x14.

class Buffer
{
public:
	~Buffer();
private:
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
	Buffer m_a; // +0x08
	unsigned char m_gap2[4]; // +0x0c
	Buffer m_b; // +0x10
	CountUpBuffer m_c; // +0x14
};

// Destruction: 14, 10, 8 -> calls 8881d0, 887940, 887940
// ??1BuddyMessage@@QAE@XZ
BuddyMessage::~BuddyMessage()
{
}
