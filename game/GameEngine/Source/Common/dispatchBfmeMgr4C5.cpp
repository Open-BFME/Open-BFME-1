// Clean reconstruction of the retail dispatcher at RVA 0x005639B0.

class BfmeMgr4C5
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void dispatch(int value);

	char padding[0x4DA4];
	int mode;
};

extern BfmeMgr4C5 *g_mgr12F4C5C;

void dispatchBfmeMgr4C5()
{
	if (g_mgr12F4C5C->mode == 40)
		g_mgr12F4C5C->dispatch(1);
	else
		g_mgr12F4C5C->dispatch(40);
}
