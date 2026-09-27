// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME updateNumPlayersOnline, RVA 0x0050BA40 (1421 bytes).
// Port of EA's GPL-3.0-or-later ZH WOLWelcomeMenu.cpp helper.
// Identity: the WOLWelcomeMenu.wnd:StaticTextNumPlayersOnline widget key,
// GUI:NumPlayersOnline and MOTD:NumPlayersHeading labels and the matched
// HandleNumPlayersOnline neighbour establish this helper's purpose.
// Retail retains the heading's player-count vararg removed by the later ZH
// patch. StringBase uses its native 8-byte buffer header; STLport's static
// allocator path releases the temporary returned by MultiByteToWideCharSingleLine.

#define _STLP_USE_STATIC_LIB 1
#include <stddef.h>
#include "Common/UnicodeString.h"
#include "Common/AsciiString.h"
#include <string>
#include <stdlib.h>
#include <string.h>
#pragma intrinsic(strlen)
template<class T> inline StringBase<T>::~StringBase() {releaseBuffer();}
template<class T> inline int StringBase<T>::getLength() const {return m_data?m_data->length:0;}
template<class T> inline T StringBase<T>::getCharAt(int i) const {return m_data?m_data->data[i]:0;}
template<class T> inline bool StringBase<T>::isEmpty() const {return !m_data || m_data->length==0;}
template<> inline const char *StringBase<char>::str() const {return m_data?m_data->data:"";}
template<> inline const wchar_t *StringBase<wchar_t>::str() const {return m_data?m_data->data:L"";}
template<> inline bool StringBase<char>::startsWith(const char *s) const {return startsWith(s,strlen(s));}
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->~StringBase<char>(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->~StringBase<wchar_t>(); }
inline AsciiString &AsciiString::operator=(const char *s) { ((StringBase<char>*)this)->set(s,s?strlen(s):0); return *this; }
typedef int Int;
typedef unsigned char UnsignedByte;
typedef int Color;
enum NameKeyType {};
class GameWindow;
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)
class GameWindowManager { public:
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
 virtual void slot6C();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7C();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8C();
 virtual void slot90();
 virtual void slot94();
 virtual void slot98();
 virtual void slot9C();
 virtual void slotA0();
 virtual void slotA4();
 virtual void slotA8();
 virtual void slotAC();
 virtual void slotB0();
 virtual void slotB4();
 virtual void slotB8();
 virtual void slotBC();
 virtual void slotC0();
 virtual void slotC4();
 virtual void slotC8();
 virtual void slotCC();
 virtual void slotD0();
 virtual void slotD4();
 virtual void slotD8();
 virtual GameWindow *winGetWindowFromId(GameWindow*,NameKeyType);
};
extern GameWindowManager *TheWindowManager;
class GameTextInterface { public:
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
 virtual UnicodeString fetch(const char*,bool *exists=0);
};
extern GameTextInterface *TheGameText;
class GameSpyInfo { public:
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00C();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01C();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02C();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03C();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04C();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05C();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06C();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07C();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08C();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09C();
 virtual void slot0A0();
 virtual void slot0A4();
 virtual void slot0A8();
 virtual void slot0AC();
 virtual void slot0B0();
 virtual void slot0B4();
 virtual void slot0B8();
 virtual void slot0BC();
 virtual void slot0C0();
 virtual void slot0C4();
 virtual void slot0C8();
 virtual void slot0CC();
 virtual void slot0D0();
 virtual void slot0D4();
 virtual void slot0D8();
 virtual void slot0DC();
 virtual void slot0E0();
 virtual void slot0E4();
 virtual void slot0E8();
 virtual void slot0EC();
 virtual void slot0F0();
 virtual void slot0F4();
 virtual void slot0F8();
 virtual void slot0FC();
 virtual void slot100();
 virtual const AsciiString &getMOTD();
};
extern GameSpyInfo *TheGameSpyInfo;
extern GameWindow *rva0050BA40_listboxInfo;
extern int rva0050BA40_lastNumPlayersOnline;
extern Color GameSpyColor[];
enum {GSCOLOR_MOTD=27,GSCOLOR_MOTD_HEADING=28};
void GadgetStaticTextSetText(GameWindow*,UnicodeString);
void GadgetListBoxReset(GameWindow*);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool=true);
std::wstring MultiByteToWideCharSingleLine(const char*);
inline Color GameMakeColor(UnsignedByte r,UnsignedByte g,UnsignedByte b,UnsignedByte a) {return (a<<24)|(r<<16)|(g<<8)|b;}
#define NULL 0
#define DEBUG_LOG(x)
static UnsignedByte grabUByte(const char *s)
{
	char tmp[5] = "0xff";
	tmp[2] = s[0];
	tmp[3] = s[1];
	UnsignedByte b = strtol(tmp, NULL, 16);
	return b;
}

void updateNumPlayersOnline(void)
{
	GameWindow *playersOnlineWindow = TheWindowManager->winGetWindowFromId(
		NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextNumPlayersOnline") );

	if (playersOnlineWindow)
	{
		UnicodeString valStr;
		valStr.format(TheGameText->fetch("GUI:NumPlayersOnline"), rva0050BA40_lastNumPlayersOnline);
		GadgetStaticTextSetText(playersOnlineWindow, valStr);
	}

	if (rva0050BA40_listboxInfo && TheGameSpyInfo)
	{
		GadgetListBoxReset(rva0050BA40_listboxInfo);
		AsciiString aLine;
		UnicodeString line;
		AsciiString aMotd = TheGameSpyInfo->getMOTD();
		UnicodeString headingStr;
		//Kris: Patch 1.01 - November 12, 2003
		//Removed number of players from string, and removed the argument. The number is incorrect anyways...
		//This was a Harvard initiated fix.
		headingStr.format(TheGameText->fetch("MOTD:NumPlayersHeading"), rva0050BA40_lastNumPlayersOnline);

		while (headingStr.nextToken(&line, UnicodeString(L"\n")))
		{
			if (line.getCharAt(line.getLength()-1) == '\r')
				line.removeLastChar();	// there is a trailing '\r'

			line.trim();

			if (line.isEmpty())
			{
				line = UnicodeString(L" ");
			}

			GadgetListBoxAddEntryText(rva0050BA40_listboxInfo, line, GameSpyColor[GSCOLOR_MOTD_HEADING], -1, -1);
		}
		GadgetListBoxAddEntryText(rva0050BA40_listboxInfo, UnicodeString(L" "), GameSpyColor[GSCOLOR_MOTD_HEADING], -1, -1);

		while (aMotd.nextToken(&aLine, "\n"))
		{
			if (aLine.getCharAt(aLine.getLength()-1) == '\r')
				aLine.removeLastChar();	// there is a trailing '\r'

			aLine.trim();

			if (aLine.isEmpty())
			{
				aLine = " ";
			}

			Color c = GameSpyColor[GSCOLOR_MOTD];
			if (aLine.startsWith("\\\\"))
			{
				aLine = aLine.str()+1;
			}
			else if (aLine.startsWith("\\") && aLine.getLength() > 9)
			{
				// take out the hex value from strings starting as "\ffffffffText"
				UnsignedByte a, r, g, b;
				a = grabUByte(aLine.str()+1);
				r = grabUByte(aLine.str()+3);
				g = grabUByte(aLine.str()+5);
				b = grabUByte(aLine.str()+7);
				c = GameMakeColor(r, g, b, a);
				DEBUG_LOG(("MOTD line '%s' has color %X\n", aLine.str(), c));
				aLine = aLine.str() + 9;
			}
			line = UnicodeString(MultiByteToWideCharSingleLine(aLine.str()).c_str());

			GadgetListBoxAddEntryText(rva0050BA40_listboxInfo, line, c, -1, -1);
		}
	}
}
