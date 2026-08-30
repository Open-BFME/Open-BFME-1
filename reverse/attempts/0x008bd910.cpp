// ?bfmeRouteNode1282@@YGXPAVBfmeNodeDX@@H@Z
// partial score=0.96 date=2026-08-30
class BfmeNodeDX
{
public:
	void bfmeEmit1281(int mode, void *tail, int enabled);

	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x50 - 0x08];
	void *m_detail;
};

class Rva008AD000
{
public:
	unsigned char has(int value);
	void bfmeAdd1282(int value);
	int m_count;
	int m_values[512];
};

class BfmePrimarySlots1282
{
public:
	void bfmeAddPrimary1282(int value);

private:
	int m_count;
	int m_values[64];
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
	Rva008AD000 m_all;
	char m_padding818[0x924 - 0x818];
	BfmePrimarySlots1282 m_primary;
	Rva008AD000 m_secondary;
};

extern BfmeManager1282 *g_bfmeHolderBU;
extern void *g_bfmeEmitContext1282;
extern unsigned char g_bfmeDispatchEnabled1281;
extern unsigned char g_bfmeSecondaryEnabled1282;

void __stdcall bfmeRouteNode1282(BfmeNodeDX *node, int emit)
{
	BfmeNodeDetail1282 *detail = (BfmeNodeDetail1282 *)node->m_detail;
	int type = *detail->m_type;
	if (type == 4) {
		for (int index = 0; index < 512; ++index) {
			if (g_bfmeHolderBU->m_all.m_values[index] == (int)node)
				return;
		}
		g_bfmeHolderBU->m_all.bfmeAdd1282((int)node);
		return;
	}
	if (type == 5) {
		if (g_bfmeHolderBU->m_secondary.has((int)node))
			return;
		BfmeFlagList1282 *flags = detail->m_flags;
		if (emit != 0)
			node->bfmeEmit1281(0x200, g_bfmeEmitContext1282, 1);
		if (flags == 0)
			return;
		for (int index = 0; index < flags->m_count; ++index) {
			if ((flags->m_entries[index].m_flags & 0x27cf8) != 0) {
				g_bfmeHolderBU->m_secondary.bfmeAdd1282((int)node);
				return;
			}
		}
		return;
	}
	if (type == 2 && g_bfmeDispatchEnabled1281 == 1 && g_bfmeSecondaryEnabled1282 == 1) {
		g_bfmeHolderBU->m_primary.bfmeAddPrimary1282((int)node);
		g_bfmeHolderBU->m_secondary.bfmeAdd1282((int)node);
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
