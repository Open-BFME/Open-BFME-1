struct BfmeNodeZK
{
	BfmeNodeZK *m_bfmeNextZK;
	int m_bfmeIdZK;
	int m_bfmeKindZK;
};

struct BfmeEntryZK
{
	unsigned char m_bfmeHeadZK[0xe];
	short m_bfmeShortZK;
	unsigned char m_bfmeTailZK[4];
};

class BfmeFinderZK
{
public:
	int bfmeFindZK(void *key, int id);

	int m_bfmeSlotZK;
};

class BfmeKeyZK
{
public:
	unsigned char m_bfmeHeadZK[0x2c];
	unsigned char m_bfmeAtZK[4];
};

// The matched string-record release at 0x00359530 proves this four-byte
// owned string field and its destructor. No string is copied in this helper.
class AsciiString
{
public:
	~AsciiString();
	char *m_data;
};

struct BfmeStringRecordZK
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	BfmeNodeZK *m_nodes;
};

class Rva0035D2B0StringRecordTable
{
friend class BfmeFinderZK;

int findOrCreateIndex(AsciiString *name);

public:
	void release(int index);
	unsigned char m_bfmeHeadZK[0x0c];
	BfmeStringRecordZK *m_records;
};

class BfmeOwnerZK
{
public:
	void bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to);

	unsigned char m_bfmeHeadZK[0x2c];
	BfmeFinderZK m_bfmeFinderZK;
	unsigned char m_bfmeMidZK[8];
	BfmeEntryZK *m_bfmeTableZK;
};

int BfmeFinderZK::bfmeFindZK(void *key, int id)
{
	Rva0035D2B0StringRecordTable *sourceTable =
		reinterpret_cast<Rva0035D2B0StringRecordTable *>(key);
	Rva0035D2B0StringRecordTable *destinationTable =
		reinterpret_cast<Rva0035D2B0StringRecordTable *>(this);
	BfmeStringRecordZK *sourceRecord =
		sourceTable->m_records + id;
	int index = destinationTable->findOrCreateIndex(&sourceRecord->m_name);

	if (index == -1)
		return -1;

	BfmeStringRecordZK *destinationRecord =
		destinationTable->m_records + index;
	BfmeNodeZK *node = sourceRecord->m_nodes;
	sourceRecord->m_nodes = node->m_bfmeNextZK;
	node->m_bfmeNextZK = destinationRecord->m_nodes;
	destinationRecord->m_nodes = node;
	sourceTable->release(id);
	return index;
}

void BfmeOwnerZK::bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to)
{
	int id = (*from)->m_bfmeIdZK;
	int index = m_bfmeFinderZK.bfmeFindZK(key->m_bfmeAtZK, id);

	if (index == -1)
		return;

	(*from)->m_bfmeIdZK = index;
	(*from)->m_bfmeKindZK = m_bfmeTableZK[index].m_bfmeShortZK;

	BfmeNodeZK *next = (*from)->m_bfmeNextZK;

	(*from)->m_bfmeNextZK = *to;
	*to = *from;
	*from = next;
}
