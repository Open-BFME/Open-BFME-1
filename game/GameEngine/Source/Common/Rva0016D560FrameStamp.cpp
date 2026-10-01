// Open-BFME5: clean C++ conversion of the conditional frame-stamp refresh.

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the frame field at +0x3C
// through its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

struct Rva0016D560GameLogic
{
	char m_pad00[0x3C];
	unsigned int m_frame;
};

class Rva0016D560Stamp
{
public:
	int refreshFrameStamp();

private:
	char m_pad00[0x24];
	unsigned int m_frameStamp;
};

int Rva0016D560Stamp::refreshFrameStamp()
{
	if (m_frameStamp != 0)
		m_frameStamp = ((Rva0016D560GameLogic *)TheGameLogic)->m_frame + 5;
	else
		m_frameStamp = ((Rva0016D560GameLogic *)TheGameLogic)->m_frame;

	return 0;
}
