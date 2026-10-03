// cl: /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

class BfmeOwnCW;

struct Rva003568C0Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359330StringRecordTable
{
private:
	friend class BfmeOwnCW;
	int findNameIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva003568C0Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class BfmeSubCW
{
public:
	int m_bfmeDataCW;
};

class BfmeEntryCW
{
public:
	unsigned char m_bfmeHeadCW[8];
	BfmeSubCW m_bfmeSubCW;
	unsigned char m_bfmeTailCW[8];
};

class BfmeVecCW
{
public:
	int *m_bfmeBeginCW;
	int *m_bfmeEndCW;
	unsigned char m_bfmePadCW[4];
	BfmeEntryCW *m_bfmeEntriesCW;
};

class BfmeOwnCW
{
public:
	int bfmeLookupCW(void *key);

	unsigned char m_bfmeHeadCW[0xc];
	BfmeVecCW m_bfmeVecCW;
};

int BfmeOwnCW::bfmeLookupCW(void *key)
{
	BfmeVecCW *vec = &m_bfmeVecCW;

	int index = ((Rva00359330StringRecordTable *)vec)->findNameIndex((AsciiString *)key);

	if ((unsigned int)index < (unsigned int)(vec->m_bfmeEndCW - vec->m_bfmeBeginCW))
	{
		int id = vec->m_bfmeBeginCW[index];

		if (((StringBase<char> *)&vec->m_bfmeEntriesCW[id].m_bfmeSubCW)->compare(
			*(const StringBase<char> *)key) == 0)
			return id;
	}

	return -1;
}
