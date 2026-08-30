// cl: /DNDEBUG /MD /EHsc
// stlport

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	UnicodeString(const UnicodeString &other);
	~UnicodeString();
	void set(const UnicodeString &text);
	bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

private:
	void *m_data;
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

class AptTextRecordMap : private AptTextRecordHashMap
{
public:
	AptTextRecord *findOrInsert(const AsciiString &name);
	void clearListener(const AsciiString &name)
	{
		iterator it = AptTextRecordHashMap::find(name);
		if (it != end())
			it->second.listener = 0;
	}
};

AptTextRecord *AptTextRecordMap::findOrInsert(const AsciiString &name)
{
	return &operator[](name);
}

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
	AptTextRecord *record = m_aptTextRecords.findOrInsert(name);
	record->text.set(text);

	if (record->listener != 0)
		record->listener->setText(&record->text);
}

void WindowManager::bfme_bindAptText(const AsciiString &name, const UnicodeString &text, AptTextListener *listener)
{
	if (listener) {
		AptTextRecord *record = m_aptTextRecords.findOrInsert(name);
		record->listener = listener;
		if (record->text.isEmpty())
			record->text.set(text);
		listener->setText(&record->text);
	} else {
		m_aptTextRecords.clearListener(name);
	}
}
