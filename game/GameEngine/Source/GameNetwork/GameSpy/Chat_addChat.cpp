// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// GameSpyInfo::addChat, RVA 0x00625AF0, 955 bytes.
// Identity: Chat.cpp source family, GUIMessageReceived and chat-format literals,
// and WOLGameSetupMenuUpdate's GameSpyInfoInterface slot 0xF0 caller.
// Native PlayerInfo +4 base nickname, +0x14 profile ID, +0x18 flags;
// GameSpyInfo text flags +0x244/+0x245. Full witnesses: astra_P/LAYOUTS.md.
// This TU keeps the original Chat.cpp STL claims in their existing environment.
// The visible noinline comparison is independently exact at 0x0005FEB0 (92 B).
// QAE AudioEventRTS destructor selects the proved 162-byte native body at
// 0x000B31F0, via ILT 0x00026F35; the UAE ledger name selects a different body.
#include <map>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include <string.h>
#pragma intrinsic(memcmp)
template <> __declspec(noinline) int StringBase<char>::compare(const StringBase<char>& other) const {
    const int len = other.m_data ? other.m_data->length : 0;
    const char *data = other.m_data ? other.m_data->data : "";
    const int myLen = m_data ? m_data->length : 0;
    const char *myData = m_data ? m_data->data : "";
    int result = memcmp(myData, data, myLen<len?myLen:len);
    if (result == 0) result = myLen-len;
    return result;
}
template <class T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }
template <> inline const wchar_t *StringBase<wchar_t>::str() const { return m_data ? m_data->data : L""; }
typedef bool Bool;
typedef int Int;
typedef wchar_t WideChar;
#define FALSE false
#define TRUE true
class GameWindow;
class PlayerInfo { public:
    PlayerInfo(); PlayerInfo(const PlayerInfo&); ~PlayerInfo();
    AsciiString m_name, m_baseName, m_locale;
    int m_wins, m_losses, m_profileID, m_flags, m_rankPoints;
    int field_20, field_24, field_28, m_side, m_preorder;
};
class BuddyInfo { public:
    int m_id; AsciiString m_name, m_email, m_countryCode;
    int m_status; UnicodeString m_statusString, m_locationString;
};
typedef std::map<int, BuddyInfo> BuddyInfoMap;
class AudioEventRTS { public:
    AudioEventRTS(const AsciiString &, int);
    ~AudioEventRTS();
    void *vptr;
    unsigned char field_04[0x6c];
};
class AudioManager { public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0C();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1C();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2C();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3C();
    virtual void slot_40();
    virtual unsigned int addAudioEvent(const AudioEventRTS *);
};
class LanguageFilter { public: void filterLine(UnicodeString &); };
extern AudioManager *TheAudio;
extern LanguageFilter *TheLanguageFilter;
extern int GameSpyColor[];
void GadgetListBoxSetItemData(GameWindow *, void *, int, int);
class GameSpyInfoInterface { public:
    virtual void slot_00() = 0;
    virtual void slot_04() = 0;
    virtual void slot_08() = 0;
    virtual void slot_0C() = 0;
    virtual void slot_10() = 0;
    virtual void slot_14() = 0;
    virtual void slot_18() = 0;
    virtual void slot_1C() = 0;
    virtual void slot_20() = 0;
    virtual void slot_24() = 0;
    virtual void slot_28() = 0;
    virtual void slot_2C() = 0;
    virtual void slot_30() = 0;
    virtual void slot_34() = 0;
    virtual void slot_38() = 0;
    virtual void slot_3C() = 0;
    virtual void slot_40() = 0;
    virtual void slot_44() = 0;
    virtual void slot_48() = 0;
    virtual void slot_4C() = 0;
    virtual void slot_50() = 0;
    virtual BuddyInfoMap *getBuddyMap() = 0;
    virtual void slot_58() = 0;
    virtual void slot_5C() = 0;
    virtual void slot_60() = 0;
    virtual void slot_64() = 0;
    virtual AsciiString getLocalName() = 0;
    virtual void slot_6C() = 0;
    virtual void slot_70() = 0;
    virtual void slot_74() = 0;
    virtual void slot_78() = 0;
    virtual void slot_7C() = 0;
    virtual void slot_80() = 0;
    virtual void slot_84() = 0;
    virtual void slot_88() = 0;
    virtual void slot_8C() = 0;
    virtual void slot_90() = 0;
    virtual void slot_94() = 0;
    virtual void slot_98() = 0;
    virtual void slot_9C() = 0;
    virtual void slot_A0() = 0;
    virtual void slot_A4() = 0;
    virtual void slot_A8() = 0;
    virtual void slot_AC() = 0;
    virtual void slot_B0() = 0;
    virtual void slot_B4() = 0;
    virtual void slot_B8() = 0;
    virtual void slot_BC() = 0;
    virtual void slot_C0() = 0;
    virtual void slot_C4() = 0;
    virtual void slot_C8() = 0;
    virtual void slot_CC() = 0;
    virtual void slot_D0() = 0;
    virtual void slot_D4() = 0;
    virtual void slot_D8() = 0;
    virtual void slot_DC() = 0;
    virtual void slot_E0() = 0;
    virtual void slot_E4() = 0;
    virtual void slot_E8() = 0;
    virtual int addText(UnicodeString, int, GameWindow *) = 0;
    virtual void addChat(PlayerInfo, UnicodeString, bool, bool, GameWindow *) = 0;
    virtual void slot_F4() = 0;
    virtual void slot_F8() = 0;
    virtual void slot_FC() = 0;
    virtual void slot_100() = 0;
    virtual void slot_104() = 0;
    virtual void slot_108() = 0;
    virtual void slot_10C() = 0;
    virtual void slot_110() = 0;
    virtual void slot_114() = 0;
    virtual void slot_118() = 0;
    virtual void slot_11C() = 0;
    virtual void slot_120() = 0;
    virtual void slot_124() = 0;
    virtual void slot_128() = 0;
    virtual bool isSavedIgnored(int) = 0;
    virtual void slot_130() = 0;
    virtual void slot_134() = 0;
    virtual void slot_138() = 0;
    virtual void slot_13C() = 0;
    virtual void slot_140() = 0;
    virtual bool isIgnored(AsciiString) = 0;
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameSpyInfo : public GameSpyInfoInterface { public:
    virtual void addChat(PlayerInfo, UnicodeString, bool, bool, GameWindow *);
    unsigned char field_04[0x240];
    bool m_disallowAsainText, m_disallowNonAsianText;
};
typedef char PlayerInfoSize[sizeof(PlayerInfo)==0x34?1:-1];
typedef char AudioEventSize[sizeof(AudioEventRTS)==0x70?1:-1];
void GameSpyInfo::addChat( PlayerInfo p, UnicodeString msg, Bool isPublic, Bool isAction, GameWindow *win )
{
	Int style;
	Bool isMe = ((const StringBase<char>*)&p.m_baseName)->compare(*(const StringBase<char>*)&TheGameSpyInfo->getLocalName()) == 0;
	if(!isMe && (isSavedIgnored(p.m_profileID) || isIgnored(p.m_baseName)))
		return;
	
	Bool isOwner = p.m_flags & 0x20;
	Bool isBuddy = getBuddyMap()->find(p.m_profileID) != getBuddyMap()->end();


	if(!isMe)
	{
		if(m_disallowAsainText)
		{
			const WideChar *buff = msg.str();
			Int length =  msg.getLength();	
			for(Int i = 0; i < length; ++i)
			{
				if(buff[i] >= 256)
					return;
			}
		}
		else if(m_disallowNonAsianText)
		{
			const WideChar *buff = msg.str();
			Int length =  msg.getLength();	
			Bool hasUnicode = FALSE;
			for(Int i = 0; i < length; ++i)
			{
				if(buff[i] >= 256)
				{
					hasUnicode = TRUE;
					break;
				}
			}
			if(!hasUnicode)
				return;
		}

		if (!isPublic)
		{
			AudioEventRTS privMsgAudio("GUIMessageReceived", 2);

			if( TheAudio )
			{
				TheAudio->addAudioEvent( &privMsgAudio );
			}  // end if
		}
	}


	if (isBuddy)
	{
		style = 21;
	}
	else if (isPublic && isAction)
	{
		style = (isOwner)?16:14;
	}
	else if (isPublic)
	{
		style = (isOwner)?15:13;
	}
	else if (isAction)
	{
		style = (isOwner)?20:18;
	}
	else
	{
		style = (isOwner)?19:17;
	}

	UnicodeString name;
	name.translate(p.m_baseName);

	// filters language
//  if( TheGlobalData->m_languageFilterPref )
//  {
    TheLanguageFilter->filterLine(msg);
//  }

	UnicodeString fullMsg;
	if (isAction)
	{
		fullMsg.format( UnicodeString(L"%ls %ls"), name.str(), msg.str() );
	}
	else
	{
		fullMsg.format( UnicodeString(L"[%ls] %ls"), name.str(), msg.str() );
	}

	Int index = addText(fullMsg, GameSpyColor[style], win);
	if (index >= 0)
	{
		GadgetListBoxSetItemData(win, (void *)p.m_profileID, index, 0);
	}
}

