// cl: /DNDEBUG /MD /EHsc

// ?getAudioLODIndex@GameLODManager@@QAEHABVAsciiString@@@Z
// BFME's two-entry AudioLOD lookup.  The method is not present in the ZH
// reference, so this TU keeps the BFME table and the reporting path local.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned count);
extern "C" unsigned __cdecl strlen(const char *text);

extern "C" char *bfmeTabEYC[];

class AsciiString
{
public:
	struct Data
	{
		Int references;
		unsigned short length;
		unsigned short reserved;
		char text[1];
	};

	Int compareNoCase(const char *other) const
	{
		Int otherLength = other ? strlen(other) : 0;
		Int thisLength;
		if (m_data)
			thisLength = m_data->length;
		else
			thisLength = 0;
		const char *thisText = m_data ? m_data->text : "";

		Int count = thisLength < otherLength ? thisLength : otherLength;
		Int comparison = _memicmp(thisText, other, count);
		if (comparison != 0)
			return comparison;
		return thisLength - otherLength;
	}

	Data *m_data;
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern bool _bfme_debugReportingEnabled(void);

class GameLODManager
{
public:
	Int getAudioLODIndex(const AsciiString &name);
};

Int GameLODManager::getAudioLODIndex(const AsciiString &name)
{
	for (Int i = 0; i < 2; ++i)
	{
		if (name.compareNoCase(bfmeTabEYC[i]) == 0)
			return i;
	}

	if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
		report = report->slot38(
			"GameLODManager::getAudioLODIndex - Invalid LOD name '");
		const char *text = name.m_data ? name.m_data->text : "";
		report->slot38(text);
		report->slot38("'")->slot4C(2);
	}

	return -1;
}
