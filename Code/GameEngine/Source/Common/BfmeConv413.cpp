extern "C" unsigned char bfmeVftAPA[];

void *__stdcall bfmeOneAPA(void *one, int *got);
void *__stdcall bfmeTwoAPA(void *one, int *got);

class BfmeThingAPA
{
public:
	BfmeThingAPA *bfmeInitAPA(void *one, void *two);
	void *m_bfmeVft;
	int m_bfmeGot;
	void *m_bfmeWhat;
};

BfmeThingAPA *BfmeThingAPA::bfmeInitAPA(void *one, void *two)
{
	m_bfmeVft = bfmeVftAPA;
	int got = 0;
	if (two != 0)
	{
		m_bfmeWhat = bfmeOneAPA(one, &got);
		m_bfmeGot = got;
	}
	else
	{
		m_bfmeWhat = bfmeTwoAPA(one, &got);
		m_bfmeGot = got;
	}
	return this;
}
