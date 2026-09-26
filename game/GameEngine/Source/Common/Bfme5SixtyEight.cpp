// Two more: a ring-buffer push and a search that writes into the node it
// finds.

class Gen_0024D1E0
{
public:
	void bfmePush(unsigned char value);

private:
	char m_bfmeHead[0x390];					// +0x000
	unsigned char m_bfmeBuffer[8];				// +0x390
	int m_bfmeIndex;					// +0x398
};

// ?bfmePush@Gen_0024D1E0@@QAEXE@Z
void Gen_0024D1E0::bfmePush(unsigned char value)
{
	m_bfmeBuffer[m_bfmeIndex] = value;

	++m_bfmeIndex;

	if (m_bfmeIndex == 8)
		m_bfmeIndex = 0;
}

class BfmeNodeER
{
public:
	int m_bfmeHead;						// +0x00
	void *m_bfmeKey;					// +0x04
	int m_bfmeGap[6];					// +0x08
	int m_bfmeValue;					// +0x20
};

class Gen_003399D0
{
public:
	void bfmeAssign(void *key, int value);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeNodeER **m_bfmeStart;				// +0x0C
	BfmeNodeER **m_bfmeFinish;				// +0x10
};

// ?bfmeAssign@Gen_003399D0@@QAEXPAXH@Z
void Gen_003399D0::bfmeAssign(void *key, int value)
{
	if (key == 0)
		return;

	BfmeNodeER **entry = m_bfmeStart;
	BfmeNodeER **finish = m_bfmeFinish;

	while (entry != finish)
	{
		BfmeNodeER *node = *entry;

		if (node != 0 && node->m_bfmeKey == key)
		{
			node->m_bfmeValue = value;

			return;
		}

		++entry;
	}
}
