// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// stlport
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::UnicodeString(const wchar_t *s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase((const unsigned short*)s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }
#include "PreRTS.h"
#include <stdio.h>
#include "Common/UserPreferences.h"
class GameWindow;
int GadgetComboBoxGetLength(GameWindow*);
void GadgetComboBoxGetSelectedPos(GameWindow*, int*);
UnicodeString GadgetComboBoxGetText(GameWindow*);
void GadgetComboBoxSetSelectedPos(GameWindow*, int, bool);
extern GameWindow *comboboxRemoteIP;
// Identity: ZH NetworkDirectConnect.cpp UpdateRemoteIPList; RemoteIP0 and
// NumRemoteIPs writes and matched JoinDirectConnectGame's call to this body.
void UpdateRemoteIPList()
{
	Int n1[4], n2[4];
	LANPreferences prefs;
	Int numEntries = GadgetComboBoxGetLength(comboboxRemoteIP);
	Int currentSelection = -1;
	GadgetComboBoxGetSelectedPos(comboboxRemoteIP, &currentSelection);
	UnicodeString unisel = GadgetComboBoxGetText(comboboxRemoteIP);
	AsciiString sel;
	sel.translate(unisel);

//	UnicodeString newEntry = prefs.getRemoteIPEntry(0);
	UnicodeString newEntry = unisel;
	UnicodeString newIP;
	((StringBase<unsigned short> *)&newEntry)->nextToken((StringBase<unsigned short> *)&newIP, (const unsigned short *)UnicodeString(L":").str());
	Int numFields = swscanf(newIP.str(), L"%d.%d.%d.%d", &(n1[0]), &(n1[1]), &(n1[2]), &(n1[3]));

	if (numFields != 4) {
		// this is not a properly formatted IP, don't change a thing.
		return;
	}

	prefs["RemoteIP0"] = sel;

	Int currentINIEntry = 1;

	for (Int i = 0; i < numEntries; ++i)
	{
		if (i != currentSelection)
		{
			GadgetComboBoxSetSelectedPos(comboboxRemoteIP, i, FALSE);
			UnicodeString uni;
			uni = GadgetComboBoxGetText(comboboxRemoteIP);
			AsciiString ascii;
			ascii.translate(uni);

			// prevent more than one copy of an IP address from being put in the list.
			if (currentSelection == -1)
			{
				UnicodeString oldEntry = uni;
				UnicodeString oldIP;
				((StringBase<unsigned short> *)&oldEntry)->nextToken((StringBase<unsigned short> *)&oldIP, (const unsigned short *)UnicodeString(L":").str());

				swscanf(oldIP.str(), L"%d.%d.%d.%d", &(n2[0]), &(n2[1]), &(n2[2]), &(n2[3]));

				Bool isEqual = TRUE;
				for (Int i = 0; (i < 4) && (isEqual == TRUE); ++i) {
					if (n1[i] != n2[i]) {
						isEqual = FALSE;
					}
				}
				// check to see if this is a duplicate or if this is not a properly formatted IP address.
				if (isEqual == TRUE)
				{
					--numEntries;
					continue;
				}
			}
			AsciiString temp;
			temp.format("RemoteIP%d", currentINIEntry);
			++currentINIEntry;
			prefs[temp.str()] = ascii;
		}
	}

	if (currentSelection == -1)
	{
		++numEntries;
	}

	AsciiString numRemoteIPs;
	numRemoteIPs.format("%d", numEntries);

	prefs["NumRemoteIPs"] = numRemoteIPs;

	prefs.write();
}

