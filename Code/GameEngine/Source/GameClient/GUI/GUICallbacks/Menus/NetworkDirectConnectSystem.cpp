// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib

#define BFME_ASCIISTRING_CSTR_CTOR_NOINLINE
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// stlport

#define UNICODESTRING_H

#include "string_base.h"

template<> inline StringBase<unsigned short>::StringBase() : m_data(0) {}

class AsciiString;

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(*(const StringBase<unsigned short> *)&other);
		return *this;
	}
	UnicodeString &operator=(const unsigned short *text)
	{
		StringBase<unsigned short>::set(text);
		return *this;
	}

	int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	void removeLastChar()
	{
		StringBase<unsigned short>::removeLastChar();
	}

	void translate(const AsciiString &other);

	int compareNoCase(const UnicodeString &other) const
	{
		return StringBase<unsigned short>::compareNoCase(
			*(const StringBase<unsigned short> *)&other);
	}
};

inline bool operator<(const UnicodeString &left, const UnicodeString &right)
{
	return *(const StringBase<unsigned short> *)&left <
		*(const StringBase<unsigned short> *)&right;
}

#include "PreRTS.h"
#include "GameSpy/peer/peer.h"
#include "Common/QuotedPrintable.h"
#include "Common/UserPreferences.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/Shell.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameNetwork/IPEnumeration.h"

class LANAPI
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
	virtual void RequestSetName(UnicodeString newName);
};

extern Bool LANbuttonPushed;
extern Bool buttonPushed;
extern LANAPI *TheLAN;
extern NameKeyType buttonBackID;
extern NameKeyType buttonHostID;
extern NameKeyType buttonJoinID;
extern GameWindow *editPlayerName;

void HostDirectConnectGame();
void JoinDirectConnectGame();

// ?NetworkDirectConnectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType NetworkDirectConnectSystem(GameWindow *window,
	UnsignedInt msg, UnsignedInt mData1, UnsignedInt mData2)
{
	UnicodeString txtInput;

	switch (msg)
	{
		case GWM_CREATE:
		{
			break;
		}

		case GWM_DESTROY:
		{
			break;
		}

		case GWM_INPUT_FOCUS:
		{
			if (mData1 == 1)
				*(Bool *)mData2 = true;

			return MSG_HANDLED;
		}

		case GBM_SELECTED:
		{
			if (buttonPushed)
				break;

			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			if (controlID == buttonBackID)
			{
				UnicodeString name;
				name = GadgetTextEntryGetText(editPlayerName);

				LANPreferences prefs;
				prefs["UserName"] = UnicodeStringToQuotedPrintable(name);
				prefs.write();

				while (name.getLength() > 12)
					name.removeLastChar();
				TheLAN->RequestSetName(name);

				buttonPushed = true;
				LANbuttonPushed = true;
				TheShell->pop();
			}
			else if (controlID == buttonHostID)
			{
				HostDirectConnectGame();
			}
			else if (controlID == buttonJoinID)
			{
				JoinDirectConnectGame();
			}
			break;
		}

		case GEM_EDIT_DONE:
		{
			break;
		}
		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
