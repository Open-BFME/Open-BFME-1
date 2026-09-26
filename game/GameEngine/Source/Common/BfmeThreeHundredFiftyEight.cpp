class BfmeThingVA
{
public:
	void bfmeDtorVA();
	void *bfmeKillVA(int flags);
};

void __stdcall bfmeFreeVA(void *what);

void *BfmeThingVA::bfmeKillVA(int flags)
{
	bfmeDtorVA();
	if ((flags & 1) != 0)
		bfmeFreeVA(this);
	return this;
}
