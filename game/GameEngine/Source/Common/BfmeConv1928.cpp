class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBufferCS(); }

	void releaseBufferCS();

	void *m_bfmeBufCS;
};

class AsciiString;

class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const;

private:
	void *m_bfmeData;
};

class BfmeDrawableWithID
{
public:
	unsigned int bfmeGetID();
};

struct BfmeSinkCSNode;

struct BfmeSinkCSEntry
{
	unsigned char m_bfmeHead[0x48];
	unsigned int m_bfmeID;
	unsigned char m_bfmeGap[0x38];
	void *m_bfmeValue;
	AsciiStringCompareShim m_bfmeText;
};

struct BfmeSinkCSNode
{
	BfmeSinkCSEntry *entry() const { return m_bfmeEntry; }
	BfmeSinkCSNode *next() const { return m_bfmeNext; }

	BfmeSinkCSNode *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	BfmeSinkCSEntry *m_bfmeEntry;
};

struct BfmeSinkCSList
{
	struct iterator
	{
		BfmeSinkCSNode *operator->() const { return m_bfmeNode; }
		void operator++() { m_bfmeNode = m_bfmeNode->next(); }
		bool operator!=(const iterator &other) const { return m_bfmeNode != other.m_bfmeNode; }

		BfmeSinkCSNode *m_bfmeNode;
	};

	iterator begin() const
	{
		iterator result = {m_bfmeHead->next()};
		return result;
	}

	iterator end() const
	{
		iterator result = {m_bfmeHead};
		return result;
	}

	BfmeSinkCSNode *m_bfmeHead;
};

class BfmeSinkCS
{
public:
	void bfmeWriteCS(void *first, const BFMERetailAsciiString &text, void *third);

	unsigned char m_bfmeHead[0x20];
	BfmeSinkCSList m_bfmeList;
	unsigned char m_bfmeGap[4];
	unsigned char m_bfmeReady;
};

class BfmeHostCS
{
public:
	void bfmeSendCS(void *first, BFMERetailAsciiString text, void *third);

	unsigned char m_bfmeHeadCS[0x30a4];
	BfmeSinkCS *m_bfmeSinkCS;
};

void BfmeHostCS::bfmeSendCS(void *first, BFMERetailAsciiString text, void *third)
{
	BfmeSinkCS *s = m_bfmeSinkCS;

	if (s != 0)
		s->bfmeWriteCS(first, text, third);
}

void BfmeSinkCS::bfmeWriteCS(void *first, const BFMERetailAsciiString &text, void *third)
{
	BfmeSinkCS *self = this;
	if (first == 0 || self->m_bfmeReady == 0)
		return;

	for (BfmeSinkCSList::iterator node = self->m_bfmeList.begin();
		node != self->m_bfmeList.end();
		++node)
	{
		unsigned int id = static_cast<BfmeDrawableWithID *>(first)->bfmeGetID();
		BfmeSinkCSEntry *const entry = node->entry();
		if (id == entry->m_bfmeID)
		{
			if (entry->m_bfmeText.compare(*reinterpret_cast<const AsciiString *>(&text)) == 0)
			{
				entry->m_bfmeValue = third;
			}
		}
	}
}
