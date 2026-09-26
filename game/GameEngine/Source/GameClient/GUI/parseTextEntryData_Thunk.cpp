// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift parseTextEntryData to clean C++.

#include <stdio.h>
#include <string.h>

typedef bool Bool;
typedef int Int;
typedef short Short;

class WinInstanceData;

struct EntryData
{
	void *text;
	void *secretTextDisplay;
	void *constructText;
	unsigned int flags;
	Short maxTextLen;
	Bool secretText;
};

static Int scanBool(const char *source, Bool &val)
{
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	val = (Bool)temp;
	return ret;
}

static Int scanShort(const char *source, Short &value)
{
	Int parsedInteger = 0;
	Int conversionCount = sscanf(source, "%d", &parsedInteger);
	value = (Short)parsedInteger;
	return conversionCount;
}

// ?parseTextEntryData@@YA_NPADPAVWinInstanceData@@0PAX@Z
bool __cdecl parseTextEntryData(char *, WinInstanceData *, char *buffer, void *rawEntryData)
{
	EntryData *entryData = (EntryData *)rawEntryData;
	char *fieldToken;
	char *fieldDelimiters = " :,\n\r\t";

	fieldToken = strtok(buffer, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	scanShort(fieldToken, entryData->maxTextLen);

	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	scanBool(fieldToken, entryData->secretText);

	entryData->flags = 0;
	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	Bool numericalOnly;
	scanBool(fieldToken, numericalOnly);
	if (numericalOnly)
		entryData->flags |= 0x20;

	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	Bool alphaNumericalOnly;
	scanBool(fieldToken, alphaNumericalOnly);
	if (alphaNumericalOnly)
		entryData->flags |= 0x40;

	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	Bool asciiOnly;
	scanBool(fieldToken, asciiOnly);
	if (asciiOnly)
		entryData->flags |= 0x10;

	return true;
}
