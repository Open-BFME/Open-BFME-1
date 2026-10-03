// Two more: twelve slots filled from one global, and twelve words copied in.

// Use the existing owner of retail's 0x7FA00000 NaN payload at VA 0x0112E8AC.
// The constructor copies its bits without interpreting them as a float.
union Rva0112E8ACValue
{
    unsigned int bits;
    float value;
};
extern const Rva0112E8ACValue g_Va0112E8AC;

class Gen_000B4A90
{
public:
	Gen_000B4A90(void);
private:
	int m_bfmeSlots[12];						// +0x00
};

// Preserve retail's separate load before each slot assignment.
Gen_000B4A90::Gen_000B4A90(void)
{
	m_bfmeSlots[0] = g_Va0112E8AC.bits;
	m_bfmeSlots[1] = g_Va0112E8AC.bits;
	m_bfmeSlots[2] = g_Va0112E8AC.bits;
	m_bfmeSlots[3] = g_Va0112E8AC.bits;
	m_bfmeSlots[4] = g_Va0112E8AC.bits;
	m_bfmeSlots[5] = g_Va0112E8AC.bits;
	m_bfmeSlots[6] = g_Va0112E8AC.bits;
	m_bfmeSlots[7] = g_Va0112E8AC.bits;
	m_bfmeSlots[8] = g_Va0112E8AC.bits;
	m_bfmeSlots[9] = g_Va0112E8AC.bits;
	m_bfmeSlots[10] = g_Va0112E8AC.bits;
	m_bfmeSlots[11] = g_Va0112E8AC.bits;
}

class BfmeBlockQB
{
public:
	int m_bfmeWords[12];
};

class Gen_001B51C0
{
public:
	void bfmeSetBlock(const BfmeBlockQB *src);
private:
	int m_bfmeGap[25];							// +0x00
	int m_bfmeBlock[12];						// +0x64
};

void Gen_001B51C0::bfmeSetBlock(const BfmeBlockQB *src)
{
	m_bfmeBlock[0] = src->m_bfmeWords[0];
	m_bfmeBlock[1] = src->m_bfmeWords[1];
	m_bfmeBlock[2] = src->m_bfmeWords[2];
	m_bfmeBlock[3] = src->m_bfmeWords[3];
	m_bfmeBlock[4] = src->m_bfmeWords[4];
	m_bfmeBlock[5] = src->m_bfmeWords[5];
	m_bfmeBlock[6] = src->m_bfmeWords[6];
	m_bfmeBlock[7] = src->m_bfmeWords[7];
	m_bfmeBlock[8] = src->m_bfmeWords[8];
	m_bfmeBlock[9] = src->m_bfmeWords[9];
	m_bfmeBlock[10] = src->m_bfmeWords[10];
	m_bfmeBlock[11] = src->m_bfmeWords[11];
}
