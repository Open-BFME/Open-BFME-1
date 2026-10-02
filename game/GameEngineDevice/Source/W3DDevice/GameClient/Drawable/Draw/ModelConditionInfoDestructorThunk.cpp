// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <memory>
#include <bitset>
// Open-BFME: ModelConditionInfo has a 0x128-byte BFME layout.  Its callers
// enter through ILT 0x0002306F at retail body RVA 0x0013C3F0; the historical
// ledger row began fourteen bytes late, after the compiler's SEH prologue.

// The final vector pointer is constructed through the allocator proxy in
// STLport _Vector_base; keeping that nested construction preserves EH scheduling.
struct Rva00776330Pointer
{
	Rva00776330Pointer(void *value) : p(value) {}
	void *p;
};
struct Gen00026AB2
{
	Gen00026AB2() : m_start(0), m_finish(0), m_end(0) {}
	~Gen00026AB2();
	void *m_start;
	void *m_finish;
	Rva00776330Pointer m_end;
};

struct Gen_uwm_000134ad
{
	Gen_uwm_000134ad() : m_start(0), m_finish(0), m_end(0) {}
	~Gen_uwm_000134ad();
	void *m_start;
	void *m_finish;
	Rva00776330Pointer m_end;
};

struct Gen00776240Field60
{
	Gen00776240Field60() : m_start(0), m_finish(0), m_end(0) {}
	~Gen00776240Field60();
	void *m_start;
	void *m_finish;
	Rva00776330Pointer m_end;
};

void Gen0082E5F0(void *node, unsigned int size);
// Existing address-derived binding: retail directly calls RVA 0x0082E540.
// The vendored __new_alloc::allocate instead inlines global operator new.
void *Rva0082E540NodeAllocate(unsigned int size);

// RVA 0x00776330 allocates 44 bytes and self-links the first two pointers.
struct Rva00776330Node
{
	Rva00776330Node *next;
	Rva00776330Node *prev;
	char data[0x24];
};
struct BfmeTreeAt9C
{
	BfmeTreeAt9C() : m_header(0)
	{
		Rva00776330Node *node = (Rva00776330Node *)
			Rva0082E540NodeAllocate(sizeof(Rva00776330Node));
		node->next = node;
		node->prev = node;
		m_header = node;
	}
	void clear();
	__forceinline ~BfmeTreeAt9C()
	{
		clear();
		if (m_header != 0) {
			Gen0082E5F0(m_header, 0x2C);
		}
	}
	void *m_header;
};

// The constructor clears ten words before constructing its other members.
struct Rva00776330Words
{
	_STL::bitset<320> words;
};
extern void j_0003ab11();
class ModelConditionInfo
{
public:
	~ModelConditionInfo();
	ModelConditionInfo();

private:
	Rva00776330Words m_at00;
	Gen00026AB2 m_at28;
	AsciiString m_at34;
	int m_unknown38;
	AsciiString m_at3C;
	Gen00026AB2 m_at40;
	AsciiString m_names4C[4];
	AsciiString m_names5C[4];
	AsciiString m_names6C[4];
	AsciiString m_names7C[4];
	AsciiString m_names8C[4];
	BfmeTreeAt9C m_at9C;
	Gen_uwm_000134ad m_atA0;
	Gen00776240Field60 m_atAC;
	int m_unknownB8;
	AsciiString m_atBC;
	char m_unknownC0[0x68];
};

ModelConditionInfo::~ModelConditionInfo()
{
}

// Zero Hour's inline constructor calls clear(). BFME's corresponding call
// enters ILT 0x0003AB11 -> RVA 0x00774B60 (thiscall, no stack arguments).
ModelConditionInfo::ModelConditionInfo()
{
	union {
		void (*raw)();
		void (ModelConditionInfo::*member)();
	} fn;
	fn.raw = j_0003ab11;
	(this->*fn.member)();
}
