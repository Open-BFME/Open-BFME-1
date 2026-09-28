// ?d_003594a0@@YAXXZ
// partial score=0.955 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// Retail contains matching 108-byte routines at 0x003592A0 and 0x003594A0.
// Rva00359330StringRecordRelease.cpp establishes a 20-byte record and its
// field offsets. This draft walks the active index at +0x1C backwards, drains
// each node list at record +0x10, and sets the reference count at +0x0E to one.
// Callers do not prove the table owner, so the class name keeps the target RVA.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void __cdecl operator delete(void *block);

class BfmeNodeY
{
public:
	~BfmeNodeY();

	BfmeNodeY *m_next;
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
		void method();                                                     \
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
	void TABLE::method()                                                   \
	{                                                                      \
		TABLE *self = this;                                                \
		int index = self->m_activeTail;                                    \
	                                                                       \
		while (index != -1)                                                \
		{                                                                  \
			RECORD *record = &self->m_records[index];                       \
			NODE *head = record->m_nodes;                                   \
	                                                                       \
			NODE *next;                                                      \
			                                                               \
			while (head->m_next != 0)                                      \
			{                                                              \
				NODE *node = head->m_next;                                  \
			                                                               \
				next = head->m_next->m_next;                                 \
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

BFME_STRING_RECORD_RESET( Rva003594A0, Rva003594A0Record,
	BfmeNodeY, delete node )
