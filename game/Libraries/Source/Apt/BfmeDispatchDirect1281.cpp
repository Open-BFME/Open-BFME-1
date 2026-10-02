// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// BfmeSlotDispatcher1281::bfmeDispatchDirect1281 (retail 0x008BB720, 1679 B).
// Identity: the matched caller bfmeRouteEncoded1281 (AptInput.cpp, 0x008BCCC0)
// calls it for encoded kind 0, and symbols.csv pins the name at 0x008BB720.
// Member names keep their offsets: no layout witness exists for this class.
// The tail blocks are bfmeBroadcast1282 (0x008BAAB0) inlined for modes
// 0x10, 0x20 and 2; the mode 1 broadcast stays an out-of-line call.

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

class Rva008D1FB0
{
public:
	bool method(void *other);
};

struct Rva8BB1A0BoundsSource;

struct Rva8BB1A0BoundsCheckThunk
{
	bool contains(Rva8BB1A0BoundsSource *source, void *unused);
};

class BfmeN1034;

class BfmeTab1034
{
public:
	BfmeN1034 *bfmeFind1034F(int key);
};

class BfmeEntrySource1282
{
public:
	BfmeTab1034 *bfmeGetLookup1282();
};

class BfmeRouteManager1282
{
public:
	void bfmeSubmit1282(void *entry, BfmeN1034 *node, int zero, int encoded);
};

struct BfmeRecord1281
{
	int m_mask;
	void *m_payload;
};

struct BfmeAudio1281
{
	char m_padding00[8];
	void *m_handle08;
};

struct BfmeDescriptor1281
{
	char m_padding00[0x34];
	int m_count34;
	BfmeRecord1281 *m_records38;
	BfmeAudio1281 **m_audio3c;
};

struct BfmeNodeInfo1281
{
	char m_padding00[0x0c];
	BfmeDescriptor1281 *m_descriptor0c;
	char m_padding10[8];
	int m_flags18;
	int m_state1c;
	char m_padding20[0x74 - 0x20];
	unsigned char m_flags74;
};

struct BfmeNode1285
{
	void bfmeSetState1285(int state);
};

struct BfmeEntry1282;
struct BfmePickNode1284;

class BfmeNodeDX
{
public:
	virtual void bfmeAttach1281();
	virtual void bfmeRelease1281();

	bool bfmeEmit1281(int mode, void *tail, int flag);

	unsigned int m_flags04;
	char m_padding08[0x44];
	BfmeEntrySource1282 *m_source4c;
	BfmeNodeInfo1281 *m_info50;
};

// BfmeOtherLP and BfmeThingLP are real classes (defined in
// game/GameEngine/Source/Common/BfmeTwoHundredThirtyTwo.cpp); no header declares
// them, so name the callee by its defining spelling with a declaration-only
// slice: this body only calls bfmePushLP, never a layout.
class BfmeOtherLP;

class BfmeThingLP
{
public:
	void bfmePushLP(void *what, BfmeOtherLP *other, int note);
};

class BfmeBroadcast1282
{
public:
	void bfmeBroadcast1282(BfmeEntry1282 *entry, int mode);
	void bfmeFlush1282();
};

class BfmePicker1284
{
public:
	BfmePickNode1284 *bfmePick1284(int group, int slot);
};

struct BfmeRoute1281
{
	int m_mask;
	int m_index;
	int m_code;
};

class AptValue;

extern Gen_008A0C30 *g_bfmeHolderBU;
extern AptValue *g_bfmeFallbackDB;
extern void *g_bfmeExtra1282;
extern BfmeRoute1281 g_bfmeRouteTable1282[7];
extern int g_bfmeRouteKeys1282[1];
extern void (__cdecl *g_bfmePlay1282)(void *handle, int zero);

class BfmeSlotDispatcher1281 : public BfmeBroadcast1282
{
public:
	void bfmeDispatchDirect1281(unsigned int encoded);

private:
	char m_padding000[0xA28];
	int m_secondaryCount;
	BfmeNodeDX *m_secondary[512];
	char m_padding122c[0x125c - 0x122c];
	BfmeNodeDX *m_node125c;
	BfmeNodeDX *m_node1260;
	bool m_flag1264;
	BfmeNodeDX *m_node1268;
	BfmeNodeDX *m_node126c;
	int m_mode1270;
	int m_group1274;
	int m_slot1278;
};

static inline bool bfmeBit15Clear(const BfmeNodeDX *node)
{
	return (static_cast<unsigned char>(~(node->m_flags04 >> 15)) & 1) != 0;
}

void BfmeSlotDispatcher1281::bfmeDispatchDirect1281(unsigned int encoded)
{
	BfmeNodeDX *selected = reinterpret_cast<BfmeNodeDX *>(g_bfmeFallbackDB);
	int visited = 0;
	int index;
	for (index = 0; index < 512; ++index) {
		if (visited == m_secondaryCount)
			break;
		BfmeNodeDX *entry = m_secondary[index];
		if (entry == 0 || g_bfmeHolderBU->bfmeAllows(entry))
			continue;
		unsigned int flags = entry->m_flags04;
		if ((flags & 0x3f) != 0xf || (static_cast<unsigned char>(~(flags >> 15)) & 1) != 0)
			entry->bfmeEmit1281(8, (void *)encoded, 1);
		if ((bfmeBit15Clear(m_node125c) || m_flag1264 == true) &&
			reinterpret_cast<Gen_008D1EB0 *>(entry)->bfmeIdle()) {
			flags = entry->m_flags04;
			if ((((flags & 0x3f) == 0xf &&
				  (static_cast<unsigned char>(~(flags >> 15)) & 1) == 0 &&
				  (entry->m_info50->m_flags74 & 8) != 0) ||
				 reinterpret_cast<BfmeNode1220 *>(entry)->bfmeAllows1220()) &&
				reinterpret_cast<Rva8BB1A0BoundsCheckThunk *>(this)->contains(reinterpret_cast<Rva8BB1A0BoundsSource *>(entry), (void *)encoded)) {
				if (bfmeBit15Clear(selected) ||
					(!reinterpret_cast<Rva008D1EE0Chain *>(entry)->contains(selected) &&
					 reinterpret_cast<Rva008D1FB0 *>(entry)->method(selected)))
					selected = entry;
			}
		}
		++visited;
	}

	m_node1268 = selected;
	if (!bfmeBit15Clear(m_node125c)) {
		if (!bfmeBit15Clear(m_node1260) && !reinterpret_cast<Rva8BB1A0BoundsCheckThunk *>(this)->contains(reinterpret_cast<Rva8BB1A0BoundsSource *>(m_node125c), (void *)encoded)) {
			m_node125c->bfmeEmit1281(0x10000, (void *)encoded, 1);
			m_node1260 = reinterpret_cast<BfmeNodeDX *>(g_bfmeFallbackDB);
		} else if (bfmeBit15Clear(m_node1260) && reinterpret_cast<Rva8BB1A0BoundsCheckThunk *>(this)->contains(reinterpret_cast<Rva8BB1A0BoundsSource *>(m_node125c), (void *)encoded)) {
			m_node125c->bfmeEmit1281(0x8000, (void *)encoded, 1);
			m_node1260 = m_node125c;
		}
	}

	if (!bfmeBit15Clear(selected) && selected != m_node1260) {
		BfmeNodeDX *previous = m_node1260;
		if (!bfmeBit15Clear(previous) && previous != m_node125c)
			previous->bfmeEmit1281(0x4000, (void *)encoded, 1);
		m_node1260 = selected;
		selected->bfmeEmit1281(0x2000, (void *)encoded, 1);
	} else if (!bfmeBit15Clear(m_node1260) && selected != m_node1260 &&
			   bfmeBit15Clear(m_node125c) && !reinterpret_cast<Rva8BB1A0BoundsCheckThunk *>(this)->contains(reinterpret_cast<Rva8BB1A0BoundsSource *>(m_node1260), (void *)encoded)) {
		m_node1260->bfmeEmit1281(0x4000, (void *)encoded, 1);
		m_node1260 = reinterpret_cast<BfmeNodeDX *>(g_bfmeFallbackDB);
	}

	m_group1274 = encoded >> 17;
	m_slot1278 = (encoded >> 2) & 0x7fff;
	BfmeNodeDX *picked = reinterpret_cast<BfmeNodeDX *>(
		reinterpret_cast<BfmePicker1284 *>(this)->bfmePick1284(m_group1274, m_slot1278));
	if (g_bfmeHolderBU->bfmeAllows(picked))
		picked = 0;
	else if (picked != 0)
		picked->bfmeAttach1281();

	if (m_mode1270 != 0) {
		BfmeNodeDX *current = m_node126c;
		if (current != 0 && !bfmeBit15Clear(current)) {
			if (picked != current) {
				if (current->m_info50->m_state1c == 4) {
					reinterpret_cast<BfmeNode1285 *>(current)->bfmeSetState1285(2);
					BfmeNodeDX *entry = m_node126c;
					BfmeDescriptor1281 *descriptor = entry->m_info50->m_descriptor0c;
					for (int record = 0; record < descriptor->m_count34; ++record) {
						BfmeRecord1281 *item = &descriptor->m_records38[record];
						if ((item->m_mask & 0x10) != 0)
							reinterpret_cast<BfmeThingLP *>(this)->bfmePushLP(
								&item->m_payload,
								reinterpret_cast<BfmeOtherLP *>(entry->m_source4c),
								reinterpret_cast<int>(g_bfmeExtra1282));
					}
					if ((entry->m_info50->m_flags18 & 0x10000) != 0) {
						int *route = &g_bfmeRouteTable1282[0].m_index;
						for (; (int)route < (int)&g_bfmeRouteTable1282[7].m_index; route += 3) {
							if ((route[-1] & 0x10000) != 0) {
								BfmeN1034 *node = entry->m_source4c->bfmeGetLookup1282()->bfmeFind1034F(
									(int)&g_bfmeRouteKeys1282[route[0]]);
								if (node != 0) {
									int code = ((route[1] & 0x7f) << 10) | 5;
									reinterpret_cast<BfmeRouteManager1282 *>(g_bfmeHolderBU)
										->bfmeSubmit1282(entry, node, 0, code);
								}
							}
						}
					}
					bfmeFlush1282();
				}
			} else if (current->m_info50->m_state1c == 2) {
				reinterpret_cast<BfmeNode1285 *>(current)->bfmeSetState1285(4);
				BfmeNodeDX *entry = m_node126c;
				BfmeDescriptor1281 *descriptor = entry->m_info50->m_descriptor0c;
				for (int record = 0; record < descriptor->m_count34; ++record) {
					BfmeRecord1281 *item = &descriptor->m_records38[record];
					if ((item->m_mask & 0x20) != 0)
						reinterpret_cast<BfmeThingLP *>(this)->bfmePushLP(
							&item->m_payload,
							reinterpret_cast<BfmeOtherLP *>(entry->m_source4c),
							reinterpret_cast<int>(g_bfmeExtra1282));
				}
				if ((entry->m_info50->m_flags18 & 0x8000) != 0) {
					int *route = &g_bfmeRouteTable1282[0].m_index;
					for (; (int)route < (int)&g_bfmeRouteTable1282[7].m_index; route += 3) {
						if ((route[-1] & 0x8000) != 0) {
							BfmeN1034 *node = entry->m_source4c->bfmeGetLookup1282()->bfmeFind1034F(
								(int)&g_bfmeRouteKeys1282[route[0]]);
							if (node != 0) {
								int code = ((route[1] & 0x7f) << 10) | 5;
								reinterpret_cast<BfmeRouteManager1282 *>(g_bfmeHolderBU)
									->bfmeSubmit1282(entry, node, 0, code);
							}
						}
					}
				}
				bfmeFlush1282();
			}
		} else {
			if (picked == 0)
				return;
			if (!bfmeBit15Clear(picked)) {
				BfmeNodeDX *entry = picked;
				BfmeDescriptor1281 *descriptor = entry->m_info50->m_descriptor0c;
				for (int record = 0; record < descriptor->m_count34; ++record) {
					BfmeRecord1281 *item = &descriptor->m_records38[record];
					if ((item->m_mask & 0x20) != 0)
						reinterpret_cast<BfmeThingLP *>(this)->bfmePushLP(
							&item->m_payload,
							reinterpret_cast<BfmeOtherLP *>(entry->m_source4c),
							reinterpret_cast<int>(g_bfmeExtra1282));
				}
				if ((entry->m_info50->m_flags18 & 0x8000) != 0) {
					int *route = &g_bfmeRouteTable1282[0].m_index;
					for (; (int)route < (int)&g_bfmeRouteTable1282[7].m_index; route += 3) {
						if ((route[-1] & 0x8000) != 0) {
							BfmeN1034 *node = entry->m_source4c->bfmeGetLookup1282()->bfmeFind1034F(
								(int)&g_bfmeRouteKeys1282[route[0]]);
							if (node != 0) {
								int code = ((route[1] & 0x7f) << 10) | 5;
								reinterpret_cast<BfmeRouteManager1282 *>(g_bfmeHolderBU)
									->bfmeSubmit1282(entry, node, 0, code);
							}
						}
					}
				}
				bfmeFlush1282();
			}
		}
	} else if (picked != m_node126c) {
		if (m_node126c != 0 && !bfmeBit15Clear(m_node126c)) {
			reinterpret_cast<BfmeNode1285 *>(m_node126c)->bfmeSetState1285(1);
			BfmeNodeDX *entry = m_node126c;
			BfmeDescriptor1281 *descriptor = entry->m_info50->m_descriptor0c;
			for (int record = 0; record < descriptor->m_count34; ++record) {
				BfmeRecord1281 *item = &descriptor->m_records38[record];
				if ((item->m_mask & 2) != 0)
					reinterpret_cast<BfmeThingLP *>(this)->bfmePushLP(
						&item->m_payload,
						reinterpret_cast<BfmeOtherLP *>(entry->m_source4c),
						reinterpret_cast<int>(g_bfmeExtra1282));
			}
			if ((entry->m_info50->m_flags18 & 0x4000) != 0) {
				int *route = &g_bfmeRouteTable1282[0].m_index;
				for (; (int)route < (int)&g_bfmeRouteTable1282[7].m_index; route += 3) {
					if ((route[-1] & 0x4000) != 0) {
						BfmeN1034 *node = entry->m_source4c->bfmeGetLookup1282()->bfmeFind1034F(
							(int)&g_bfmeRouteKeys1282[route[0]]);
						if (node != 0) {
							int code = ((route[1] & 0x7f) << 10) | 5;
							reinterpret_cast<BfmeRouteManager1282 *>(g_bfmeHolderBU)
								->bfmeSubmit1282(entry, node, 0, code);
						}
					}
				}
			}
			if (descriptor->m_audio3c != 0 && descriptor->m_audio3c[0] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[0]->m_handle08, 0);
			bfmeFlush1282();
		}
		if (m_node126c != 0)
			m_node126c->bfmeRelease1281();
		m_node126c = picked;
		if (picked == 0)
			return;
		picked->bfmeAttach1281();
		if (!bfmeBit15Clear(picked)) {
			reinterpret_cast<BfmeNode1285 *>(m_node126c)->bfmeSetState1285(2);
			bfmeBroadcast1282(reinterpret_cast<BfmeEntry1282 *>(picked), 1);
		}
	}
	if (picked != 0)
		picked->bfmeRelease1281();
}
