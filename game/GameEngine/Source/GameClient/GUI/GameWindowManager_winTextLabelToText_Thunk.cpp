// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ conversion of GameWindowManager::winTextLabelToText.

struct StringData
{
	int RefCount;
	unsigned short Length;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
	bool isEmpty() const { return Data == 0 || Data->Length == 0; }

private:
	StringData *Data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so its copy ctor is a forwarder retail inlines: the
// call site encodes the base body at 0x00888400
// (??0?$StringBase@G@@AAE@ABV0@@Z). The delegation has to be visible here
// for this TU to encode the same call.
#include "string_base.h"

class UnicodeString
{
public:
	UnicodeString() : Data(0) {}
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}
	~UnicodeString();
	void translate(const AsciiString &);

	// Retail's storage is ?TheEmptyString@UnicodeString@@2V1@A (0x00F36E54),
	// which is what Common/System/UnicodeString.cpp -- the only TU that
	// defines the datum -- exports. The `const` is what decides the trailing
	// access code: `static const UnicodeString` mangles ...@2V1@B and no
	// object in the tree defines that, so only its address was ever taken.
	static UnicodeString TheEmptyString;

private:
	StringData *Data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	UnicodeString winTextLabelToText(AsciiString label);
};

UnicodeString GameWindowManager::winTextLabelToText(AsciiString label)
{
	if (label.isEmpty()) {
		return UnicodeString::TheEmptyString;
	}

	UnicodeString text;
	text.translate(label);
	return text;
}
