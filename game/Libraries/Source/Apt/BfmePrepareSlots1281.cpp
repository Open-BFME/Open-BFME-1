// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeNodeDX;

class Gen_008A0C30
{
public:
	bool bfmeAllows(BfmeNodeDX *node) const;
};

class Gen_008D1EB0
{
public:
	bool bfmeIdle() const;
};

class BfmeNode1220
{
public:
	bool bfmeAllows1220();
};

class Rva008D1EE0Chain
{
public:
	bool contains(void *node);
};

class Rva008D1FB0Chain
{
public:
	bool compare(void *node);
};

struct Rva8BB1A0BoundsSource;

struct Rva8BB1A0BoundsCheckThunk
{
	bool contains(Rva8BB1A0BoundsSource *source, void *unused);
};

class BfmeR1227
{
public:
	void bfmeAdd1227(void *payload, void *source, void *extra);
};

struct BfmeRecord1281
{
	int m_mask;
	void *m_payload;
};

struct BfmeDescriptor1281
{
	char m_padding00[0x34];
	int m_count34;
	BfmeRecord1281 *m_records38;
};

struct BfmeNodeInfo1281
{
	char m_padding00[0x0c];
	BfmeDescriptor1281 *m_descriptor0c;
	char m_padding10[0x74 - 0x10];
	unsigned char m_flags74;
};

class BfmeNodeDX
{
public:
	bool bfmeEmit1281(int mode, void *tail, int flag);

	char m_padding00[4];
	unsigned int m_flags04;
	char m_padding08[0x44];
	void *m_source4c;
	BfmeNodeInfo1281 *m_info50;
};

class AptValue;

extern Gen_008A0C30 *g_bfmeHolderBU;
extern AptValue *g_bfmeFallbackDB;
extern unsigned char g_bfmeDispatchEnabled1281;
extern void *g_bfmeExtra1282;

class BfmeSlotDispatcher1281 : public BfmeR1227
{
public:
	void bfmePrepare1281(int group, int slot, unsigned int encoded);

private:
	bool bfmeContains1281(BfmeNodeDX *node, unsigned int encoded)
	{
		return reinterpret_cast<Rva8BB1A0BoundsCheckThunk *>(this)->contains(
			reinterpret_cast<Rva8BB1A0BoundsSource *>(node), (void *)encoded);
	}

	char m_padding000[0x14];
	int m_count14;
	BfmeNodeDX *m_entries18[512];
	char m_padding818[0xA28 - 0x818];
	int m_secondaryCount;
	BfmeNodeDX *m_secondary[512];
	char m_padding122c[0x125c - 0x122c];
	BfmeNodeDX *m_node125c;
	char m_padding1260[4];
	bool m_flag1264;
	BfmeNodeDX *m_node1268;
};

static inline bool bfmeBit15Clear(const BfmeNodeDX *node)
{
	return (static_cast<unsigned char>(~(node->m_flags04 >> 15)) & 1) != 0;
}

void BfmeSlotDispatcher1281::bfmePrepare1281(int group, int slot, unsigned int encoded)
{
	BfmeNodeDX *selected = reinterpret_cast<BfmeNodeDX *>(g_bfmeFallbackDB);
	int consumed = 0;
	bool emitted20 = false;
	bool emitted10 = false;
	int visited = 0;
	int index;
	for (index = 0; index < 512; ++index) {
		if (visited == m_secondaryCount)
			break;
		BfmeNodeDX *entry = m_secondary[index];
		if (entry == 0 || g_bfmeHolderBU->bfmeAllows(entry))
			continue;
		if (g_bfmeDispatchEnabled1281 != 0 &&
			reinterpret_cast<Gen_008D1EB0 *>(entry)->bfmeIdle()) {
			unsigned int flags = entry->m_flags04;
			if ((((flags & 0x3f) == 0xf &&
				  (static_cast<unsigned char>(~(flags >> 15)) & 1) == 0 &&
				  (entry->m_info50->m_flags74 & 8) != 0) ||
				 reinterpret_cast<BfmeNode1220 *>(entry)->bfmeAllows1220()) &&
				bfmeContains1281(entry, encoded)) {
				if (bfmeBit15Clear(selected) ||
					(!reinterpret_cast<Rva008D1EE0Chain *>(entry)->contains(selected) &&
					 reinterpret_cast<Rva008D1FB0Chain *>(entry)->compare(selected)))
					selected = entry;
			}
		}
		switch (slot) {
		case 1:
			if (group == 0) {
				if (g_bfmeDispatchEnabled1281 != 0) {
					entry->bfmeEmit1281(0x20, (void *)encoded, 1);
					emitted20 = true;
				}
			} else {
				entry->bfmeEmit1281(0x80, (void *)encoded, 0);
			}
			break;
		case 0:
			if (group == 0) {
				if (g_bfmeDispatchEnabled1281 != 0) {
					entry->bfmeEmit1281(0x10, (void *)encoded, 1);
					emitted10 = true;
				}
			} else {
				entry->bfmeEmit1281(0x40, (void *)encoded, 0);
				if (consumed == 0)
					consumed = entry->bfmeEmit1281(0x20000, (void *)encoded, 1);
			}
			break;
		}
		++visited;
	}

	m_node1268 = selected;
	if (emitted20) {
		BfmeNodeDX *current = m_node125c;
		if (!bfmeBit15Clear(current)) {
			if (bfmeContains1281(current, encoded) && selected == m_node125c)
				m_node125c->bfmeEmit1281(0x800, (void *)encoded, 1);
			else
				m_node125c->bfmeEmit1281(0x1000, (void *)encoded, 1);
			m_flag1264 = true;
		}
	}
	if (emitted10 && !bfmeBit15Clear(selected)) {
		selected->bfmeEmit1281(0x400, (void *)encoded, 1);
		m_node125c = selected;
	}

	if (slot != 0 || consumed != 0)
		return;
	visited = 0;
	for (index = 0; index < 512; ++index) {
		if (visited == m_count14)
			return;
		BfmeNodeDX *entry = m_entries18[index];
		if (entry == 0 || g_bfmeHolderBU->bfmeAllows(entry))
			continue;
		BfmeDescriptor1281 *descriptor = entry->m_info50->m_descriptor0c;
		for (int record = 0; record < descriptor->m_count34; ++record) {
			if ((descriptor->m_records38[record].m_mask & 0xfe00) != 0 &&
				group == ((entry->m_info50->m_descriptor0c->m_records38[record].m_mask >> 9) & 0x7f)) {
				bfmeAdd1227(&descriptor->m_records38[record].m_payload,
					entry->m_source4c, g_bfmeExtra1282);
				return;
			}
		}
		++visited;
	}
}
