// cl: /O2 /Ob0

struct Rva0075BD90Sub
{
};

class Rva0075BD90Base
{
public:
	virtual void *s00(); virtual void *s04(); virtual void *s08(); virtual void *s0C();
	virtual void *s10(); virtual void *s14(); virtual void *s18(); virtual void *s1C();
	virtual void *s20(); virtual void *s24(); virtual void *s28(); virtual void *s2C();
	virtual void *s30(); virtual void *s34(); virtual void *s38(); virtual void *s3C();
	virtual void *s40(); virtual void *s44(); virtual void *s48(); virtual void *s4C();
	virtual void *s50(); virtual void *s54(); virtual void *s58(); virtual void *s5C();
	virtual void *s60(); virtual void *s64(); virtual void *s68(); virtual void *s6C();
	virtual void *s70(); virtual void *s74(); virtual void *s78(); virtual void *s7C();
	virtual void *s80(); virtual void *s84(); virtual void *s88(); virtual void *s8C();
	virtual void *s90(); virtual void *s94(); virtual void *s98(); virtual void *s9C();
	virtual void *sA0(); virtual void *sA4(); virtual void *sA8(); virtual void *sAC();
	virtual void *sB0(); virtual void *sB4();
	virtual Rva0075BD90Sub *foo();
};

class Rva0075BD90
{
public:
	Rva0075BD90Sub *get();
};

Rva0075BD90Sub *Rva0075BD90::get()
{
	Rva0075BD90Sub *p = ((Rva0075BD90Base *)((char *)this - 0x0C))->foo();
	if (p)
		return (Rva0075BD90Sub *)((char *)p + 0xA4);
	return 0;
}
