// ??0Rva0045EF90Object@@QAE@XZ
// partial score=0.82 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Rva0045EF90Base
{
public:
	Rva0045EF90Base() : m_value(0xFFFFFFFF) {}
	Rva0045EF90Base(const Rva0045EF90Base &source) : m_value(source.m_value) {}
	virtual ~Rva0045EF90Base() {}

private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object();
	Rva0045EF90Object(const Rva0045EF90Object &source);
	virtual ~Rva0045EF90Object();

private:
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	float m_value14;
	float m_value18;
	float m_value1c;
	float m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[3];
	AsciiString m_last;
};

Rva0045EF90Object::Rva0045EF90Object()
	: Rva0045EF90Base()
	, m_first()
	, m_second()
	, m_handle(0)
	, m_value24(0)
	, m_last()
{
	m_value14 = -1.0f;
	m_value18 = -1.0f;
	m_value1c = -1.0f;
	m_value20 = -1.0f;
}

Rva0045EF90Object::Rva0045EF90Object(const Rva0045EF90Object &source)
	: Rva0045EF90Base(source)
	, m_first(source.m_first)
	, m_second(source.m_second)
	, m_handle(source.m_handle)
	, m_value14(source.m_value14)
	, m_value18(source.m_value18)
	, m_value1c(source.m_value1c)
	, m_value20(source.m_value20)
	, m_value24(source.m_value24)
	, m_last(source.m_last)
{
}
