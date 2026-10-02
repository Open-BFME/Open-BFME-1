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
extern void j_00024c17();
extern void j_000125b7();
extern void j_000279d0();

struct Gen00026AB2
{
	Gen00026AB2() : m_start(0), m_finish(0), m_end(0) {}
	~Gen00026AB2();
	void rva00774B60Clear()
	{
		union { void (*raw)(); void *(Gen00026AB2::*member)(void *, void *); } fn;
		fn.raw = j_00024c17;
		(this->*fn.member)(m_start, m_finish);
	}

	void *m_start;
	void *m_finish;
	Rva00776330Pointer m_end;
};

struct Gen_uwm_000134ad
{
	Gen_uwm_000134ad() : m_start(0), m_finish(0), m_end(0) {}
	~Gen_uwm_000134ad();
	void rva00774B60Clear()
	{
		union { void (*raw)(); void *(Gen_uwm_000134ad::*member)(void *, void *); } fn;
		fn.raw = j_000125b7;
		(this->*fn.member)(m_start, m_finish);
	}

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
	void rva00774B60Clear()
	{
		union { void (*raw)(); void (BfmeTreeAt9C::*member)(); } fn;
		fn.raw = j_000279d0;
		(this->*fn.member)();
	}
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
struct Rva00774B60Turret
{
	unsigned word00, word04, word08, word0C, word10, word14;
	void rva00774B60Reset()
	{
		word00 = 0;
		word04 = 0;
		word08 = 0;
		word0C = 0;
		word10 = 0;
		word14 = 0;
	}
};
// The remaining scalar fields retain offsets until independently named.
struct Rva00774B60Tail
{
	unsigned wordC0, wordC4, wordC8, wordCC, wordD0, wordD4, wordD8;
	unsigned wordDC, wordE0, wordE4;
	float wordE8;
	unsigned char byteEC, byteED, byteEE, byteEF;

};
extern void j_0003ab11();
class ModelConditionInfo
{
public:
	~ModelConditionInfo();
	ModelConditionInfo();
	void clear();

private:
	Rva00776330Words m_at00;
	Gen00026AB2 m_at28;
	AsciiString m_at34;
	unsigned char m_byte38;
	char m_pad39[3];
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
	unsigned short m_wordB8;
	char m_padBA[2];
	AsciiString m_atBC;
	Rva00774B60Tail m_atC0;
	Rva00774B60Turret m_turrets[2];
	unsigned m_word120;
	unsigned char m_byte124;
	char m_pad125[3];
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

// ZH ModelConditionInfo::clear is the constructor's sole body call.
// BFME also clears its additional model-condition fields and fifth string array.
void ModelConditionInfo::clear()
{
	m_at00.words.reset();
	m_at28.rva00774B60Clear();
	m_at34.clear();
	m_at40.rva00774B60Clear();
	m_at9C.rva00774B60Clear();
	m_atA0.rva00774B60Clear();
	m_at3C.clear();
	m_byte38 = 0;
	for (int i = 0; i < 4; ++i) {
		m_names4C[i].clear();
		m_names5C[i].clear();
		m_names6C[i].clear();
		m_names7C[i].clear();
		m_names8C[i].clear();
	}
	for (int i = 0; i < 2; ++i)
		m_turrets[i].rva00774B60Reset();
	m_byte124 = 0;
	m_atBC.clear();
	m_wordB8 = 0;
	m_atC0.wordC0 = 0;
	m_atC0.wordC4 = 0;
	m_atC0.wordC8 = 0;
	m_atC0.wordCC = 0;
	m_atC0.wordD0 = 0;
	m_atC0.wordD4 = 0;
	m_atC0.wordDC = 0;
	m_atC0.wordE0 = 0;
	m_atC0.wordE4 = 0;
	m_atC0.byteEC = 0;
	m_atC0.byteED = 0;
	m_atC0.wordD8 = 255;
	m_atC0.wordE8 = 20.0f;
	m_atC0.byteEE = 1;
}
