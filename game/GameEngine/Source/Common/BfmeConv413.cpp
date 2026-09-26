extern "C" unsigned char bfmeVftAPA[];

void *__stdcall bfmeOneAPA(void *one, int *got);
void *__stdcall bfmeTwoAPA(void *one, int *got);
extern "C" void *__stdcall GdipCreateBitmapFromScan0(void *width, void *height, void *stride, void *format, void *scan0, int *got);

class BfmeThingAPA
{
public:
	BfmeThingAPA *bfmeInitAPA(void *one, void *two);
	BfmeThingAPA *bfmeInitScan0APA(void *width, void *height, void *stride, void *format, void *scan0);
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

// ?bfmeInitScan0APA@BfmeThingAPA@@QAEPAV1@PAX0000@Z
BfmeThingAPA *BfmeThingAPA::bfmeInitScan0APA(void *width, void *height, void *stride, void *format, void *scan0)
{
	m_bfmeVft = bfmeVftAPA;
	int got = 0;
	m_bfmeWhat = GdipCreateBitmapFromScan0(width, height, stride, format, scan0, &got);
	m_bfmeGot = got;
	return this;
}
