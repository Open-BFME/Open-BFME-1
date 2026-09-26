// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

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

struct Rva0046C2A0Mapped
{
	Rva0046C2A0Mapped() : m_counted(0), m_value(0) {}
	Rva0046C2A0Mapped(const Rva0046C2A0Mapped &other) :
		m_counted(other.m_counted), m_value(other.m_value)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva0046C2A0Mapped()
	{
		if (m_counted && --m_counted->m_references <= 0)
			m_counted->release(1);
	}

	Rva0046C2A0Counted *m_counted;
	void *m_value;
};

struct Rva0046C000Mapped
{
	Rva0046C000Mapped() : m_counted(0) {}
	Rva0046C000Mapped(const Rva0046C000Mapped &other) : m_counted(other.m_counted)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva0046C000Mapped()
	{
		if (m_counted && --m_counted->m_references <= 0)
			m_counted->release(1);
	}

	Rva0046C2A0Counted *m_counted;
};

struct Rva0046C540Mapped
{
	Rva0046C540Mapped() : m_counted(0) {}
	Rva0046C540Mapped(const Rva0046C540Mapped &other) : m_counted(other.m_counted)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva0046C540Mapped()
	{
		if (m_counted && --m_counted->m_references <= 0)
			m_counted->release(1);
	}

	Rva0046C2A0Counted *m_counted;
};

struct Rva0046AF20Mapped
{
	Rva0046AF20Mapped() : m_counted(0) {}
	Rva0046AF20Mapped(const Rva0046AF20Mapped &other) : m_counted(other.m_counted)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva0046AF20Mapped()
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

typedef std::hash_map<AsciiString, Rva0046C2A0Mapped, rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C2A0Map;

template Rva0046C2A0Mapped &Rva0046C2A0Map::operator[](const AsciiString &key);

typedef std::hash_map<AsciiString, Rva0046C000Mapped, rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C000Map;

template Rva0046C000Mapped &Rva0046C000Map::operator[](const AsciiString &key);

typedef std::hash_map<AsciiString, Rva0046C540Mapped, rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C540Map;

template Rva0046C540Mapped &Rva0046C540Map::operator[](const AsciiString &key);

typedef std::hash_map<AsciiString, Rva0046AF20Mapped, rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046AF20Map;

template Rva0046AF20Mapped &Rva0046AF20Map::operator[](const AsciiString &key);
