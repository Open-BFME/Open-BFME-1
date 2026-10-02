class BfmeThingDDE
{
public:
	int bfmeGoDDE();
	unsigned char m_bfmeHead[8];
	void *m_bfmeSub;
	unsigned char m_bfmeGap[0x3a];
	bool m_bfmeFlag;
	unsigned char m_bfmeGap2[0x11];
	int m_bfmeVal;
};

extern "C" void __identifier("?j_0000adfd@@YAXXZ")(void);

int BfmeThingDDE::bfmeGoDDE()
{
	if (m_bfmeFlag && m_bfmeSub != 0)
		__identifier("?j_0000adfd@@YAXXZ")();
	return m_bfmeVal;
}
