// cl: /O1
extern "C" unsigned char bfmeVftUE[];

void bfmeFreeUE(void *what);

class BfmeThingUE
{
public:
	void bfmeDtorUE();
	void *bfmeKillUE(int flags);
	void *m_bfmeVft;
};

void *BfmeThingUE::bfmeKillUE(int flags)
{
	m_bfmeVft = bfmeVftUE;
	bfmeDtorUE();
	if ((flags & 1) != 0)
		bfmeFreeUE(this);
	return this;
}
