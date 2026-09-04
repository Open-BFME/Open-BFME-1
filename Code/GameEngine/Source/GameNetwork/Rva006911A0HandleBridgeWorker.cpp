// cl: /DNDEBUG /MD /EHs-c-

typedef unsigned char UnsignedByte;

class Gen_00690fe0
{
public:
	void *m();
};

class Gen0002857E;

class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle()
	{
		((Gen_00690fe0 *)this)->m();
	}
	Rva00690FF0Handle(Gen0002857E *target);
};

class Rva006911A0Handle
{
public:
	Rva00690FF0Handle construct();
	void *m_target;
};

Rva00690FF0Handle Rva006911A0Handle::construct()
{
	void * volatile unused;
	void *target = m_target;
	unused = 0;
	if (!target)
	{
		return Rva00690FF0Handle();
	}
	if (*(UnsignedByte *)((char *)target + 0x41) == 0)
	{
		return Rva00690FF0Handle();
	}
	return Rva00690FF0Handle((Gen0002857E *)target);
}
