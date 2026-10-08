// Retail VA 0x01073734 is Gdiplus::Bitmap's vtable, emitted by the existing
// ATL image TUs; its deleting-destructor slot routes to 0x0005E110.
extern "C" unsigned char __identifier("bfmeVftAPA")[];

namespace Gdiplus { class GpBitmap; }
// Existing import-stub owners: GdipCreateBitmapFromFileICM and
// GdipCreateBitmapFromFile, respectively; both take two stdcall arguments.
extern void ji_009f6bf2();
extern void ji_009f6bec();
typedef int (__stdcall *BitmapFromFile)(const unsigned short *, Gdiplus::GpBitmap **);
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
	m_bfmeVft = __identifier("bfmeVftAPA");
	Gdiplus::GpBitmap *got = 0;
	if (two != 0)
	{
		m_bfmeWhat = (void *)(reinterpret_cast<BitmapFromFile>(ji_009f6bf2))((const unsigned short *)one, &got);
		m_bfmeGot = (int)got;
	}
	else
	{
		m_bfmeWhat = (void *)(reinterpret_cast<BitmapFromFile>(ji_009f6bec))((const unsigned short *)one, &got);
		m_bfmeGot = (int)got;
	}
	return this;
}

// ?bfmeInitScan0APA@BfmeThingAPA@@QAEPAV1@PAX0000@Z
BfmeThingAPA *BfmeThingAPA::bfmeInitScan0APA(void *width, void *height, void *stride, void *format, void *scan0)
{
	m_bfmeVft = __identifier("bfmeVftAPA");
	int got = 0;
	m_bfmeWhat = GdipCreateBitmapFromScan0(width, height, stride, format, scan0, &got);
	m_bfmeGot = got;
	return this;
}
