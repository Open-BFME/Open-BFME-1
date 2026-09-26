// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME's lazy MapMetaData base-name resolver, retail 0x00450FC0.  The
// numbered display-name wrapper at 0x00451240 calls this body before adding
// its player-count suffix.  MapMetaData's matched lifecycle bodies establish
// the display-name label at +0x00, filename at +0x50, and cached result at
// +0xF4.

typedef bool Bool;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const StringBase<T> &other, int start, int length);
	StringBase(const T *text);
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

public:
	void set(const StringBase<T> &other);
	void concat(const T *text, int length);

	protected:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

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
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const char *str() const { return m_data ? m_data->text : (const char *)0x0107388B; }
	int getLength() const { return m_data ? m_data->length : 0; }

	const char *reverseFind(char needle) const
	{
		const char *begin = str();
		const char *cursor = begin + getLength();
		while (cursor != begin)
		{
			--cursor;
			if (*cursor == needle)
				return cursor;
		}
		return 0;
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
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	~UnicodeString() {}

	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const WideChar *str() const { return m_data ? m_data->text : (const WideChar *)0x0107388C; }
	int getLength() const { return m_data ? m_data->length : 0; }
	Bool startsWithDollar() const { return m_data != 0 && m_data->text[0] == '$'; }

	void set(const UnicodeString &other)
	{
		StringBase<WideChar>::set(other);
	}

	void translate(const AsciiString &text);
};

class GameTextInterface
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

extern GameTextInterface *TheGameText;

class MapMetaData
{
public:
	UnicodeString getFileName() const;
	UnicodeString bfme_getBaseDisplayName();
	UnicodeString getDescription();

private:
	UnicodeString m_displayNameLabel;
	UnicodeString m_descriptionLabel;
	unsigned char m_unreconstructed08[0x50 - 0x08];
	AsciiString m_fileName;
	unsigned char m_unreconstructed54[0xF4 - 0x54];
	UnicodeString m_cachedBaseDisplayName;
	UnicodeString m_cachedDescription;
};

UnicodeString MapMetaData::bfme_getBaseDisplayName()
{
	if (m_cachedBaseDisplayName.getLength() == 0)
	{
		const char *slash = m_fileName.reverseFind('\\');
		if (slash)
		{
			AsciiString stringFileName(m_fileName, 0,
				(int)(slash - m_fileName.str()) + 1);
			stringFileName.concat("map.str", 7);
			TheGameText->initMapStringFile(stringFileName);
		}

		AsciiString label;
		if (m_displayNameLabel.startsWithDollar())
		{
			UnicodeString untranslated(m_displayNameLabel.str() + 1);
			label.translate(untranslated);
		}
		else
		{
			label.translate(m_displayNameLabel);
		}

		Bool exists = false;
		m_cachedBaseDisplayName.set(TheGameText->fetch(label, &exists));
		if (!exists)
		{
			if (slash && m_displayNameLabel.startsWithDollar())
			{
				AsciiString leaf(slash + 1);
				m_cachedBaseDisplayName.translate(leaf);
			}
			else
			{
				m_cachedBaseDisplayName.set(m_displayNameLabel);
			}
		}

		TheGameText->reset();
	}

	return m_cachedBaseDisplayName;
}

UnicodeString MapMetaData::getFileName() const
{
	UnicodeString result;
	const char *slash = m_fileName.reverseFind('\\');
	if (slash)
	{
		AsciiString leaf(slash + 1);
		result.translate(leaf);
	}
	else
	{
		result.translate(m_fileName);
	}
	return result;
}

UnicodeString MapMetaData::getDescription()
{
	if (m_cachedDescription.getLength() == 0)
	{
		const char *slash = m_fileName.reverseFind('\\');
		if (slash)
		{
			AsciiString stringFileName(m_fileName, 0,
				(int)(slash - m_fileName.str()) + 1);
			stringFileName.concat("map.str", 7);
			TheGameText->initMapStringFile(stringFileName);
		}

		AsciiString label;
		label.translate(m_descriptionLabel);

		Bool exists = false;
		m_cachedDescription.set(TheGameText->fetch(label, &exists));
		if (!exists)
			m_cachedDescription.set(m_descriptionLabel);

		TheGameText->reset();
	}

	return m_cachedDescription;
}
