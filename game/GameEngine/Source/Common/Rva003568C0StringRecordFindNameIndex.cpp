// cl: /Igame/Libraries/Source/WWVegas/WWLib
// The two BFME string-record tables use a sorted array of record indexes.
// Retail 0x003568C0 is the first table's lower-bound search over that array.
// The 20-byte record and the eight-byte BFME AsciiString header are fixed by
// the release and findRecordIndex siblings at the same table family.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct Rva003568C0AsciiStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

#include "ascii_string.h"

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

int Rva00359330StringRecordTable::findNameIndex(AsciiString *name)
{
	int low = 0;
	int *begin = m_nameIndexesBegin;
	int high = m_nameIndexesEnd - begin;
	if (high > 0)
	{
		Rva003568C0Record *records = m_records;
		while (high > low)
		{
			int middle = (low + high) >> 1;
			Rva003568C0Record *record = &records[begin[middle]];
			AsciiString *recordName =
				(AsciiString *)((char *)record + 8);
			int comparison = name->compare(*recordName);
			if (comparison == 0)
				return middle;
			if (comparison < 0)
				high = middle;
			else
				low = middle + 1;
		}
	}

	return low;
}

struct Rva00356A60AsciiStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

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

int Rva00359530StringRecordTable::findNameIndex(AsciiString *name)
{
	int low = 0;
	int *begin = m_nameIndexesBegin;
	int high = m_nameIndexesEnd - begin;
	if (high > 0)
	{
		Rva00356A60Record *records = m_records;
		while (high > low)
		{
			int middle = (low + high) >> 1;
			Rva00356A60Record *record = &records[begin[middle]];
			AsciiString *recordName =
				(AsciiString *)((char *)record + 8);
			int comparison = name->compare(*recordName);
			if (comparison == 0)
				return middle;
			if (comparison < 0)
				high = middle;
			else
				low = middle + 1;
		}
	}

	return low;
}
