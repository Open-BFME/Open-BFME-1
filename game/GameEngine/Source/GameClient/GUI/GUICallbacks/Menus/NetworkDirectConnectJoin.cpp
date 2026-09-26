// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define BFME_ASCIISTRING_CSTR_CTOR_NOINLINE
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#define ASCIISTRING_H
#include "Common/AsciiString.h"

#define UNICODESTRING_H
template <typename T> struct BfmeStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : m_data(0) {}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}

	UnicodeString &operator=(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other);
		return *this;
	}

	unsigned short getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	int compareNoCase(const UnicodeString &other) const;

	const unsigned short *str() const
	{
		static const unsigned short empty[] = { 0 };
		return m_data ? m_data->m_text : empty;
	}

	void removeLastChar()
	{
		((StringBase<unsigned short> *)this)->removeLastChar();
	}

private:
	BfmeStringData<unsigned short> *m_data;
};

#include "PreRTS.h"

#include <stdio.h>
#include <string.h>

#include "Common/QuotedPrintable.h"
#include "Common/UserPreferences.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTextEntry.h"

// Retail's direct-connect body passes the BFME address pair to vtable slot 12
// as a temporary; a named local keeps its own frame slot and makes the frame
// four bytes too big.
// The caller ILT at 0x000208E7 names this body JoinDirectConnectGame; the
// class owner is otherwise left unclaimed here.
struct BfmeNetAddress
{
	BfmeNetAddress(UnsignedInt ip, UnsignedShort port) : m_ip(ip), m_port(port) {}
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

#define BFME_SLOT(n) virtual void bfmeSlot##n(void);
class LANAPI
{
public:
	LANAPI();
	BFME_SLOT(00) BFME_SLOT(01) BFME_SLOT(02) BFME_SLOT(03)
	BFME_SLOT(04) BFME_SLOT(05) BFME_SLOT(06) BFME_SLOT(07)
	BFME_SLOT(08) BFME_SLOT(09) BFME_SLOT(10) BFME_SLOT(11)
	virtual void requestGameJoinDirectConnectAddress(const BfmeNetAddress &address);
	BFME_SLOT(13) BFME_SLOT(14) BFME_SLOT(15) BFME_SLOT(16)
	BFME_SLOT(17) BFME_SLOT(18) BFME_SLOT(19) BFME_SLOT(20)
	BFME_SLOT(21) BFME_SLOT(22) BFME_SLOT(23)
	virtual void RequestSetName(UnicodeString newName);
	BFME_SLOT(25) BFME_SLOT(26) BFME_SLOT(27) BFME_SLOT(28)
	BFME_SLOT(29) BFME_SLOT(30) BFME_SLOT(31) BFME_SLOT(32)
	BFME_SLOT(33) BFME_SLOT(34) BFME_SLOT(35) BFME_SLOT(36)
	BFME_SLOT(37) BFME_SLOT(38) BFME_SLOT(39) BFME_SLOT(40)
	BFME_SLOT(41) BFME_SLOT(42) BFME_SLOT(43) BFME_SLOT(44)
	BFME_SLOT(45) BFME_SLOT(46) BFME_SLOT(47) BFME_SLOT(48)
	BFME_SLOT(49) BFME_SLOT(50) BFME_SLOT(51) BFME_SLOT(52)
	BFME_SLOT(53) BFME_SLOT(54) BFME_SLOT(55)

	unsigned char m_storage[0x64];
};
#undef BFME_SLOT

typedef char BfmeLANAPISizeCheck[(sizeof(LANAPI) == 0x68) ? 1 : -1];

extern LANAPI *TheLAN;
static const Int g_lanPlayerNameLength = 12;
extern GameWindow *comboboxRemoteIP;
extern GameWindow *editPlayerName;

void UpdateRemoteIPList();
void PopulateRemoteIPComboBox();

void JoinDirectConnectGame()
{
	if (!TheLAN)
	{
		TheLAN = NEW LANAPI();
	}

	UnicodeString ipunistring = GadgetComboBoxGetText(comboboxRemoteIP);
	AsciiString asciientry;
	asciientry.translate(ipunistring);

	AsciiString ipstring;
	asciientry.nextToken(&ipstring, "(");

	char ipstr[16];
	strcpy(ipstr, ipstring.str());

	Int ip1, ip2, ip3, ip4;
	sscanf(ipstr, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);

	DEBUG_LOG(("JoinDirectConnectGame - joining at %d.%d.%d.%d\n", ip1, ip2, ip3, ip4));
	UnsignedInt ipaddress = (ip1 << 24) + (ip2 << 16) + (ip3 << 8) + ip4;

	UnicodeString name;
	name = GadgetTextEntryGetText(editPlayerName);

	LANPreferences prefs;
	prefs["UserName"] = UnicodeStringToQuotedPrintable(name);
	prefs.write();

	UpdateRemoteIPList();
	PopulateRemoteIPComboBox();

	while (name.getLength() > g_lanPlayerNameLength)
		name.removeLastChar();
	TheLAN->RequestSetName(name);

	TheLAN->requestGameJoinDirectConnectAddress(BfmeNetAddress(ipaddress, 0x1f98));
}
