// ?getDescription@MapMetaData@@QAE?AVUnicodeString@@XZ
// partial score=0.55 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
//
// The cached map description is populated from the map-local map.str file.
// Keep the BFME tail and the GameText vtable view TU-local: the shared Zero
// Hour MapMetaData declaration does not carry either BFME extension.

typedef unsigned short WideChar;
typedef unsigned char Bool;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const StringBase<T> &other, int start, int length);
	~StringBase() { releaseBuffer(); }
	void set(const StringBase<T> &other);
	void concat(const T *text, int length);
	void releaseBuffer();

	int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	const T *str() const
	{
		return m_data ? m_data->data : (const T *)0x0107388B;
	}

	Header *m_data;
};

class UnicodeString;

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const AsciiString &other, int start, int length)
		: StringBase<char>(other, start, length) {}
	~AsciiString() {}

	int getLength() const
	{
		return StringBase<char>::getLength();
	}

	const char *str() const
	{
		return StringBase<char>::str();
	}

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	void translate(const UnicodeString &text);
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString() {}

	int getLength() const
	{
		return StringBase<WideChar>::getLength();
	}

	void set(const UnicodeString &other)
	{
		StringBase<WideChar>::set(other);
	}
};

class BfmeMapGameText
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void reset() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;
};

extern BfmeMapGameText *TheGameText;

class MapMetaData
{
public:
	UnicodeString getDescription();

private:
	char m_beforeDescription[4];
	UnicodeString m_description;
	char m_beforeFileName[0x48];
	AsciiString m_fileName;
	char m_beforeDescriptionTail[0xA4];
	UnicodeString m_descriptionTail;
};

// ?getDescription@MapMetaData@@QAE?AVUnicodeString@@XZ
UnicodeString MapMetaData::getDescription()
{
	if (m_descriptionTail.getLength() == 0)
	{
    const char *text = m_fileName.str();
    const char *end = text + m_fileName.getLength();
		char last;
		while (end != text)
		{
			last = end[-1];
			--end;
			if (last == '\\')
				break;
		}

		if (end != text)
		{
			AsciiString mapStringFile(m_fileName, 0, (int)(end - text) + 1);
			mapStringFile.concat("map.str", 7);
			TheGameText->initMapStringFile(mapStringFile);
		}

		AsciiString label;
		label.translate(m_description);
		Bool exists;
		UnicodeString fetched = TheGameText->fetch(label, &exists);
		m_descriptionTail.set(fetched);
		if (!exists)
			m_descriptionTail.set(m_description);

		TheGameText->reset();
	}

	return m_descriptionTail;
}
