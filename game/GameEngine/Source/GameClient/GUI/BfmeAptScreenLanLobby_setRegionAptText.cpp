// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0051A850 / 0x0051A8F0 / 0x0051AAA0: format APT:LivingWorldRegion*%d
// and push the result through WindowManager::bfme_setAptText. format is
// __cdecl so this is a stack argument (add esp, 0xc).
typedef char Bool;

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct UnicodeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	void format(UnicodeString fmt, ...);
	bool isNotEmpty() const
	{
		return m_data != 0 && ((const UnicodeStringData *)m_data)->length != 0;
	}
	~UnicodeString() {}
};

// UnicodeString::str, expanded in place.  An inline member would emit a
// ?str@UnicodeString@@QBEPBGXZ COMDAT that is not retail's body (0x0005F270).
// The buffer pointer is the string's first word; the text starts at +8.
static __forceinline const unsigned short *wideStr(const UnicodeString &string)
{
	const unsigned short *data = *reinterpret_cast<const unsigned short * const *>(&string);
	return data == 0 ? 0 : data + 4;
}

struct AsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

extern WindowManager *g_rva012F19E8WindowManager;	///< retail [0x012F19E8]

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
	g_rva012F19E8WindowManager->bfme_setAptText(variableName, text);
}

// ?_bfme_setLivingWorldRegionBonus@@YAXHABVUnicodeString@@@Z
void _bfme_setLivingWorldRegionBonus(int index, const UnicodeString &text)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionBonus%d"), index);
	g_rva012F19E8WindowManager->bfme_setAptText(variableName, text);
}

// ?_bfme_setLivingWorldRegionConqueredBonus@@YAXHABVUnicodeString@@@Z
void _bfme_setLivingWorldRegionConqueredBonus(int index, const UnicodeString &text)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionConqueredBonus%d"), index);
	g_rva012F19E8WindowManager->bfme_setAptText(variableName, text);
}

// ?_bfme_setLivingWorldRegionConquered@@YAXHABVUnicodeString@@ABVAsciiString@@@Z
void _bfme_setLivingWorldRegionConquered(
	int index, const UnicodeString &textValue, const AsciiString &label)
{
	AsciiString variableName;
	variableName.format(AsciiString("APT:LivingWorldRegionConquered%d"), index);
	UnicodeString text;
	if (textValue.isNotEmpty())
		text.format(TheGameText->fetch(label), wideStr(textValue));
	g_rva012F19E8WindowManager->bfme_setAptText(variableName, text);
}
