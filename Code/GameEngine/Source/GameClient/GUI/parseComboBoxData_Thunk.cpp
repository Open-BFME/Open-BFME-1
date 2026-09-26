// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift parseComboBoxData to clean C++.

#include <stdio.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

class WinInstanceData;

struct ComboBoxData
{
	Bool isEditable;
	char m_pad[3];
	Int maxDisplay;
	Int maxChars;
	unsigned int flags;
};

static Int scanBool(const char *source, Bool &value)
{
	Int parsedInteger = 0;
	Int conversionCount = sscanf(source, "%d", &parsedInteger);
	value = (Bool)parsedInteger;
	return conversionCount;
}

static Int scanInt(const char *source, Int &val)
{
	return sscanf(source, "%d", &val);
}

// ?parseComboBoxData@@YA_NPADPAVWinInstanceData@@0PAX@Z
bool __cdecl parseComboBoxData(char *, WinInstanceData *, char *buffer, void *rawComboData)
{
	ComboBoxData *comboData = (ComboBoxData *)rawComboData;
	char *fieldToken;
	char *fieldDelimiters = " :,\n\r\t";

	fieldToken = strtok(buffer, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	scanBool(fieldToken, comboData->isEditable);

	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	scanInt(fieldToken, comboData->maxChars);

	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	scanInt(fieldToken, comboData->maxDisplay);

	comboData->flags = 0;
	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	Bool asciiOnly;
	scanBool(fieldToken, asciiOnly);
	if (asciiOnly)
		comboData->flags |= 0x10;

	fieldToken = strtok(0, fieldDelimiters);
	fieldToken = strtok(0, fieldDelimiters);
	Bool lettersAndNumbersOnly;
	scanBool(fieldToken, lettersAndNumbersOnly);
	if (lettersAndNumbersOnly)
		comboData->flags |= 0x40;

	return true;
}
