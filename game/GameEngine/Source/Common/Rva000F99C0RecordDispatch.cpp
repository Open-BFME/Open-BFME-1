// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x000F99C0, 151 bytes.  Walks an STLport vector of 0x60-byte records
// at +4 and hands each one to the visitor argument through ILT 0x00010A64
// (0x00365C20, thiscall, ret 0x2C): the record's leading UnicodeString, which
// the visitor copies with UnicodeString::set, its +0x08 and +0x0C words,
// its six-word block at +0x14 by value, its +0x40 word and its +0x44 tail.
// Owner, visitor and record are unnamed by any caller, so the names keep the
// address.  Indexing the vector afresh for every argument, rather than
// through one reference, gives retail's element-address-first schedule.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "unicode_string.h"

// The visitor call lands on the matched ?method@Rva00365C20Owner@@... at
// 0x00365C20 (Rva00365C20PlayerArmyAppend.cpp, through ILT 0x00010A64), so the
// call is spelled with that owner's parameter types: a record reference, two
// ints, the six-word payload by value, an int and a tail reference.
struct Rva00365C20SourceRecord;
struct Rva00365C20Tail;

struct Rva00365C20Payload6
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
};

class Rva00365C20Owner
{
public:
	void method( const Rva00365C20SourceRecord &source00, int source08, int source0c,
		Rva00365C20Payload6 source14, int index, const Rva00365C20Tail &source44 );
};

struct Rva000F99C0Record
{
	UnicodeString m_name;
	unsigned char m_unmodelled04[ 4 ];
	int m_word08;
	int m_word0C;
	unsigned char m_unmodelled10[ 4 ];
	Rva00365C20Payload6 m_payload14;
	unsigned char m_unmodelled2C[ 0x14 ];
	int m_word40;
	unsigned char m_tail44[ 0x1C ];
};

// The visitor argument's class keeps the address-derived name the matched
// dispatch row mangles; it is the Rva00365C20Owner above.
class Rva00365C20Visitor;

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
		( (Rva00365C20Owner *)visitor )->method(
			*(const Rva00365C20SourceRecord *)&m_records[ i ].m_name,
			m_records[ i ].m_word08, m_records[ i ].m_word0C,
			m_records[ i ].m_payload14, m_records[ i ].m_word40,
			*(const Rva00365C20Tail *)m_records[ i ].m_tail44 );
}
