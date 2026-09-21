// ?d_000acd50@@YAXXZ
// partial score=0.35 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define private public
#include "PreRTS.h"
#include <map>
#include <stdio.h>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#undef private
#include <string.h>

#pragma intrinsic(strlen)

class Rva00083DA0Host
{
public:
	StringBase<unsigned short> copyStringAt1280(void);
};

#define TheWritableGlobalData (*(Rva00083DA0Host **)0x012ED5C8)

typedef char *(__cdecl *BfmeFgetsProc)(char *, int, FILE *);
#define BfmeFgets (*(volatile BfmeFgetsProc *)0x013593B0)

typedef std::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences(void);
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);
	virtual Bool load(const UnicodeString &filename);
	virtual void unused14(void);
	virtual AsciiString getAsciiString(AsciiString key, AsciiString defaultValue) const;
	virtual void setAsciiString(AsciiString key, AsciiString value);

protected:
	StringBase<unsigned short> m_filename;
};

Bool UserPreferences::load(const UnicodeString &filename)
{
	UserPreferences *self = this;
	StringBase<unsigned short> path =
		TheWritableGlobalData->copyStringAt1280();
	self->m_filename.set(path);
	unsigned short *filenameText = *(unsigned short **)&filename;
	int filenameLength = 0;
	if (filenameText != 0) {
		filenameLength = *(unsigned short *)((char *)filenameText + 4);
		filenameText = (unsigned short *)((char *)filenameText + 8);
	} else {
		filenameText = (unsigned short *)0x0107388C;
	}
	self->m_filename.concat(filenameText, filenameLength);

	unsigned short *openText = *(unsigned short **)&self->m_filename;
	if (openText != 0) {
		openText = (unsigned short *)((char *)openText + 8);
	} else {
		openText = (unsigned short *)0x0107388C;
	}
	FILE *file = _wfopen((const wchar_t *)openText, L"r");
	if (file != 0) {
		char buffer[2048];
		while (BfmeFgets(buffer, 2048, file) != 0) {
			AsciiString line(buffer);
			line.trim();
			AsciiString key;
			AsciiString value;
			line.nextToken(&key, "=");
			char *lineText = *(char **)&line;
			if (lineText != 0) {
				lineText += 8;
			} else {
				lineText = (char *)0x0107388B;
			}
			const char *valueText = lineText + 1;
			((StringBase<char> *)&value)->set(valueText, strlen(valueText));
			key.trim();
			value.trim();
			if (key.isNotEmpty() && value.isNotEmpty()) {
				(*self)[key] = value;
			}
		}
		fclose(file);
		return true;
	}
	return false;
}
