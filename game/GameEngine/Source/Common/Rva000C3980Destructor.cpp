// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// 95B twin of ??1Gen0045AFE0@@UAE@XZ (Gen0045AFE0Destructor.cpp): identical
// SEH-wrapped shape (AsciiString release, chained-base ~Gen0045AFE0Base
// virtual call under a scalar-deleting vslot0/flag1, vtable store to
// ??_7BfmeBaseVUH@@6B@ at 0x0107FCB0), but the AsciiString/tail member sits
// 0x24 bytes further into the object (+0x30 instead of +0xc), so this
// derived class carries 0x24 extra bytes of padding ahead of it.
// The member is AsciiString: retail releases it with
// `lea ecx,[esi+0x30] / call 0x00887940`, StringBase<char>::releaseBuffer.
// Address-derived name pending a caller/vtable that names the real class.

#include "ascii_string.h"

class Rva000C3980Base
{
public:
	virtual ~Rva000C3980Base()
	{
		if( m_next != 0 )
			delete m_next;
		m_next = 0;
	}

private:
	Rva000C3980Base *m_next;
	bool m_override;
};

class __declspec(novtable) Rva000C3980 : public Rva000C3980Base
{
public:
	virtual ~Rva000C3980();

private:
	char m_pad[0x24];
	AsciiString m_tail;
};

Rva000C3980::~Rva000C3980()
{
}