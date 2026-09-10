// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME OnlineLogin numeric text filter at retail 0x0054CAA0.

typedef unsigned short WideChar;
typedef unsigned short wchar_t;
extern "C" __declspec(dllimport) int __cdecl iswdigit(WideChar value);

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
	int getLength() const { return StringBase<wchar_t>::getLength(); }
	wchar_t getCharAt(int index) const
	{
		return StringBase<wchar_t>::getCharAt(index);
	}
	const StringBase<wchar_t>::Header *rawData() const
	{
		return (const StringBase<wchar_t>::Header *)m_data;
	}
	void removeLastChar() { StringBase<wchar_t>::removeLastChar(); }
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
			unsigned short last = data->data[length - 1];
			bool keep = data->length == 0 || iswdigit(last);
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
