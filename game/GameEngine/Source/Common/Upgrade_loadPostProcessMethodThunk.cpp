// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00109560 is a global Unicode registry display-name getter.  It was
// previously misidentified as Upgrade::loadPostProcess, whose reference body
// is empty and whose this pointer the retail function never reads.

#include "string_base.h"

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	~UnicodeString() {}
};

bool getStringFromRegistry(
	void *root, UnicodeString path, UnicodeString key, UnicodeString &value);

// ?getBfmeDisplayName@@YA?AVUnicodeString@@XZ
UnicodeString getBfmeDisplayName()
{
	UnicodeString value(L"The Battle for Middle-earth");
	getStringFromRegistry(
		reinterpret_cast<void *>(0x80000002),
		UnicodeString(L"SOFTWARE\\EA Games\\The Battle for Middle-earth"),
		UnicodeString(L"DisplayName"),
		value);
	return value;
}
