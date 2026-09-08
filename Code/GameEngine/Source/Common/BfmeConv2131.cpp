void __cdecl operator delete(void *p);

class BfmeThingCDE;

class BfmeSubABI
{
public:
	virtual void bfmeSlot0ABI();
	virtual void bfmeSlot1ABI();
	virtual void bfmeSlot2ABI();
	virtual void bfmeSlot3ABI();
	virtual BfmeThingCDE *bfmeGetABI();
};

class BfmeThingCDE
{
public:
	bool bfmeCheckABI();
	void bfmeDtorCDE();

	void *m_bfme00ABI;
	void *m_bfme04ABI;
};

void __stdcall bfmeReleaseABI(void *owner);

void __stdcall bfmeReleaseABI(void *owner)
{
	if (owner == 0)
		return;

	if (((BfmeSubABI *)((char *)owner + *(int *)(*(char **)((char *)owner + 4) + 4) + 4))->bfmeGetABI() == 0)
		return;

	BfmeThingCDE *t = ((BfmeSubABI *)((char *)owner + *(int *)(*(char **)((char *)owner + 4) + 4) + 4))->bfmeGetABI();

	if (t->m_bfme04ABI != owner)
		return;

	if (t->bfmeCheckABI())
		return;

	t->bfmeDtorCDE();
	::operator delete(t);
}
