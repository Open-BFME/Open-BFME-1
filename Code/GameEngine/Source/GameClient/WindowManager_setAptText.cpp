// cl: /DNDEBUG /MD /EHsc

class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	void set(const UnicodeString &text);
};

class AptTextListener
{
public:
	virtual void unused();
	virtual void setText(UnicodeString *text);
};

struct AptTextRecord
{
	AptTextListener *listener;
	UnicodeString text;
};

class AptTextRecordMap
{
public:
	AptTextRecord *findOrInsert(const AsciiString &name);
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);

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
