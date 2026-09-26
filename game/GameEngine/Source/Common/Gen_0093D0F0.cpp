// Clean reconstruction of the counted entry walk at retail RVA 0x0093D0F0.
// The owning and entry identities are not recovered; the eight-byte entry
// stride and its leading object pointer are the layout facts visible here.

class Gen_0093D0F0_Item
{
public:
	void step();
};

struct Gen_0093D0F0_Entry
{
	Gen_0093D0F0_Item *m_item;
	int m_other;
};

class Gen_0093D0F0
{
public:
	void process();

private:
	unsigned char m_pad[0x38];
	Gen_0093D0F0_Entry *m_entries;
	unsigned char m_gap[0x44 - 0x3C];
	int m_count;
};

void Gen_0093D0F0::process()
{
	for (int i = 0; i < m_count; ++i)
		m_entries[i].m_item->step();
}
