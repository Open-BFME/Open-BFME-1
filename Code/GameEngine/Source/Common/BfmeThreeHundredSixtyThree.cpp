extern "C" unsigned char bfmeVftVF[];

void bfmeFreeSizedVF(void *what, unsigned int bytes);

class BfmeThingVF
{
public:
	void *bfmeKillVF(int flags);
	void *m_bfmeVft;
};

void *BfmeThingVF::bfmeKillVF(int flags)
{
	m_bfmeVft = bfmeVftVF;
	if ((flags & 1) != 0)
		bfmeFreeSizedVF(this, 0xd8);
	return this;
}
