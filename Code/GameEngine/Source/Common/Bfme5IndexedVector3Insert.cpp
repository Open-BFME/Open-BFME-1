// Address-derived BFME5 Vector3 insertion body at retail RVA 0x0018F5A0.

struct BfmeVector3BG
{
	int x;
	int y;
	int z;
};

extern int g_bfmeDirtyBG;

class Gen_0018F210
{
public:
	void bfmeGrowVector3(void);
	void bfmeAppendVector3(const BfmeVector3BG *value);
	void bfmeInsertVector3(const BfmeVector3BG *value, int index);

private:
	char m_head[0x10];
	BfmeVector3BG *m_values;
	int m_count;
	int m_capacity;
	char m_gap[0x14];
	bool m_valuesDirty;
};

// ?bfmeInsertVector3@Gen_0018F210@@QAEXPBUBfmeVector3BG@@H@Z
void Gen_0018F210::bfmeInsertVector3(const BfmeVector3BG *value, int index)
{
	if (index < 0)
		return;

	g_bfmeDirtyBG |= 1;

	if (index == m_count)
	{
		bfmeAppendVector3(value);
		return;
	}

	if (m_count == m_capacity)
		bfmeGrowVector3();

	for (int count = m_count; count > index; --count)
		m_values[count] = m_values[count - 1];

	m_values[index] = *value;
	++m_count;
	m_valuesDirty = true;
}
