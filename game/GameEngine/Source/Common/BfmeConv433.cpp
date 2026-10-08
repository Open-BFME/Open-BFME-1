// retail ILT 0x00046538 -> 0x00478C70 (both calls) is the matched
// GameWindow::winGetUserData row
class GameWindow
{
public:
	void *winGetUserData();
};

class BfmeEndBBA;

struct BfmeGotBBA
{
	unsigned char m_bfmeHead[8];
	BfmeEndBBA *m_bfmeEnd;
};

class BfmeSubBBA;

class BfmeThingBBA
{
public:
	void bfmeGoBBA();
	BfmeSubBBA *m_bfmeSub;
};

void BfmeThingBBA::bfmeGoBBA()
{
	((GameWindow *)((BfmeGotBBA *)((GameWindow *)m_bfmeSub)->winGetUserData())->m_bfmeEnd)->winGetUserData();
}
