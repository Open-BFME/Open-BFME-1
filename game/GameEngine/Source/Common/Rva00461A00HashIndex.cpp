// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Fifth instantiation of the hash_map<AsciiString, counted-pointer>::operator[]
// family in Rva0046C2A0HashIndex.cpp: retail 0x00461A00 is a byte-twin
// (tools/twin_scan.py) of 0x0046B840, differing only in its _M_find and
// _M_insert callees. The mapped type keeps the one-counted-pointer shape.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	void *m_data;
};

class Rva0046C2A0Counted
{
public:
	virtual void release(unsigned int deleting);
	int m_references;
};

struct Rva00461A00Mapped
{
	Rva00461A00Mapped() : m_counted(0) {}
	Rva00461A00Mapped(const Rva00461A00Mapped &other) : m_counted(other.m_counted)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva00461A00Mapped()
	{
		if (m_counted && --m_counted->m_references <= 0)
			m_counted->release(1);
	}

	Rva0046C2A0Counted *m_counted;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()(const AsciiString &left, const AsciiString &right) const;
	};
}

#include <hash_map>

typedef std::hash_map<AsciiString, Rva00461A00Mapped, rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva00461A00Map;

template Rva00461A00Mapped &Rva00461A00Map::operator[](const AsciiString &key);
