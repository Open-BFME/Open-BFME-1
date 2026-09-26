class BfmeSubZX
{
public:
	void bfmeForwardZX(int index);
	void bfmeGoZX();
};

class BfmeNodeZX
{
public:
	unsigned char m_bfmeHeadZX[0xc];
	int m_bfmeFlagZX;
	unsigned char m_bfmeMidZX[0x6c];
	BfmeSubZX *m_bfmeSubZX;
	void *m_bfmeArrZX[0x24];
	BfmeNodeZX *m_bfmeNextZX;
};

class BfmeOwnerZX
{
public:
	void bfmeWalkZX(void *a, void *b);

	unsigned char m_bfmeStartZX[4];
	int m_bfmeIndexZX;
	unsigned char m_bfmePadZX[8];
	BfmeNodeZX *m_bfmeHeadZX;
};

void BfmeOwnerZX::bfmeWalkZX(void *a, void *b)
{
	BfmeNodeZX *node = m_bfmeHeadZX;

	while (node != 0)
	{
		BfmeNodeZX *next = node->m_bfmeNextZX;

		if (node->m_bfmeFlagZX == 0)
		{
			if (node->m_bfmeSubZX != 0)
				node->m_bfmeSubZX->bfmeForwardZX(m_bfmeIndexZX);

			if (node->m_bfmeArrZX[m_bfmeIndexZX] == 0 && node->m_bfmeSubZX != 0)
				node->m_bfmeSubZX->bfmeGoZX();
		}

		if (node == next)
			break;

		node = next;
	}
}
