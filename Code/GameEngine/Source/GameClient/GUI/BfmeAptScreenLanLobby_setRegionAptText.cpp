// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0051A850 / 0x0051A8F0 / 0x0051AAA0: format APT:LivingWorldRegion*%d
// and push the result through WindowManager::bfme_setAptText. format is
// __cdecl so this is a stack argument (add esp, 0xc).
typedef char Bool;

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

struct UnicodeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	void format(UnicodeString fmt, ...);
	const unsigned short *str() const
	{
		return m_data == 0 ? 0 : (const unsigned short *)m_data + 4;
	}
	bool isNotEmpty() const
	{
		return m_data != 0 && ((const UnicodeStringData *)m_data)->length != 0;
	}
	~UnicodeString() {}
};

struct AsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void __cdecl format(AsciiString fmt, ...);
	const char *str() const
	{
		return m_data == 0 ? 0 : (const char *)m_data + 8;
	}
	bool isNotEmpty() const
	{
		return m_data != 0 && ((const AsciiStringData *)m_data)->length != 0;
	}
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

extern WindowManager *g_theWindowManager;

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

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

// ?_bfme_setLivingWorldRegionConquered@@YAXHABVUnicodeString@@ABVAsciiString@@@Z
void _bfme_setLivingWorldRegionConquered(
	int index, const UnicodeString &textValue, const AsciiString &label)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionConquered%d"), index);
	UnicodeString text;
	if (textValue.isNotEmpty())
		text.format(TheGameText->fetch(label), textValue.str());
	g_theWindowManager->bfme_setAptText(variableName, text);
}
