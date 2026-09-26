// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ThingTemplate::isEquivalentTo, retail 0x0013FE10 (486 bytes).  Identity:
// ILT 0x0003E80B jumps here and carries the symbol for its 49 callers (Team,
// ScriptActions, ScriptConditions).  The body is Zero Hour's with BFME's
// changes: the reskinnedFrom tests are gone, and a second vector of names at
// +0x2DC is checked before m_buildVariations -- each of our names against
// theirs, their names against our name, and their names against ours.  That
// nested compare is StringBase<char>::compareNoCase inlined; every other
// compare calls the out-of-line body through ILT 0x00027471.
//
// Shape notes: tt->m_field2DC's begin is taken before its end, and operator[]
// is STLport's *(begin() + n); both change register assignment.
#define _DLL
#include <string.h>

typedef bool Bool;
typedef int Int;

template <class T> class StringBase
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	int compareNoCase(const StringBase<T> &str) const;

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? &m_data->data[0] : ""; }
};

// The nested loop compares two strings in line; everywhere else the
// out-of-line StringBase<char>::compareNoCase is called.
static inline int compareNamesNoCase(const AsciiString &a, const AsciiString &b)
{
	int len = b.getLength();
	const char *data = b.str();
	int myLen = a.getLength();
	const char *myData = a.str();
	int result = _memicmp(myData, data, myLen < len ? myLen : len);
	if (result != 0)
		return result;
	return myLen - len;
}

namespace _STL
{
template <class Type> class vector
{
public:
	typedef const Type *const_iterator;
	const_iterator begin() const { return _M_start; }
	const_iterator end() const { return _M_finish; }
	Int size() const { return _M_finish - _M_start; }
	const Type &operator[](unsigned int index) const { return *(begin() + index); }

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;	// +0x04
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return m_nameString; }
	Bool isEquivalentTo(const ThingTemplate *tt) const;

	char m_pad08[0x20 - 0x08];
	AsciiString m_nameString;							// +0x020
	char m_pad24[0x2D0 - 0x24];
	_STL::vector<AsciiString> m_buildVariations;		// +0x2D0
	_STL::vector<AsciiString> m_field2DC;				// +0x2DC, BFME-only
};

// ?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z
Bool ThingTemplate::isEquivalentTo(const ThingTemplate *tt) const
{
	if (!(this && tt))
		return false;

	if (this == tt)
		return true;

	if (this->getFinalOverride() == tt->getFinalOverride())
		return true;

	const AsciiString &myName = getName();
	const AsciiString &ttName = tt->getName();
	_STL::vector<AsciiString>::const_iterator it;
	_STL::vector<AsciiString>::const_iterator end = m_field2DC.end();
	for (it = m_field2DC.begin(); it != end; ++it)
		if (it->compareNoCase(ttName) == 0)
			return true;

	_STL::vector<AsciiString>::const_iterator other = tt->m_field2DC.begin();
	_STL::vector<AsciiString>::const_iterator otherEnd = tt->m_field2DC.end();
	for (; other != otherEnd; ++other)
	{
		if (other->compareNoCase(myName) == 0)
			return true;
		for (it = m_field2DC.begin(); it != end; ++it)
			if (compareNamesNoCase(*it, *other) == 0)
				return true;
	}

	Int i;
	Int numVariations = m_buildVariations.size();
	for (i = 0; i < numVariations; ++i)
		if (m_buildVariations[i].compareNoCase(tt->getName()) == 0)
			return true;

	numVariations = tt->m_buildVariations.size();
	for (i = 0; i < numVariations; ++i)
		if (tt->m_buildVariations[i].compareNoCase(getName()) == 0)
			return true;

	return false;
}
