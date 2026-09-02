// Open-BFME5: clean C++ conversion of the conditional frame-stamp refresh.

struct Rva0016D560GameLogic
{
	char m_pad00[0x3C];
	unsigned int m_frame;
};

extern Rva0016D560GameLogic *g_bfmeClockBN;

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
		m_frameStamp = g_bfmeClockBN->m_frame + 5;
	else
		m_frameStamp = g_bfmeClockBN->m_frame;

	return 0;
}
