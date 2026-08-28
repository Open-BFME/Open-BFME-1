struct BfmeThingCPC
{
	bool bfmeCheckCPC(int value);
	unsigned char m_bfmeHead[0x204];
	void *m_bfmeMid;
};

bool __stdcall bfmeAskCPC(BfmeThingCPC *thing);

bool __stdcall bfmeGoCPC(BfmeThingCPC *thing)
{
	if (bfmeAskCPC(thing) && thing->m_bfmeMid != 0 && !thing->bfmeCheckCPC(2))
		return true;
	return false;
}
