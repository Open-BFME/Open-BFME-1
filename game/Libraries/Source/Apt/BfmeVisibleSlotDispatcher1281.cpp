class BfmeNodeDX;

struct BfmePickWorld1284;			// retail global 0x013377D8, defined in BfmePicker1284.cpp
extern BfmePickWorld1284 *g_bfmeHolderBU;

// the 0x008A0C30 slot's owner is Gen_008A0C30 (functions.csv), not the global's type
class Gen_008A0C30
{
public:
	bool bfmeAllows(BfmeNodeDX *node) const;
};

class BfmeNodeDX
{
public:
	void bfmeEmit1281(int mode, void *tail, int zero);
};

class BfmeSlotDispatcher1281
{
public:
	void bfmeApplySlot1281(void *entry, int mode, void *tail);
	void bfmeDispatchVisible1281(int unused, void *tail);

private:
	char m_padding000[0x820];
	int m_primaryCount;
	BfmeNodeDX *m_primary[64];
	char m_padding924[0xA28 - 0x924];
	int m_secondaryCount;
	BfmeNodeDX *m_secondary[512];
};

void BfmeSlotDispatcher1281::bfmeDispatchVisible1281(int, void *tail)
{
	int visited = 0;
	for (int index = 0; index < 512 && visited != m_secondaryCount; ++index) {
		BfmeNodeDX *entry = m_secondary[index];
		if (entry != 0) {
			if (!reinterpret_cast<Gen_008A0C30 *>(g_bfmeHolderBU)->bfmeAllows(entry)) {
				entry->bfmeEmit1281(0x40, tail, 0);
				++visited;
			}
		}
	}

	visited = 0;
	for (int index = 0; index < 64 && visited != m_primaryCount; ++index) {
		BfmeNodeDX *entry = m_primary[index];
		if (entry != 0) {
			bfmeApplySlot1281(entry, 0x40, tail);
			++visited;
		}
	}
}

// BfmeSlotDispatcher1281::bfmeApplySlot1281 (retail 0x008BB200, 468 B).
// Identity: bfmeDispatchVisible1281 above (matched, 0x008BC090) calls it with
// mode 0x40, and symbols.csv pins this address-derived name at 0x008BB200;
// retail ends with ret 0xC at +0x1D1 and INT3 follows.
// For each of the six {mask, key} records at VA 0x012D59D4 whose mask meets
// `mode`, look the key up on the entry (0x0089C290); a live node of type 10
// with bit 15 set is either handed to the route manager (0x008A08F0) as is,
// when the entry already owns it, or cloned for the entry through the 0x34-byte
// headered objects built at 0x008D6290 / 0x008D62F0. The retail unwind map
// proves the clone pair: state 0 frees through operator delete 0x008BA800,
// state 1 through 0x008BA870. No layout witness exists, so members keep their
// offsets. Spellings the bytes decide: `tail` is read through its address
// (retail never keeps it in a register), the 7-bit field is extracted before
// the 8-bit one, the owned-node path is the else arm (retail places it last),
// and each clone arm reloads the detail pointer itself (MSVC hoists the pair
// into EBP but keeps the two submissions apart).

class BfmeItemDX;
void __cdecl bfmePush(BfmeItemDX *item);
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

extern "C" int __identifier("bfmeObjDAE")[1];
#define g_bfmeRouteKeys1282 __identifier("bfmeObjDAE")

struct BfmeRouteMask1281
{
	int m_mask;
	int m_key;
};

extern BfmeRouteMask1281 g_Va012D59D4[6];

class BfmeN1034;

class BfmeRouteManager1282
{
public:
	void produce(void *entry, BfmeN1034 *node, int value, int tail);
};

class BfmeNode1220
{
public:
	int bfmeTest1220(int *key, int zero);
};

class Rva008BA800HeaderedDelete
{
public:
	static void operator delete(void *storage, unsigned int size);
};

class Rva008BA870HeaderedDelete
{
public:
	static void operator delete(void *storage, unsigned int size);
};

struct Rva8CE5C0Detail
{
	int m_unused00;
	int m_value04;
};

class Rva8CE5C0Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18();
	virtual int kind4C();

	unsigned m_flags;
	char m_gap08[0x18];
	int m_value20;
	int m_value24;
	void *m_owner28;
	char m_gap2c[4];
	Rva8CE5C0Detail *m_detail30;
};

// 0x34-byte clones; operator new is the headered allocator inlined
// (out-of-line copy at 0x008BA840).
class Rva8CE5C0Object : public Rva8CE5C0Value, public Rva008BA800HeaderedDelete
{
public:
	Rva8CE5C0Object(void *record, Rva8CE5C0Value *top, int property, void *context);
	__forceinline static void *operator new(unsigned int bytes)
	{
		char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
		char *block = raw + 8;
		bfmePush((BfmeItemDX *)block);
		return block;
	}
};

class Rva008D62F0Object : public Rva8CE5C0Value, public Rva008BA870HeaderedDelete
{
public:
	Rva008D62F0Object(void *record, Rva8CE5C0Value *top, int property, void *context);
	__forceinline static void *operator new(unsigned int bytes)
	{
		char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
		char *block = raw + 8;
		bfmePush((BfmeItemDX *)block);
		return block;
	}
};

void BfmeSlotDispatcher1281::bfmeApplySlot1281(void *entry, int mode, void *tail)
{
	for (int *key = &g_Va012D59D4[0].m_key; (int)key < (int)&g_Va012D59D4[6].m_key; key += 2) {
		if ((key[-1] & mode) == 0)
			continue;
		Rva8CE5C0Value *node = (Rva8CE5C0Value *)((BfmeNode1220 *)entry)->bfmeTest1220(
			&g_bfmeRouteKeys1282[*key], 0);
		if (node == 0)
			continue;
		unsigned flags = node->m_flags;
		if ((flags & 0x8000) == 0 || (flags & 0x3f) != 10 ||
			((unsigned char)~(flags >> 15) & 1) != 0)
			continue;

		unsigned raw = *(unsigned *)&tail;
		unsigned bits = (raw >> 10) & 0x7f;
		unsigned type = (raw >> 2) & 0xff;
		int routeValue = 0;
		if (type == 1 && (bits & 7) != 0) {
			Rva8CE5C0Detail *info = node->m_detail30;
			routeValue = info->m_value04;
		}

		if (node->m_owner28 != entry) {
			Rva8CE5C0Detail *detail;
			if (node->kind4C() == 1) {
				detail = node->m_detail30;
				Rva8CE5C0Object *copy = new Rva8CE5C0Object(detail,
					(Rva8CE5C0Value *)node->m_value20, node->m_value24, entry);
				copy->m_flags = (copy->m_flags & 0xffffc07f) | 0x40;
				((BfmeRouteManager1282 *)g_bfmeHolderBU)->produce(entry, (BfmeN1034 *)copy, routeValue, (int)tail);
			} else {
				detail = node->m_detail30;
				Rva008D62F0Object *copy = new Rva008D62F0Object(detail,
					(Rva8CE5C0Value *)node->m_value20, node->m_value24, entry);
				copy->m_flags = (copy->m_flags & 0xffffc07f) | 0x40;
				((BfmeRouteManager1282 *)g_bfmeHolderBU)->produce(entry, (BfmeN1034 *)copy, routeValue, (int)tail);
			}
		} else {
			((BfmeRouteManager1282 *)g_bfmeHolderBU)->produce(entry, (BfmeN1034 *)node, 0, (int)tail);
		}
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
