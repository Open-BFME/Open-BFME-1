// ?resetActive@Rva00359530StringRecordTable@@QAEXXZ
// partial score=0.7 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the two string-record tables each carry a 108-byte body that
// walks the active chain backwards from +0x1C, drains the node tail hanging
// off each record's +0x10 slot and sets the reference count at +0x0E back to
// one. The record stride of 20 bytes and the table fields are the ones
// Rva00359330StringRecordRelease.cpp established. The two bodies differ only
// in the node destructor they call, which is what ties 0x003592A0 to the
// 0x00359330 table and 0x003594A0 to the 0x00359530 table.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void __cdecl operator delete(void *block);

class Rva00354A00Node
{
public:
	~Rva00354A00Node();

	Rva00354A00Node *m_next;
};

class Rva00354A60
{
public:
	void invoke();

	Rva00354A60 *m_next;
};

#define BFME_STRING_RECORD_RESET( TABLE, RECORD, NODE, DESTROY )           \
	struct RECORD                                                          \
	{                                                                      \
		int m_previous;                                                    \
		int m_next;                                                        \
		void *m_name;                                                      \
		unsigned char m_released;                                           \
		unsigned char m_pad;                                               \
		unsigned short m_references;                                        \
		NODE *m_nodes;                                                     \
	};                                                                     \
	                                                                       \
	class TABLE                                                            \
	{                                                                      \
	public:                                                                \
		void resetActive();                                                \
	                                                                       \
	public:                                                                \
		int *m_nameIndexesBegin;                                           \
		int *m_nameIndexesEnd;                                             \
		int *m_nameIndexesCapacity;                                        \
		RECORD *m_records;                                                 \
		int m_10;                                                          \
		int m_14;                                                          \
		int m_freeHead;                                                    \
		int m_activeTail;                                                  \
	};                                                                     \
	                                                                       \
	void TABLE::resetActive()                                              \
	{                                                                      \
		TABLE *self = this;                                                \
		int index = self->m_activeTail;                                    \
	                                                                       \
		while (index != -1)                                                \
		{                                                                  \
			RECORD *record = &self->m_records[index];                       \
			NODE *head = record->m_nodes;                                   \
	                                                                       \
			NODE *next = head->m_next;                                     \
	                                                                       \
			while (next != 0)                                              \
			{                                                              \
				NODE *node = head->m_next;                                  \
	                                                                       \
				next = node->m_next;                                        \
	                                                                       \
				DESTROY;                                                   \
	                                                                       \
				head->m_next = next;                                        \
				_ReadWriteBarrier();                                        \
			}                                                              \
	                                                                       \
			record->m_references = 1;                                       \
			index = self->m_records[index].m_previous;                      \
		}                                                                  \
	}

BFME_STRING_RECORD_RESET( Rva00359330StringRecordTable, Rva00359330ResetRecord,
	Rva00354A00Node, delete node )
BFME_STRING_RECORD_RESET( Rva00359530StringRecordTable, Rva00359530ResetRecord,
	Rva00354A60, if (node != 0) { node->invoke(); operator delete(node); } )
