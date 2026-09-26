class BfmeNodeDX;

class Gen_008A0C30
{
public:
	bool bfmeAllows(BfmeNodeDX *node) const;
};

extern Gen_008A0C30 *g_bfmeHolderBU;

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
			if (!g_bfmeHolderBU->bfmeAllows(entry)) {
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
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
