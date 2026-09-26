class BfmeStateXV
{
public:
	char bfmeKindXV();
};

class BfmeThingXV
{
public:
	virtual void bfmeT0XV();
	virtual void bfmeT1XV();
	virtual void bfmeT2XV();
	virtual void bfmeT3XV();
	virtual void bfmeT4XV();
	virtual void bfmeT5XV();
	virtual void bfmeT6XV();
	virtual void bfmeT7XV();
	virtual void bfmeT8XV();
	virtual void bfmeT9XV();
	virtual BfmeStateXV *bfmeStateXV();

	void bfmeStartXV();
	void bfmeStopXV();

	unsigned char m_bfmeHeadXV[0x364];
	char m_bfmeDoneXV;
};

void __stdcall bfmeCheckXV(BfmeThingXV *thing, char flag)
{
	BfmeStateXV *state = thing->bfmeStateXV();

	if (state == 0)
		return;

	if (flag == 0)
	{
		if (state->bfmeKindXV() == 1 && thing->m_bfmeDoneXV == 0)
			thing->bfmeStartXV();
	}
	else
	{
		if (state->bfmeKindXV() == 0 && thing->m_bfmeDoneXV != 0)
			thing->bfmeStopXV();
	}
}
