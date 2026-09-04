// cl: /DNDEBUG /MD /EHsc
// stlport

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

template <typename Character>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	void set(const StringBase<Character> &text);

protected:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other);
	~UnicodeString();
	void set(const UnicodeString &text)
	{
		StringBase<unsigned short>::set(text);
	}
	bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

};

class AptTextListener
{
public:
	virtual void unused();
	virtual void setText(UnicodeString *text);
};

struct AptTextRecord
{
	AptTextRecord() : listener(0), text() {}
	~AptTextRecord() { listener = 0; }

	AptTextListener *listener;
	UnicodeString text;
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

typedef std::hash_map<AsciiString, AptTextRecord, rts::hash<AsciiString>, rts::equal_to<AsciiString> > AptTextRecordHashMap;

class AptTextRecordMap : public AptTextRecordHashMap
{
public:
	void clearListener(const AsciiString &name)
	{
		iterator it = AptTextRecordHashMap::find(name);
		if (it != end())
			it->second.listener = 0;
	}
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
	void bfme_bindAptText(const AsciiString &name, const UnicodeString &text, AptTextListener *listener);

private:
	// Preserve the retail layout so the named-record map remains at +0x44.
	char m_bfmeHead[0x44];
	AptTextRecordMap m_aptTextRecords;
};

// ?bfme_setAptText@WindowManager@@QAEXABVAsciiString@@ABVUnicodeString@@@Z
void WindowManager::bfme_setAptText(const AsciiString &name, const UnicodeString &text)
{
	AptTextRecord *record = &m_aptTextRecords[name];
	record->text.set(text);

	if (record->listener != 0)
		record->listener->setText(&record->text);
}

void WindowManager::bfme_bindAptText(const AsciiString &name, const UnicodeString &text, AptTextListener *listener)
{
	if (listener) {
		AptTextRecord *record = &m_aptTextRecords[name];
		record->listener = listener;
		if (record->text.isEmpty())
			record->text.set(text);
		listener->setText(&record->text);
	} else {
		m_aptTextRecords.clearListener(name);
	}
}
