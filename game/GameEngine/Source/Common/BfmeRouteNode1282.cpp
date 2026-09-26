// The 0x008BEBF0 submitter calls this helper with its own object in ECX.
// Its node argument is the node-detail record at +0x50, and the second
// argument controls the optional 0x200 emission before the secondary scan.

class BfmeNodeDX
{
public:
	void bfmeEmit1281(int mode, void *tail, int enabled);

	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x50 - 0x08];
	void *m_detail;
};

class Rva008ACFC0RegisteredObject
{
};

class Rva008ACFC0PointerRegistry
{
public:
	void add(Rva008ACFC0RegisteredObject *object);
	int m_cursor;
	int m_values[512];
};

class Rva008AD000
{
public:
	unsigned char has(int value);
	int m_count;
	int m_values[512];
};

class BfmeRef008A4B20
{
};

class BfmePtrTable64_008A4B20
{
public:
	void add(BfmeRef008A4B20 *object);

private:
	int m_count;
	BfmeRef008A4B20 *m_values[64];
};

struct BfmeFlagEntry1282
{
	unsigned int m_flags;
	int m_unused04;
	int m_unused08;
};

struct BfmeFlagList1282
{
	int m_count;
	BfmeFlagEntry1282 *m_entries;
};

struct BfmeNodeDetail1282
{
	char m_padding00[0x0c];
	int *m_type;
	char m_padding10[0x20 - 0x10];
	BfmeFlagList1282 *m_flags;
};

struct BfmeManager1282
{
	char m_padding000[0x14];
	Rva008ACFC0PointerRegistry m_all;
	char m_padding818[0x924 - 0x818];
	BfmePtrTable64_008A4B20 m_primary;
	Rva008AD000 m_secondary;
};

extern BfmeManager1282 *g_bfmeHolderBU;
extern void *g_bfmeExtra1282;
extern unsigned char g_bfmeDispatchEnabled1281;
extern unsigned char g_bfmeSecondaryEnabled1282;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeSubmitter1283
{
public:
	void bfmeRouteNode1282(BfmeNodeDX *node, int emit);
};

static __forceinline void bfmeEmit1282(void *extra, BfmeNodeDX *node)
{
	node->bfmeEmit1281(0x200, extra, 1);
}

void BfmeSubmitter1283::bfmeRouteNode1282(BfmeNodeDX *node, int emit)
{
	BfmeNodeDetail1282 *detail = (BfmeNodeDetail1282 *)node->m_detail;
	int type = *detail->m_type;
	if (type == 4) {
		for (int index = 0; index < 512; ++index) {
			if (g_bfmeHolderBU->m_all.m_values[index] == (int)node)
				return;
		}
		g_bfmeHolderBU->m_all.add((Rva008ACFC0RegisteredObject *)node);
		return;
	}
	if (type == 5) {
		if (g_bfmeHolderBU->m_secondary.has((int)node))
			return;
		BfmeFlagList1282 *flags = detail->m_flags;
		if (emit != 0) {
			void *extra = g_bfmeExtra1282;
			_ReadWriteBarrier();
			bfmeEmit1282(extra, node);
		}
		if (flags == 0)
			return;
		for (int index = 0; index < flags->m_count; ++index) {
			if ((flags->m_entries[index].m_flags & 0x27cf8) != 0) {
				((Rva008ACFC0PointerRegistry *)&g_bfmeHolderBU->m_secondary)->add(
					(Rva008ACFC0RegisteredObject *)node);
				return;
			}
		}
		return;
	}
	if (type == 2 && g_bfmeDispatchEnabled1281 == 1 && g_bfmeSecondaryEnabled1282 == 1) {
		g_bfmeHolderBU->m_primary.add((BfmeRef008A4B20 *)node);
		((Rva008ACFC0PointerRegistry *)&g_bfmeHolderBU->m_secondary)->add(
			(Rva008ACFC0RegisteredObject *)node);
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
