// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport
// Retail 0x0023A730 is slot 3 in the secondary interface installed at
// complete-object +0xE4 by HordeContain, AODHordeContain, and
// HorseHordeContain constructors. Thus this-0xDC reads complete-object +8.
// The slot's semantic name and the pointed-to type remain unknown.
#define _STLP_USE_STATIC_LIB 1
#include <list>

class Rva001BF100 {
public:
	void run();
};

class Rva0023A730Receiver {
public:
#define SLOT(N) virtual void slot##N() = 0
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05);
	SLOT(06); SLOT(07); SLOT(08); SLOT(09); SLOT(10); SLOT(11);
	SLOT(12); SLOT(13); SLOT(14); SLOT(15); SLOT(16); SLOT(17);
	SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29);
	SLOT(30); SLOT(31); SLOT(32); SLOT(33); SLOT(34); SLOT(35);
	SLOT(36); SLOT(37); SLOT(38); SLOT(39); SLOT(40); SLOT(41);
	SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53);
	SLOT(54); SLOT(55); SLOT(56); SLOT(57); SLOT(58); SLOT(59);
#undef SLOT
	virtual void slot60(_STL::list<Rva001BF100 *> *items) = 0;
};

void Rva0023A730Receiver::slot03()
{
	Rva001BF100 *atPrimaryPlus08 = *reinterpret_cast<Rva001BF100 **>(
		reinterpret_cast<char *>(this) - 0xDC);
	atPrimaryPlus08->run();
	_STL::list<Rva001BF100 *> items;
	slot60(&items);
	for (_STL::list<Rva001BF100 *>::iterator it = items.begin();
		it != items.end(); ++it)
	{
		(*it)->run();
	}
}
