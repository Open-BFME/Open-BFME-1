extern "C" __declspec(dllimport) void * __cdecl memmove( void *destination, const void *source, unsigned int count );

// Retail fixes the record stride at 20 bytes and the name field at +8.  The
// direct call from that field to AsciiString's established destructor body is
// what identifies the otherwise address-derived owned type.  The two integer
// links and the compacted four-byte index range are likewise named only for
// the operations visible in this body; the original owner identity is absent.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
	char *m_data;
};

struct Rva00359330Node;

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva00359330Node *m_nodes;
};

#define BFME_STRING_RECORD_TABLE( NAME )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void release( int index );                                         \
	                                                                      \
	private:                                                              \
		int findNameIndex( AsciiString *name );                            \
	                                                                      \
		int *m_nameIndexesBegin;                                           \
		int *m_nameIndexesEnd;                                             \
		int *m_nameIndexesCapacity;                                        \
		Rva00359330Record *m_records;                                      \
		int m_10;                                                          \
		int m_14;                                                          \
		int m_freeHead;                                                    \
		int m_activeTail;                                                  \
	};                                                                    \
	                                                                      \
	void NAME::release( int index )                                       \
	{                                                                     \
		Rva00359330Record *record = &m_records[index];                     \
		--record->m_references;                                            \
		record->m_released = 1;                                            \
	                                                                      \
		if ( record->m_nodes == 0 )                                       \
		{                                                                 \
			int nameIndex = findNameIndex( &record->m_name );               \
	                                                                      \
			if ( record->m_previous != -1 )                                \
				m_records[record->m_previous].m_next = record->m_next;       \
	                                                                      \
			if ( record->m_next != -1 )                                    \
				m_records[record->m_next].m_previous = record->m_previous;   \
			else                                                          \
				m_activeTail = record->m_previous;                           \
	                                                                      \
			record->m_previous = m_freeHead;                               \
			m_freeHead = index;                                            \
			record->m_name.~AsciiString();                                 \
	                                                                      \
			int *position = m_nameIndexesBegin + nameIndex;                \
			int *next = position + 1;                                      \
			if ( m_nameIndexesEnd != next )                                \
				memmove( position, next,                                     \
					(char *)m_nameIndexesEnd - (char *)next );                 \
			--m_nameIndexesEnd;                                           \
		}                                                                 \
	}

BFME_STRING_RECORD_TABLE( Rva00359330StringRecordTable )
BFME_STRING_RECORD_TABLE( Rva00359530StringRecordTable )
