// Indexed update for the same globally-dirty object family as the exact
// setters at 0x0018F210-0x0018F2E0.  Appending is delegated when index equals
// the current count; an in-range replacement copies the three scalar fields.

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
	void bfmeSetVector3(const BfmeVector3BG *value, int index);

private:
	char m_head[0x10];
	BfmeVector3BG *m_values;
	int m_count;
	int m_capacity;
	char m_gap[0x14];
	bool m_valuesDirty;
};

// ?bfmeAppendVector3@Gen_0018F210@@QAEXPBUBfmeVector3BG@@@Z
void Gen_0018F210::bfmeAppendVector3(const BfmeVector3BG *value)
{
	if (m_count == m_capacity)
		bfmeGrowVector3();

	g_bfmeDirtyBG |= 1;
	m_values[m_count] = *value;
	++m_count;
	m_valuesDirty = true;
}

// ?bfmeSetVector3@Gen_0018F210@@QAEXPBUBfmeVector3BG@@H@Z
void Gen_0018F210::bfmeSetVector3(const BfmeVector3BG *value, int index)
{
	if (index < 0)
		return;

	g_bfmeDirtyBG |= 1;

	if (index == m_count)
	{
		bfmeAppendVector3(value);
		return;
	}

	if (index > m_count)
		return;

	m_values[index] = *value;
	m_valuesDirty = true;
}
