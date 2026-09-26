class BfmeSinkBLC
{
public:
	void *bfmeMakeBLC(void *what);
};

extern BfmeSinkBLC *g_bfmeSinkBLC;

class BfmeThingBLC
{
public:
	void bfmeGoBLC(void *what);
	void *m_bfmeGot;
};

void BfmeThingBLC::bfmeGoBLC(void *what)
{
	m_bfmeGot = g_bfmeSinkBLC->bfmeMakeBLC(what);
}
