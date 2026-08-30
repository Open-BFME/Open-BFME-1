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

struct BfmeRecord1282
{
	int m_mask;
	void *m_payload;
};

struct BfmeAudio1282
{
	char m_padding00[8];
	void *m_handle08;
};

struct BfmeDescriptor1282
{
	char m_padding00[0x34];
	int m_count34;
	BfmeRecord1282 *m_records38;
	BfmeAudio1282 **m_audio3c;
};

struct BfmeEntryInfo1282
{
	char m_padding00[0x0c];
	BfmeDescriptor1282 *m_descriptor0c;
	char m_padding10[8];
	int m_flags18;
};

struct BfmeEntry1282
{
	char m_padding00[0x4c];
	BfmeEntrySource1282 *m_source4c;
	BfmeEntryInfo1282 *m_info50;
};

struct BfmeRoute1282
{
	int m_mask;
	int m_index;
	int m_code;
};

class BfmeR1227
{
public:
	void bfmeAdd1227(void *payload, void *source, void *extra);
};

class BfmeRouteManager1282
{
public:
	void bfmeSubmit1282(void *entry, BfmeN1034 *node, int zero, int encoded);
};

extern BfmeRouteManager1282 *g_bfmeHolderBU;
extern void *g_bfmeExtra1282;
extern BfmeRoute1282 g_bfmeRouteTable1282[7];
extern int g_bfmeRouteKeys1282[1];
extern void (__cdecl *g_bfmePlay1282)(void *handle, int zero);

class BfmeBroadcast1282 : public BfmeR1227
{
public:
	void bfmeBroadcast1282(BfmeEntry1282 *entry, int mode);
	void bfmeFlush1282();
};

void BfmeBroadcast1282::bfmeBroadcast1282(BfmeEntry1282 *entry, int mode)
{
	BfmeDescriptor1282 *descriptor = entry->m_info50->m_descriptor0c;
	for (int index = 0; index < descriptor->m_count34; ++index) {
		BfmeRecord1282 *record = &descriptor->m_records38[index];
		if ((record->m_mask & mode) != 0)
			bfmeAdd1227(&record->m_payload, entry->m_source4c, g_bfmeExtra1282);
	}

	int routeMask = 0;
	if ((mode & 8) != 0) routeMask = 0x800;
	if ((mode & 4) != 0) routeMask |= 0x400;
	if ((mode & 0x40) != 0) routeMask |= 0x1000;
	if ((mode & 1) != 0) routeMask |= 0x2000;
	if ((mode & 2) != 0) routeMask |= 0x4000;
	if ((mode & 0x20) != 0) routeMask |= 0x8000;
	if ((mode & 0x10) != 0) routeMask |= 0x10000;

	if ((entry->m_info50->m_flags18 & routeMask) != 0) {
		int *route = &g_bfmeRouteTable1282[0].m_index;
		for (; (int)route < (int)&g_bfmeRouteTable1282[7].m_index; route += 3) {
			if ((route[-1] & routeMask) != 0) {
				BfmeN1034 *node = entry->m_source4c->bfmeGetLookup1282()->bfmeFind1034F(
					(int)&g_bfmeRouteKeys1282[route[0]]);
				if (node != 0) {
					int encoded = ((route[1] & 0x7f) << 10) | 5;
					g_bfmeHolderBU->bfmeSubmit1282(entry, node, 0, encoded);
				}
			}
		}
	}

	if (descriptor->m_audio3c != 0) {
		switch (mode) {
		case 2:
			if (descriptor->m_audio3c[0] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[0]->m_handle08, 0);
			break;
		case 1:
			if (descriptor->m_audio3c[1] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[1]->m_handle08, 0);
			break;
		case 4:
			if (descriptor->m_audio3c[2] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[2]->m_handle08, 0);
			break;
		case 8:
			if (descriptor->m_audio3c[3] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[3]->m_handle08, 0);
			break;
		}
	}
	bfmeFlush1282();
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
