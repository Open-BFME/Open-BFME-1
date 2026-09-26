// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00452000, 220 bytes.
// The ILT at 0x000036BB and AptMapPreviewSetMapDescription.cpp identify this
// getter as the MapMetaData map.str description first-line accessor.

typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase();
	StringBase(const StringBase<T> &other);
	StringBase(const StringBase<T> &other, int start, int length);
	~StringBase();
	void set(const StringBase<T> &other);

	Header *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	UnicodeString(const UnicodeString &other, int start, int length)
		: StringBase<WideChar>(other, start, length) {}
	~UnicodeString() {}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const WideChar *str() const
	{
		return m_data ? m_data->m_text : (const WideChar *)0x0107388C;
	}

	void set(const UnicodeString &other)
	{
		StringBase<WideChar>::set(other);
	}
};

class MapMetaData
{
public:
	UnicodeString getDescription();
	UnicodeString bfme_getDescriptionFirstLine();
};

UnicodeString MapMetaData::bfme_getDescriptionFirstLine()
{
	UnicodeString description = getDescription();
	const WideChar *text = description.str();
	const WideChar *end = text + description.getLength();
	while (text != end)
	{
		if (*text == 10)
			goto found;
		++text;
	}
	goto done;

found:
	{
		UnicodeString result(description, 0, (int)(text - description.str()));
		description.set(result);
	}

done:
	return description;
}
