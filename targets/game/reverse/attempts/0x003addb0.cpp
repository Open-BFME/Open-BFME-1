// ?d_003addb0@@YAXXZ
// partial score=0.5 date=2026-09-25
// stlport
// cl: /DNDEBUG /MD /EHsc
// partial score=0.50 date=2026-09-25
//
// The matched Glo012F1024Item::bfmeEnter body at RVA 0x003AEE70 calls ILT 0x0002EEEC, which jumps to the body at 0x003ADDB0. The pin at ILT 0x0002EEEC names it Glo012F1024Item::j_0002eeec. Retail ends with ret after 224 bytes. The retail unwind map frees the allocated pointer if the constructor throws.
//
// This source uses explicit allocation and placement construction. The compiler loads fs:[0] before it writes the exception record, as retail does. The probe reports 224 source bytes and 58 non-relocation differences.
//
// The frame listing shows slots for the flag, the raw allocation pointer, and a temporary pointer passed to placement cleanup. The source reserves 12 local bytes while retail reserves 8. The initial STLport vector accessors left 149 differences. Removing the flag local left 121 differences in a 205-byte draft. The next attempt should reduce the frame and match the constructor call sequence.
//
// t=26min model=GPT-6 blocker=stack-frame/constructor-call-layout
#include <vector>

struct BfmeElem20
{
	char m_bfmeHead[0x10];
	unsigned char m_bfmeByte;
	char m_bfmeTail[0x03];
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	void *m_bfmeSub;
	void j_00003f0d(void *item);
};

extern Glo012F1028Type *Glo012F1028;

class Glo012F1024FlagCtor16B
{
public:
	static __forceinline void *operator new(unsigned int size, void *storage) { (void)size; return storage; }
	static void operator delete(void *storage, void *placement) { ::operator delete(storage); (void)placement; }
	Glo012F1024FlagCtor16B(int value, void *addr, unsigned char flag);
	char m_bfmeBody[0x10];
};

class Glo012F1024Item
{
public:
	void j_0002eeec(void);

	char m_bfmePad[0x90];
	std::vector<BfmeElem20> m_bfmeFlag20;
};

void Glo012F1024Item::j_0002eeec(void)
{
	unsigned int index = 0;
	if (m_bfmeFlag20.size() != 0)
	{
		do
		{
			BfmeElem20 *elem = m_bfmeFlag20.begin() + index;
			unsigned char flag;
			void *storage = ::operator new(0x10);
			if (storage != 0)
			{
				flag = elem->m_bfmeByte;
				storage = new (storage) Glo012F1024FlagCtor16B(*(int *)((char *)elem + 4), (void *)((char *)elem + 0xC), flag);
			}
			Glo012F1028->j_00003f0d(storage);
			++index;
		} while (index < m_bfmeFlag20.size());
	}
}
