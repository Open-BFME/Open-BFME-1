// A clip taken up for playing when nothing else is in the way.

struct BfmeFrameZZ
{
	int m_bfmeFirst;			// 0x0
	int m_bfmeSecond;			// 0x4
	int m_bfmeThing;			// 0x8
};

struct BfmeClipZZ
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeFrameZZ *m_bfmeFrames;		// 0x10
	int m_bfmeCount;			// 0x14
};

class BfmeThingZZ
{
public:
	unsigned char bfmeStartZZ(BfmeClipZZ *clip, int mark);

private:
	unsigned char m_bfmeHead[0x28];		// 0x00
	int m_bfmeMark;				// 0x28
	unsigned char m_bfmeGap[8];		// 0x2c
	unsigned char m_bfmeDone;		// 0x34
	unsigned char m_bfmeSpare[3];		// 0x35
	int m_bfmeBusy;				// 0x38
	BfmeClipZZ *m_bfmeClip;			// 0x3c
	int m_bfmeThing;			// 0x40
};

unsigned char BfmeThingZZ::bfmeStartZZ(BfmeClipZZ *clip, int mark)
{
	if (m_bfmeBusy == 0 && m_bfmeClip == 0)
	{
		m_bfmeClip = clip;

		int count = clip->m_bfmeCount;
		int frame = 0;

		if (count <= 0)
			frame = count - 1;

		m_bfmeThing = clip->m_bfmeFrames[frame].m_bfmeThing;
		m_bfmeMark = mark;
		m_bfmeDone = 0;

		return 1;
	}

	return 0;
}
