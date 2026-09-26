// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Igame/Libraries/Source/WWVegas/WWLib
// INI::isDeclarationOfType, retail RVA 0x00851BF0 / 510 bytes.
// Original predicate flow: restore both temporary string terminators before returning.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)
#define stricmp _strcmpi

template<> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

template<> inline int StringBase<char>::getLength() const
{
	return m_data ? m_data->length : 0;
}

template<> inline const char *StringBase<char>::str() const
{
	return m_data ? &m_data->data[0] : (const char *)"";
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class INI {
public:
	static bool __cdecl isDeclarationOfType(AsciiString blockType,
		AsciiString blockName, char *bufferToCheck);
};

bool __cdecl INI::isDeclarationOfType(AsciiString blockType,
	AsciiString blockName, char *bufferToCheck)
{
	bool retVal = true;
	if (!bufferToCheck || blockType.isEmpty() || blockName.isEmpty()) {
		return false;
	}

	char restoreChar;
	char *tempBuff = bufferToCheck;
	int blockTypeLength = blockType.getLength();
	int blockNameLength = blockName.getLength();

	while (isspace(*tempBuff)) {
		++tempBuff;
	}

	if (strlen(tempBuff) > blockTypeLength) {
		restoreChar = tempBuff[blockTypeLength];
		tempBuff[blockTypeLength] = 0;

		if (stricmp(blockType.str(), tempBuff) != 0) {
			retVal = false;
		}

		tempBuff[blockTypeLength] = restoreChar;
		tempBuff = tempBuff + blockTypeLength;
	} else {
		retVal = false;
	}

	while (isspace(*tempBuff)) {
		++tempBuff;
	}

	if (strlen(tempBuff) > blockNameLength) {
		restoreChar = tempBuff[blockNameLength];
		tempBuff[blockNameLength] = 0;

		if (stricmp(blockName.str(), tempBuff) != 0) {
			retVal = false;
		}

		tempBuff[blockNameLength] = restoreChar;
		tempBuff = tempBuff + blockNameLength;
	} else {
		retVal = false;
	}

	while (strlen(tempBuff)) {
		retVal = retVal && isspace(tempBuff[0]);
		++tempBuff;
	}

	return retVal;
}
