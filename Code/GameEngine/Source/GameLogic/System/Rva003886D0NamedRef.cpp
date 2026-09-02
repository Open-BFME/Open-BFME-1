// cl: /O2 /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Ref-counted BFME name record constructed by the GameLogic family.

#include "StringInline.h"

class Rva003886D0RefBase
{
public:
	Rva003886D0RefBase() : m_refCount(0) {}
	virtual ~Rva003886D0RefBase();
	virtual void release();
	void addRef() { ++m_refCount; }

protected:
	int m_refCount;
};

class Rva003886D0NamedRef : public Rva003886D0RefBase
{
public:
	Rva003886D0NamedRef(const AsciiString &name);

private:
	AsciiString m_name;
};

Rva003886D0NamedRef::Rva003886D0NamedRef(const AsciiString &name) :
	m_name(name)
{
}

class Rva0038A020NamedPtr
{
public:
	Rva0038A020NamedPtr(const AsciiString &name);

private:
	Rva003886D0NamedRef *m_ptr;
};

Rva0038A020NamedPtr::Rva0038A020NamedPtr(const AsciiString &name)
{
	m_ptr = new Rva003886D0NamedRef(name);
	if (m_ptr)
		m_ptr->addRef();
}

class Rva0038BD90NamedPtr : public Rva0038A020NamedPtr
{
public:
	Rva0038BD90NamedPtr(AsciiString name);
};

Rva0038BD90NamedPtr::Rva0038BD90NamedPtr(AsciiString name) :
	Rva0038A020NamedPtr(name)
{
}
