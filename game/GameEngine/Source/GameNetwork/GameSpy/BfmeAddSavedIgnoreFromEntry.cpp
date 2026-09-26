// The callback reads a text-entry GameWindow, finds its PlayerInfo record, and
// adds the record to GameSpyInfo's saved-ignore list after the retail filters.
class GameWindow;

template <typename T>
struct BfmeStringDataE6B
{
	int m_bfmeRefE6B;
	unsigned short m_bfmeLenE6B;
	unsigned short m_bfmeCapE6B;
	T m_bfmeTextE6B[1];
};

template <typename T>
class StringBase
{
	template <typename U> friend class StringBase;
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);

	BfmeStringDataE6B<T> *data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	__forceinline AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}

	BfmeStringDataE6B<unsigned short> *dataPointer() const
	{
		return data;
	}
};

UnicodeString GadgetTextEntryGetText(GameWindow *entry);

class BfmeUniETA;
void *bfmeLookupETA(const BfmeUniETA &text);

class BfmePlayerInfoE6B
{
public:
	unsigned char m_bfmeHeadE6B[4];
	AsciiString m_bfmeNameE6B;
	unsigned char m_bfmePadE6B[0x0c];
	int m_bfmeProfileIDE6B;
	unsigned int m_bfmeFlagsE6B;
};

class GameSpyInfo
{
public:
	virtual void bfmeSlot00E6B();
	virtual void bfmeSlot01E6B();
	virtual void bfmeSlot02E6B();
	virtual void bfmeSlot03E6B();
	virtual void bfmeSlot04E6B();
	virtual void bfmeSlot05E6B();
	virtual void bfmeSlot06E6B();
	virtual void bfmeSlot07E6B();
	virtual void bfmeSlot08E6B();
	virtual void bfmeSlot09E6B();
	virtual void bfmeSlot10E6B();
	virtual void bfmeSlot11E6B();
	virtual void bfmeSlot12E6B();
	virtual void bfmeSlot13E6B();
	virtual void bfmeSlot14E6B();
	virtual void bfmeSlot15E6B();
	virtual void bfmeSlot16E6B();
	virtual void bfmeSlot17E6B();
	virtual void bfmeSlot18E6B();
	virtual void bfmeSlot19E6B();
	virtual void bfmeSlot20E6B();
	virtual void bfmeSlot21E6B();
	virtual void bfmeSlot22E6B();
	virtual void bfmeSlot23E6B();
	virtual void bfmeSlot24E6B();
	virtual void bfmeSlot25E6B();
	virtual void bfmeSlot26E6B();
	virtual void bfmeSlot27E6B();
	virtual int getLocalProfileID();
	virtual void bfmeSlot29E6B();
	virtual void bfmeSlot30E6B();
	virtual void bfmeSlot31E6B();
	virtual void bfmeSlot32E6B();
	virtual void bfmeSlot33E6B();
	virtual void bfmeSlot34E6B();
	virtual void bfmeSlot35E6B();
	virtual void bfmeSlot36E6B();
	virtual void bfmeSlot37E6B();
	virtual void bfmeSlot38E6B();
	virtual void bfmeSlot39E6B();
	virtual void bfmeSlot40E6B();
	virtual void bfmeSlot41E6B();
	virtual void bfmeSlot42E6B();
	virtual void bfmeSlot43E6B();
	virtual void bfmeSlot44E6B();
	virtual void bfmeSlot45E6B();
	virtual void bfmeSlot46E6B();
	virtual void bfmeSlot47E6B();
	virtual void bfmeSlot48E6B();
	virtual void bfmeSlot49E6B();
	virtual void bfmeSlot50E6B();
	virtual void bfmeSlot51E6B();
	virtual void bfmeSlot52E6B();
	virtual void bfmeSlot53E6B();
	virtual void bfmeSlot54E6B();
	virtual void bfmeSlot55E6B();
	virtual void bfmeSlot56E6B();
	virtual void bfmeSlot57E6B();
	virtual void bfmeSlot58E6B();
	virtual void bfmeSlot59E6B();
	virtual void bfmeSlot60E6B();
	virtual void bfmeSlot61E6B();
	virtual void bfmeSlot62E6B();
	virtual void bfmeSlot63E6B();
	virtual void bfmeSlot64E6B();
	virtual void bfmeSlot65E6B();
	virtual void bfmeSlot66E6B();
	virtual void bfmeSlot67E6B();
	virtual void bfmeSlot68E6B();
	virtual void bfmeSlot69E6B();
	virtual void bfmeSlot70E6B();
	virtual void bfmeSlot71E6B(int id);
	virtual void bfmeSlot72E6B(int id);
	virtual void addToSavedIgnoreList(int id, AsciiString name) = 0;
	virtual void bfmeSlot74E6B(int id);
};

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyConfigInterface
{
public:
	virtual void bfmeSlot00E6B();
	virtual void bfmeSlot01E6B();
	virtual void bfmeSlot02E6B();
	virtual void bfmeSlot03E6B();
	virtual void bfmeSlot04E6B();
	virtual void bfmeSlot05E6B();
	virtual void bfmeSlot06E6B();
	virtual void bfmeSlot07E6B();
	virtual void bfmeSlot08E6B();
	virtual void bfmeSlot09E6B();
	virtual void bfmeSlot10E6B();
	virtual bool rejectPlayer(int id);
};

extern GameSpyConfigInterface *TheGameSpyConfig;

void __stdcall bfmeAddSavedIgnoreFromEntryE6B(GameWindow *entry)
{
	UnicodeString text;

	text.set(GadgetTextEntryGetText(entry));

	if (text.dataPointer() != 0 && text.dataPointer()->m_bfmeLenE6B != 0)
	{
		BfmePlayerInfoE6B *player = (BfmePlayerInfoE6B *)bfmeLookupETA(
			(const BfmeUniETA &)text);

		if (player != 0 && player->m_bfmeProfileIDE6B !=
			TheGameSpyInfo->getLocalProfileID() &&
			(player->m_bfmeFlagsE6B & 0x20) == 0 &&
			(TheGameSpyConfig == 0 ||
			 !TheGameSpyConfig->rejectPlayer(player->m_bfmeProfileIDE6B)))
		{
			TheGameSpyInfo->addToSavedIgnoreList(
				player->m_bfmeProfileIDE6B, player->m_bfmeNameE6B);
		}
	}
}
