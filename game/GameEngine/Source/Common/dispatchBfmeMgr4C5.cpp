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

// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse; (defined once in
// GameClient/Input/Mouse.cpp).  This TU keeps its own view of the layout and
// casts at the use so the reference links to the one global.
class Mouse;
extern Mouse *TheMouse;

void dispatchBfmeMgr4C5()
{
	BfmeMgr4C5 *m = (BfmeMgr4C5 *)TheMouse;
	if (m->mode == 40)
		m->dispatch(1);
	else
		m->dispatch(40);
}
