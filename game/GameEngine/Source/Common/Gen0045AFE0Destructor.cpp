// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// The tail member is the narrow string retail releases through
// StringBase<char>::releaseBuffer (0x00887940): the body does
// `lea ecx,[esi+0x0c] / call 0x00887940`, so the member is AsciiString and
// its (inline, empty) destructor is exactly that call. The address-derived
// Gen00887940 stand-in named a symbol nothing defined.

#include "ascii_string.h"

class Gen0045AFE0Base
{
public:
	virtual ~Gen0045AFE0Base()
	{
		if( m_next != 0 )
			delete m_next;
		m_next = 0;
	}

private:
	Gen0045AFE0Base *m_next;
	bool m_override;
};

class __declspec(novtable) Gen0045AFE0 : public Gen0045AFE0Base
{
public:
	virtual ~Gen0045AFE0();

private:
	AsciiString m_tail;                                        ///< +0x0c
};

Gen0045AFE0::~Gen0045AFE0()
{
}