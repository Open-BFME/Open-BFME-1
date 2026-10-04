#include <string.h>

void bfmeUnpackTwoColors1280(float *output, const unsigned int *colors);

// Retail reached these bodies through incremental-link thunks; call the
// thunks directly instead of aliasing a misspelled member name onto them.
extern void d_008be760();
extern void d_008b06c0();
extern void d_008cc690();

struct BfmeIterator1285 { void *m_data; unsigned m_extra; };
class BfmeIteratorList1285
{
public:
	BfmeIterator1285 *bfmeFirst1285();
	BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *);
};

class Rva008CF3C0String;
class Rva008A9B00;
class Rva008CF3C0State
{
public:
	void append(void *, void *, Rva008CF3C0String *, Rva008A9B00 *, int, int, int);
};

struct Rva008AE770Stack {};
extern Rva008AE770Stack Rva008AE770TheStack;

struct Words008BEBF0Six { unsigned words[6]; };
struct Words008BEBF0Eight { unsigned words[8]; };

class BfmeNodeDX
{
public:
	void *vptr;
	union
	{
		unsigned flags;
		struct { unsigned kindBits:6; unsigned spareBits:9; unsigned validBit:1; unsigned highBits:16; };
	};
	unsigned field08[2];
	Words008BEBF0Six field10;
	Words008BEBF0Eight field28;
	unsigned field48;
	unsigned field4c;
	char *field50;
	void finish008B06C0();
};

class Value008BEBF0
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual BfmeIteratorList1285 *list();
	union
	{
		unsigned flags;
		struct { unsigned lowBits:15; unsigned validBit:1; unsigned highBits:16; };
	};
};

class BfmeSubmitter1283
{
public:
	void bfmeSubmit1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		float *colors, int a9, int a10, int a11, int zero);
	void create008BE760(int, void *, int, int, int, int, BfmeNodeDX **, int *);
	void bfmeRouteNode1282(BfmeNodeDX *, int);
	void bfmeSubmitColors1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		const unsigned int *colors, int a9, int a10, int a11);
};

void BfmeSubmitter1283::bfmeSubmit1283(int nodeArg, int a2, int a3, int a4, int a5, int a6, int a7,
	float *a8, int a9, int a10, int a11, int a12)
{
	typedef void (BfmeSubmitter1283::*CreateFn)(int, void *, int, int, int, int, BfmeNodeDX **, int *);
	union { void (*fn)(); CreateFn call; } create = { d_008be760 };
	typedef void (BfmeNodeDX::*FinishFn)();
	union { void (*fn)(); FinishFn call; } finish = { d_008b06c0 };
	typedef void (Rva008CF3C0State::*AppendFn)(void *, void *, Rva008CF3C0String *, Rva008A9B00 *, int, int, int);
	union { void (*fn)(); AppendFn call; } append = { d_008cc690 };
	BfmeNodeDX *a1 = (BfmeNodeDX *)nodeArg;
	float *colors = a8;
	int created = 0;
	void *input = (void *)a3;
	BfmeNodeDX *node = (BfmeNodeDX *)a1;
	if (input) {
		if (!node) {
			BfmeNodeDX *createdNode;
			(this->*create.call)(a2, input, a4, a5, a6, a7, &createdNode, &created);
			node = createdNode;
		}
	}
	if (!node) return;
	if (!node->field48) {
		if (colors) node->field28 = *(Words008BEBF0Eight *)colors;
		if (a9) node->field10 = *(Words008BEBF0Six *)a9;
	}
	if (a10) *(int *)(node->field50 + 0x20) = a10;
	if (node->kindBits == 17 && !((unsigned char)~(node->flags >> 15) & 1))
		*(int *)(node->field50 + 0x18) = a11;
	if (created) bfmeRouteNode1282(node, 1);
	if (((node->flags & 63) == 13 && !((unsigned char)~(node->flags >> 15) & 1)) ||
		((node->flags & 63) == 18 && !((unsigned char)~(node->flags >> 15) & 1))) {
		Value008BEBF0 *value = (Value008BEBF0 *)a12;
		if (value && value->validBit) {
			a1 = (BfmeNodeDX *)value->list();
			for (BfmeIterator1285 *it = ((BfmeIteratorList1285 *)a1)->bfmeFirst1285();
				it; it = ((BfmeIteratorList1285 *)a1)->bfmeNext1285(it)) {
				if (strcmp((char *)it->m_data + 8, "__proto__") &&
					strcmp((char *)it->m_data + 8, "prototype"))
					(((Rva008CF3C0State *)&Rva008AE770TheStack)->*append.call)(node, 0,
						(Rva008CF3C0String *)it, (Rva008A9B00 *)(it->m_extra & ~1), 1, 1, 0);
			}
		}
		(node->*finish.call)();
	}
}

void BfmeSubmitter1283::bfmeSubmitColors1283(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, const unsigned int *colors, int a9, int a10, int a11)
{
	float unpacked[8];
	if (colors != 0) {
		bfmeUnpackTwoColors1280(unpacked, colors);
		bfmeSubmit1283(a1, a2, a3, a4, a5, a6, a7, unpacked, a9, a10, a11, 0);
	} else {
		bfmeSubmit1283(a1, a2, a3, a4, a5, a6, a7, 0, a9, a10, a11, 0);
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
