// cl: /Oy-
// The record's own name written out with its length measured in place, then a
// number written after it in the record's own base. The name-writer is pinned
// by address; the number is turned into text by the runtime.

extern "C" unsigned int __cdecl strlen(const char *at);
#pragma intrinsic(strlen)

extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *out, int base);

class BfmeThingQQ
{
public:
	virtual void bfmeSpare000QQ(void) = 0;
	virtual void bfmeSpare001QQ(void) = 0;
	virtual void bfmeSpare002QQ(void) = 0;
	virtual void bfmeSpare003QQ(void) = 0;
	virtual void bfmeSpare004QQ(void) = 0;
	virtual void bfmeSpare005QQ(void) = 0;
	virtual void bfmeSpare006QQ(void) = 0;
	virtual void bfmeSpare007QQ(void) = 0;
	virtual void bfmeSpare008QQ(void) = 0;
	virtual void bfmeSpare009QQ(void) = 0;
	virtual void bfmeSpare010QQ(void) = 0;
	virtual void bfmeSpare011QQ(void) = 0;
	virtual void bfmeSpare012QQ(void) = 0;
	virtual void bfmeSpare013QQ(void) = 0;
	virtual void bfmeAddQQ(const char *text) = 0;

	void bfmeShowQQ(short what);

	void bfmeSetQQ(const char *at, unsigned int many);

	unsigned char m_bfmeHead[0x9e6c];	// 0x0004
	char m_bfmeName[0x10];			// 0x9e70
	int m_bfmeBase;				// 0x9e80
};

void BfmeThingQQ::bfmeShowQQ(short what)
{
	char tmp[0x14];

	bfmeSetQQ(m_bfmeName, strlen(m_bfmeName));

	bfmeAddQQ(_itoa(what, tmp, m_bfmeBase));
}
