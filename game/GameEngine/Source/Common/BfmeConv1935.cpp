class StringBaseG
{
public:
	~StringBaseG() { releaseBuffer(); }

	void *m_bfmeBufDB;

private:
	void releaseBuffer();
};

struct BfmeNodeDB
{
	BfmeNodeDB *m_bfmePrevDB;
	BfmeNodeDB *m_bfmeNextDB;
	StringBaseG m_bfmeTextDB;
	unsigned char m_bfmePadDB[8];
};

extern "C" void *__cdecl bfmeAllocDB(unsigned int size);
extern "C" void __cdecl bfmeCopyDB(StringBaseG *dst, StringBaseG *src);

class BfmeHostDB
{
public:
	void bfmeAddDB(StringBaseG text, void *first, void *second);

	unsigned char m_bfmeHeadDB[0xc0];
	BfmeNodeDB *m_bfmeListDB;
};

void BfmeHostDB::bfmeAddDB(StringBaseG text, void *first, void *second)
{
	BfmeNodeDB *head = m_bfmeListDB;
	BfmeNodeDB *n = (BfmeNodeDB *)bfmeAllocDB(0x14);

	bfmeCopyDB(&n->m_bfmeTextDB, &text);

	BfmeNodeDB *next = head->m_bfmeNextDB;

	n->m_bfmePrevDB = head;
	n->m_bfmeNextDB = next;
	next->m_bfmePrevDB = n;
	head->m_bfmeNextDB = n;
}
