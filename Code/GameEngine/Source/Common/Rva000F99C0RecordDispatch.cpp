// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x000F99C0, 151 bytes.  Walks an STLport vector of 0x60-byte records
// at +4 and hands each one to the visitor argument through ILT 0x00010A64
// (0x00365C20, thiscall, ret 0x2C): the record, its +0x08 and +0x0C words,
// its six-word block at +0x14 by value, its +0x40 word and its +0x44 tail.
// Owner, visitor and record are unnamed by any caller, so the names keep the
// address.  Indexing the vector afresh for every argument, rather than
// through one reference, gives retail's element-address-first schedule.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva000F99C0Payload
{
	unsigned int m_words[ 6 ];
};

struct Rva000F99C0Record
{
	unsigned char m_unmodelled00[ 8 ];
	unsigned int m_word08;
	unsigned int m_word0C;
	unsigned char m_unmodelled10[ 4 ];
	Rva000F99C0Payload m_payload14;
	unsigned char m_unmodelled2C[ 0x14 ];
	int m_word40;
	unsigned char m_tail44[ 0x1C ];
};

class Rva00365C20Visitor
{
public:
	void visit( const Rva000F99C0Record *record, unsigned int word08, unsigned int word0C,
		Rva000F99C0Payload payload, int word40, const unsigned char *tail );
};

class Rva000F99C0RecordDispatch
{
public:
	void dispatch( Rva00365C20Visitor *visitor );

private:
	int m_unmodelled00;
	_STL::vector<Rva000F99C0Record> m_records;
};

void Rva000F99C0RecordDispatch::dispatch( Rva00365C20Visitor *visitor )
{
	for( unsigned int i = 0; i < m_records.size(); ++i )
		visitor->visit( &m_records[ i ], m_records[ i ].m_word08, m_records[ i ].m_word0C,
			m_records[ i ].m_payload14, m_records[ i ].m_word40, m_records[ i ].m_tail44 );
}
