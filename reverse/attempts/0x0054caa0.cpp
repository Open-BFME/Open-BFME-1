// ?bfmeOnlineLoginTextFilter@@YA_NAAVUnicodeString@@HHH@Z
// partial score=0.98 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define _WCTYPE_INLINE_DEFINED
#include <wctype.h>

template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};


private:
	void *m_data;

public:
	int getLength() const
	{
		return m_data ? ((const Header *)m_data)->length : 0;
	}

	T getCharAt(int index) const
	{
		return m_data ? ((const Header *)m_data)->data[index] : 0;
	}

	void removeLastChar();
};

class UnicodeString : private StringBase<wchar_t>
{
public:
	int getLength() const
	{
		return StringBase<wchar_t>::getLength();
	}

	wchar_t getCharAt(int index) const
	{
		return StringBase<wchar_t>::getCharAt(index);
	}

	const StringBase<wchar_t>::Header *rawData() const
	{
		return (const StringBase<wchar_t>::Header *)m_data;
	}

	void removeLastChar()
	{
		StringBase<wchar_t>::removeLastChar();
	}
};

bool bfmeOnlineLoginIntegerInRange(const UnicodeString &text, int minimum, int maximum);

bool bfmeOnlineLoginTextFilter(UnicodeString &text, int maximumLength, int, int maximum)
{
	while (text.getLength() > maximumLength)
		text.removeLastChar();

	const StringBase<wchar_t>::Header *data = text.rawData();
	if (data)
	{
		int length = data->length;
		if (length > 0)
		{
			bool keep = data->length == 0 || iswdigit(data->data[length - 1]);
			if (!keep)
				text.removeLastChar();
		}

		if (text.getLength() > 0)
		{
			if (bfmeOnlineLoginIntegerInRange(text, 0, maximum))
				return true;

			text.removeLastChar();
		}
	}
	return false;
}
