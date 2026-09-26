// cl: /O1
extern "C" unsigned char bfmeVftUF[];

void bfmeFreeUF(void *what);

class BfmeThingUF
{
public:
	void bfmeDtorUF();
	void *bfmeKillUF(int flags);
	void *m_bfmeVft;
};

void *BfmeThingUF::bfmeKillUF(int flags)
{
	m_bfmeVft = bfmeVftUF;
	bfmeDtorUF();
	if ((flags & 1) != 0)
		bfmeFreeUF(this);
	return this;
}
