// ?bfmeCheckGD@@YADPAVBfmeObjGD@@@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 57/57 exact size; retail places the shared return-0 block EARLY at +0x09 and
// jumps BACKWARD to it from the flags test, MSVC places it at the tail.
// Pins: ?bfmeGetGD@... 0x000022BB, ?bfmeValueGD@... 0x0003A391
class BfmeThingGD
{
public:
	unsigned char m_bfmeHeadGD[0xc8];
	unsigned char m_bfmeFlagsGD;
};

class BfmeInnerGD
{
public:
	BfmeThingGD *bfmeGetGD(void);
};

class BfmeHolderGD
{
public:
	unsigned char m_bfmeHeadGD[4];
	BfmeInnerGD *m_bfmeInnerGD;
};

class BfmeObjGD
{
public:
	int bfmeValueGD(void);

	unsigned char m_bfmeHeadGD[4];
	BfmeHolderGD *m_bfmeHolderGD;
};

char __cdecl bfmeCheckGD(BfmeObjGD *obj)
{
	if (obj == 0)
		return 0;

	BfmeHolderGD *holder = obj->m_bfmeHolderGD;
	BfmeThingGD *thing = (BfmeThingGD *)holder;

	if (holder != 0 && holder->m_bfmeInnerGD != 0)
		thing = holder->m_bfmeInnerGD->bfmeGetGD();

	if ((thing->m_bfmeFlagsGD & 4) != 0)
		return 0;

	return obj->bfmeValueGD() == 1;
}
