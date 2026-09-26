// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class GameLogicFrameSlice
{
public:
	unsigned int m_pad[0x3C / sizeof(unsigned int)];
	unsigned int m_frame;
};

extern GameLogicFrameSlice *TheGameLogic;

class Rva0022CD20Obj
{
public:
	bool pending() const;

private:
	char m_pad[0xAC];
	unsigned int m_frame;
};

bool Rva0022CD20Obj::pending() const
{
	return TheGameLogic->m_frame < m_frame;
}
