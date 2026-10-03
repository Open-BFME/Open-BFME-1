// ?tail003C12A0@Transfer003C3D90@@QAEXPAVXfer@@@Z
// partial score=0.9413 date=2026-10-03
// ?tail003C12A0@Transfer003C3D90@@QAEXPAVXfer@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include "../../../../game/Libraries/Source/WWVegas/WWLib/string_base.h"
#include <list>
#include "../../../../game/GameEngine/Source/Common/System/xfer.h"

class UnicodeString
{
public:
	UnicodeString() : m_text(0) {}
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that);
	}
	~UnicodeString()
	{
		((StringBase<wchar_t> *)this)->releaseBuffer();
	}

private:
	void *m_text;
};

struct Rva003C12A0Element
{
	UnicodeString m_text;
	int m_word4;
	int m_word8;

	Rva003C12A0Element()
		: m_text()
		, m_word4(0)
		, m_word8(3)
	{
	}

	~Rva003C12A0Element() {}
};

bool operator==(const Rva003C12A0Element &, const Rva003C12A0Element &);
bool operator<(const Rva003C12A0Element &, const Rva003C12A0Element &);

class Transfer003C3D90
{
public:
	void tail003C12A0(Xfer *xfer);

private:
	unsigned char m_unmodelled00[0xC0];
	_STL::list<Rva003C12A0Element> m_list;
};

// ?tail003C12A0@Transfer003C3D90@@QAEXPAVXfer@@@Z
void Transfer003C3D90::tail003C12A0(Xfer *xfer)
{
	int count = (int)m_list.size();
	*xfer == count;
	bool proceed = xfer->IsLoading();

	if (proceed)
	{
		m_list.clear();
		int i;
		i = 0;
		for (; i < count; ++i)
		{
			Rva003C12A0Element tmp;
			*xfer == tmp.m_text;
			*xfer == tmp.m_word4;
			xfer->XferRawBytes(&tmp.m_word8, 4);
			m_list.push_back(tmp);
		}
		return;
	}

	_STL::list<Rva003C12A0Element>::iterator it = m_list.begin();
	_STL::list<Rva003C12A0Element>::iterator end = m_list.end();
	for (; it != end; ++it)
	{
		Rva003C12A0Element tmp2(*it);
		*xfer == tmp2.m_text;
		*xfer == tmp2.m_word4;
		xfer->XferRawBytes(&tmp2.m_word8, 4);
	}
}
