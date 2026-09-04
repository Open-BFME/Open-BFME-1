// BFME SubtitleManager indexed accessors.  Their release-build bounds failure
// path feeds the original diagnostic strings through the shared debug manager.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class SubtitleCrashMessage
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual SubtitleCrashMessage *setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(bool visible);
};

class SubtitleDebugManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual SubtitleCrashMessage *getCrashMessage(void *first, void *second);
};

extern SubtitleDebugManager *TheGen001336E5C;
void _bfme_debugRecordCallsite(int kind);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString();
	AsciiString &operator=(const AsciiString &that);

private:
	void *m_data;
};

union SubtitleEntryBulk
{
	int words[10];
	struct
	{
		unsigned int color;
		char middle[0x14];
		bool displayed;
		char rest[0x0B];
	} fields;
};

class SubtitleEntry
{
public:
	SubtitleEntry(const SubtitleEntry &that);
	AsciiString getText() const;
	SubtitleEntry &operator=(const SubtitleEntry &that)
	{
		m_text = that.m_text;
		m_label = that.m_label;
		m_bulk = that.m_bulk;
		m_tailFirst = that.m_tailFirst;
		m_tailSecond = that.m_tailSecond;
		return *this;
	}

	AsciiString m_text;
	AsciiString m_label;
	SubtitleEntryBulk m_bulk;
	int m_tailFirst;
	int m_tailSecond;
};

class SubtitleEntryVector
{
public:
	SubtitleEntryVector() : m_start(0), m_finish(0), m_end(0) {}
	int size() const { return m_finish - m_start; }
	SubtitleEntry *operator[](int index) const { return m_start[index]; }

	SubtitleEntry **m_start;
	SubtitleEntry **m_finish;
	SubtitleEntry **m_end;
};

class SubtitleManager
{
public:
	SubtitleManager(int first, int second, const AsciiString &name);
	bool hasBeenDisplayed(int index) const;
	AsciiString getText(int index) const;
	void setDisplayedStats(int index);
	unsigned int getColor(int index) const;
	int getStartFrame(int index) const;

private:
	int m_first;
	int m_second;
	AsciiString m_name;
	AsciiString m_secondaryName;
	int m_count;
	SubtitleEntryVector m_entries;
	int m_startFrame;
	int m_state[15];
	bool m_enabled;
};

SubtitleManager::SubtitleManager(int first, int second, const AsciiString &name) :
	m_first(first),
	m_second(second),
	m_name(name),
	m_secondaryName(),
	m_count(0),
	m_entries(),
	m_enabled(false)
{
	m_startFrame = 0x7FFFFFFF;
	// Keep the sentinel visible before the remaining state is cleared, as retail does.
	_ReadWriteBarrier();
	m_state[0] = 0;
	m_state[1] = 0;
	m_state[2] = 0;
	m_state[3] = 0;
	m_state[4] = 0;
	m_state[5] = 0;
	m_state[6] = 0;
	m_state[7] = 0;
	m_state[8] = 0;
	m_state[9] = 0;
	m_state[10] = 0;
	m_state[11] = 0;
	m_state[12] = 0;
	m_state[13] = 0;
	m_state[14] = 0;
}

bool SubtitleManager::hasBeenDisplayed(int index) const
{
	if (index < m_entries.size())
		return m_entries[index]->m_bulk.fields.displayed;

	_bfme_debugRecordCallsite(1);
	SubtitleDebugManager *manager = TheGen001336E5C;
	manager->beginReport();
	manager = TheGen001336E5C;
	SubtitleCrashMessage *message = manager->getCrashMessage(0, 0);
	message->setText("Index out of range in SubTitleManager::HasBeenDisplayed.")->show(true);
	return false;
}

AsciiString SubtitleManager::getText(int index) const
{
	if (index < m_entries.size())
		return m_entries[index]->getText();

	_bfme_debugRecordCallsite(1);
	SubtitleDebugManager *manager = TheGen001336E5C;
	manager->beginReport();
	manager = TheGen001336E5C;
	SubtitleCrashMessage *message = manager->getCrashMessage(0, 0);
	message->setText("Index out of range in SubTitleManager::GetText().")->show(true);
	return AsciiString();
}

void SubtitleManager::setDisplayedStats(int index)
{
	if (index < m_entries.size())
	{
		m_entries[index]->m_bulk.fields.displayed = true;
		return;
	}

	_bfme_debugRecordCallsite(1);
	SubtitleDebugManager *manager = TheGen001336E5C;
	manager->beginReport();
	manager = TheGen001336E5C;
	SubtitleCrashMessage *message = manager->getCrashMessage(0, 0);
	message->setText("Index out of range in SubTitleManager::SetDisplayedStats().")->show(true);
}

unsigned int SubtitleManager::getColor(int index) const
{
	if (index < m_entries.size())
		return m_entries[index]->m_bulk.fields.color;

	_bfme_debugRecordCallsite(1);
	SubtitleDebugManager *manager = TheGen001336E5C;
	manager->beginReport();
	manager = TheGen001336E5C;
	SubtitleCrashMessage *message = manager->getCrashMessage(0, 0);
	message->setText("Index out of range in SubTitleManager::GetColor().")->show(true);
	return 0xFFFF00FF;
}

int SubtitleManager::getStartFrame(int index) const
{
	if (index < m_entries.size())
		return m_entries[index]->m_bulk.words[4];

	_bfme_debugRecordCallsite(1);
	SubtitleDebugManager *manager = TheGen001336E5C;
	manager->beginReport();
	manager = TheGen001336E5C;
	SubtitleCrashMessage *message = manager->getCrashMessage(0, 0);
	message->setText("Index out of range in SubTitleManager::GetStartFrame.")->show(true);
	return 0x7FFFFFFF;
}

SubtitleEntry::SubtitleEntry(const SubtitleEntry &that) :
	m_text(that.m_text),
	m_label(that.m_label)
{
	m_bulk = that.m_bulk;
	m_tailFirst = that.m_tailFirst;
	m_tailSecond = that.m_tailSecond;
}

SubtitleEntry *subtitleCopy(SubtitleEntry *first, SubtitleEntry *last,
	SubtitleEntry *result)
{
	int count = last - first;
	while (count > 0)
	{
		*result = *first;
		++first;
		++result;
		--count;
	}
	return result;
}
