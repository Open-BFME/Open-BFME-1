// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Glo012F1028Sub::consume (retail 0x003C88E0, 283 B, ret 4). The caller at
// 0x003B41A0 reaches it through ILT 0x00045B88, where symbols.csv pins this
// name. It walks the record-pointer vector at +0x28 for the record whose name
// equals *key; when that record is not the current selection (+0x04), it
// releases the resource at +0x24 and clears the selection, then selects it.
// The records are a real STLport vector<T*>. Raw begin/end members with an
// explicit size guard missed retail by 60 bytes: they loaded the start
// pointer first and kept it in ECX. vector::size() in the for condition
// matches retail exactly.

#include "ascii_string.h"
#include <vector>

static inline int CompareAscii003C88E0(const AsciiString &self, const AsciiString &other)
{
	int thatLen = other.StringBase<char>::getLength();
	const char *thatData = other.str();
	int thisLen = self.StringBase<char>::getLength();
	const char *thisData = self.str();
	int c = memcmp(thisData, thatData, thisLen < thatLen ? thisLen : thatLen);
	return c ? c : thisLen - thatLen;
}

class Glo012F1028Record
{
public:
	char m_pad00[4];
	AsciiString m_name;
};
class Glo012F1028Resource
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;

	int m_refCount;
};

static __forceinline void releaseGlo012F1028Resource(
	Glo012F1028Resource *&ref)
{
	Glo012F1028Resource *resource = ref;
	if (resource != 0)
	{
		resource->slot16();
		if (--resource->m_refCount == 0)
			resource->slot00();
		ref = 0;
	}
}

class Glo012F1028Sub
{
public:
	void consume(AsciiString *key);

private:
	void *m_vptr;
	Glo012F1028Record *m_selected;
	char m_pad08[0x1c];
	Glo012F1028Resource *m_resource;
	std::vector<Glo012F1028Record *> m_records;
};

void Glo012F1028Sub::consume(AsciiString *key)
{
	for (unsigned int index = 0; index < m_records.size(); ++index)
	{
		if (CompareAscii003C88E0(*key, m_records[index]->m_name) == 0)
		{
			if (m_selected != 0 && m_selected != m_records[index])
			{
				if (m_resource != 0)
					releaseGlo012F1028Resource(m_resource);
				m_resource = 0;
				m_resource = 0;
				m_selected = 0;
			}
			m_selected = m_records[index];
			return;
		}
	}
}
