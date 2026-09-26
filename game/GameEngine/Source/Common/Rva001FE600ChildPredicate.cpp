// cl: /DNDEBUG /MD /EHsc
// Address-derived layout: the method follows a pointer at +0xE4 to an
// embedded child slot at +0x14 and accepts an absent child or a zero word.

class Rva001FE600Owner
{
public:
	bool hasNoBlockingChild();
};

struct Rva001FE600Child;

struct Rva001FE600Child
{
	unsigned int m_unknown;
	unsigned short m_word;
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

bool Rva001FE600Owner::hasNoBlockingChild()
{
	unsigned char *owner = *(unsigned char **)((unsigned char *)this - 0x1C);
	owner += 0x14;
	_ReadWriteBarrier();
	Rva001FE600Child *child = *(Rva001FE600Child **)owner;
	return child == 0 || child->m_word == 0;
}
