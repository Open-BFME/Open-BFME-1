// cl: /DNDEBUG /MD /EHs-c-

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : m_bfmeThing(0) {}
	void *m_bfmeThing;
};

class Gen_00929A20
{
public:
	char m_bfmeHead[0xB4];
	void *m_bfmeArrays[8];
};

class Gen_0092F070
{
public:
	BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;
	char m_bfmeHead[0x9C];
	Gen_00929A20 *m_cur;
};

class BfmeThingBUZA
{
public:
	BfmeHandleCX bfmeGoBUZA(int a, int b) const;
};

class Gen_00945B20
{
public:
	BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;

private:
	Gen_0092F070 *m_model;
};

BfmeHandleCX Gen_00945B20::bfmeGet(int pidx, int pass, int stage) const
{
	volatile int dead = 0;
	Gen_0092F070 *model = m_model;
	Gen_00929A20 *desc = model->m_cur;
	if (desc->m_bfmeArrays[stage + pass * 2])
		return model->bfmeGet(pidx, pass, stage);
	return ((BfmeThingBUZA *)model)->bfmeGoBUZA(pass, stage);
}
