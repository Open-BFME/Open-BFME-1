// cl: /Iinputs/reference/shims/stringinline
#include "StringInline.h"
void __cdecl operator delete(void *block);

extern void j_0002756b();

class BfmeChildYJ
{
public:
	void bfmeCleanYJ();
};

typedef void (BfmeChildYJ::*CleanCall)();

union CleanTarget
{
	void (*freeFunction)();
	CleanCall memberFunction;
};

class BfmeOwnerYJ
{
public:
	~BfmeOwnerYJ();

	AsciiString m_bfmeTextYJ;
	unsigned char m_bfmePadYJ[0x38];
	BfmeChildYJ *m_bfmeChildYJ;
};

BfmeOwnerYJ::~BfmeOwnerYJ()
{
	BfmeChildYJ *child = m_bfmeChildYJ;

	if (child != 0)
	{
		CleanTarget target = { &j_0002756b };
		(child->*target.memberFunction)();
		operator delete(child);
	}
}
