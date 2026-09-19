// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

struct GameLogicFrameSource
{
	unsigned char m_padding[0x3c];
	UnsignedInt m_frame;
};

#define TheBfmeGameLogic (*(GameLogicFrameSource **)0x012F0898)

class Radar
{
public:
	virtual void queueTerrainRefresh(void);

private:
	unsigned char m_padding[0x1468 - 4];
	UnsignedInt m_queueTerrainRefreshFrame;
};

void Radar::queueTerrainRefresh(void)
{
	m_queueTerrainRefreshFrame = TheBfmeGameLogic->m_frame;
}
