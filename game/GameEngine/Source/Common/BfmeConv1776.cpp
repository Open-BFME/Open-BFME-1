// cl: /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

class BfmeOwnCX;

struct Rva00356A60Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359530StringRecordTable
{
private:
	friend class BfmeOwnCX;
	int findNameIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00356A60Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class BfmeSubCX
{
public:
	int m_bfmeDataCX;
};

class BfmeEntryCX
{
public:
	unsigned char m_bfmeHeadCX[8];
	BfmeSubCX m_bfmeSubCX;
	unsigned char m_bfmeTailCX[8];
};

class BfmeVecCX
{
public:
	int *m_bfmeBeginCX;
	int *m_bfmeEndCX;
	unsigned char m_bfmePadCX[4];
	BfmeEntryCX *m_bfmeEntriesCX;
};

class BfmeOwnCX
{
public:
	int bfmeLookupCX(void *key);

	unsigned char m_bfmeHeadCX[0x2c];
	BfmeVecCX m_bfmeVecCX;
};

int BfmeOwnCX::bfmeLookupCX(void *key)
{
	BfmeVecCX *vec = &m_bfmeVecCX;

	int index = ((Rva00359530StringRecordTable *)vec)->findNameIndex((AsciiString *)key);

	if ((unsigned int)index < (unsigned int)(vec->m_bfmeEndCX - vec->m_bfmeBeginCX))
	{
		int id = vec->m_bfmeBeginCX[index];

		if (((StringBase<char> *)&vec->m_bfmeEntriesCX[id].m_bfmeSubCX)->compare(
			*(const StringBase<char> *)key) == 0)
			return id;
	}

	return -1;
}
