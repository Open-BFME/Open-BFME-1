// cl: /Oy-
// The record's own name written out with its length measured in place, then a
// number written after it in the record's own base. The name-writer is pinned
// by address; the number is turned into text by the runtime.

extern "C" unsigned int __cdecl strlen(const char *at);
#pragma intrinsic(strlen)

extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *out, int base);

class BfmeThingQR
{
public:
	virtual void bfmeSpare000QR(void) = 0;
	virtual void bfmeSpare001QR(void) = 0;
	virtual void bfmeSpare002QR(void) = 0;
	virtual void bfmeSpare003QR(void) = 0;
	virtual void bfmeSpare004QR(void) = 0;
	virtual void bfmeSpare005QR(void) = 0;
	virtual void bfmeSpare006QR(void) = 0;
	virtual void bfmeSpare007QR(void) = 0;
	virtual void bfmeSpare008QR(void) = 0;
	virtual void bfmeSpare009QR(void) = 0;
	virtual void bfmeSpare010QR(void) = 0;
	virtual void bfmeSpare011QR(void) = 0;
	virtual void bfmeSpare012QR(void) = 0;
	virtual void bfmeSpare013QR(void) = 0;
	virtual void bfmeAddQR(const char *text) = 0;

	void bfmeShowQR(unsigned short what);

	void bfmeSetQR(const char *at, unsigned int many);

	unsigned char m_bfmeHead[0x9e6c];	// 0x0004
	char m_bfmeName[0x10];			// 0x9e70
	int m_bfmeBase;				// 0x9e80
};

void BfmeThingQR::bfmeShowQR(unsigned short what)
{
	char tmp[0x14];

	bfmeSetQR(m_bfmeName, strlen(m_bfmeName));

	bfmeAddQR(_itoa(what, tmp, m_bfmeBase));
}
