// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0051A850 / 0x0051A8F0 / 0x0051AAA0: format APT:LivingWorldRegion*%d
// and push the result through WindowManager::bfme_setAptText. format is
// __cdecl so this is a stack argument (add esp, 0xc).

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
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
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void __cdecl format(AsciiString fmt, ...);
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

extern WindowManager *g_theWindowManager;

// ?_bfme_setLivingWorldRegionName@@YAXHABVUnicodeString@@@Z
void _bfme_setLivingWorldRegionName(int index, const UnicodeString &text)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionName%d"), index);
	g_theWindowManager->bfme_setAptText(variableName, text);
}

// ?_bfme_setLivingWorldRegionBonus@@YAXHABVUnicodeString@@@Z
void _bfme_setLivingWorldRegionBonus(int index, const UnicodeString &text)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionBonus%d"), index);
	g_theWindowManager->bfme_setAptText(variableName, text);
}

// ?_bfme_setLivingWorldRegionConqueredBonus@@YAXHABVUnicodeString@@@Z
void _bfme_setLivingWorldRegionConqueredBonus(int index, const UnicodeString &text)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionConqueredBonus%d"), index);
	g_theWindowManager->bfme_setAptText(variableName, text);
}
