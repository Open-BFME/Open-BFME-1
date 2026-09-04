// ?bfmeClear@Gen_00137D50@@QAEXXZ
// partial score=0.9 date=2026-09-04
// BFME retail 0x00137D50: remove each chained entry and erase its table key.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString(void);

private:
	void *m_bfmeData;
};

class BfmeTableAB
{
public:
	void bfmeErase(const AsciiString &key);
};

class BfmeChainRefAB
{
public:
	BfmeChainRefAB *bfmeRelease(void);
};

class BfmeChainElemAB
{
public:
	virtual ~BfmeChainElemAB(void);

	BfmeChainRefAB *m_bfmeRef;
	bool m_bfmeOwned;
	char m_bfme0C[0x14];
	AsciiString m_bfmeKey;
	char m_bfme24[0x368];
	BfmeChainElemAB *m_bfmeNext;
};

class Gen_00137D50
{
public:
	void bfmeClear(void);

private:
	int m_bfme00[2];
	BfmeChainElemAB *m_bfmeHead;
	int m_bfme0C;
	BfmeTableAB m_bfmeTable;
};

// ?bfmeClear@Gen_00137D50@@QAEXXZ
void Gen_00137D50::bfmeClear(void)
{
	BfmeChainElemAB *element = m_bfmeHead;

	while (element)
	{
		BfmeChainElemAB *next = element->m_bfmeNext;
		bool wasHead = false;
		if (element == m_bfmeHead)
			wasHead = true;
		AsciiString key(element->m_bfmeKey);

		if (element->m_bfmeOwned)
		{
			delete element;
			if (wasHead)
				m_bfmeHead = next;
			m_bfmeTable.bfmeErase(key);
			element = next;
			continue;
		}
		if (element->m_bfmeRef)
			element->m_bfmeRef = element->m_bfmeRef->bfmeRelease();
		element = next;
	}
}
