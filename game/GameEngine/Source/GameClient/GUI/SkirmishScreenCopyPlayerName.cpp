// cl: /DNDEBUG /MD /EHsc
// Retail 0x00579790: copy slot zero's current skirmish name into the
// by-reference UnicodeString supplied by the Skirmish APT callback.

template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	void set(const StringBase<T> &other);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}
};

class BfmeGameSlot
{
public:
	UnicodeString getName() const;
};

class BfmeGameInfo
{
public:
	BfmeGameSlot *getSlot(int index);
};

extern BfmeGameInfo *g_bfmeCurrentCB;

class BfmeAptScreenSkirmish
{
public:
	void getPlayerName(UnicodeString &dest);
};

// ?getPlayerName@BfmeAptScreenSkirmish@@QAEXAAVUnicodeString@@@Z
void BfmeAptScreenSkirmish::getPlayerName(UnicodeString &dest)
{
	if(g_bfmeCurrentCB)
		dest.set(g_bfmeCurrentCB->getSlot(0)->getName());
}
