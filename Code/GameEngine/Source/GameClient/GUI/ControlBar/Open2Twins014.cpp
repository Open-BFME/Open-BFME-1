// cl: /DNDEBUG /MD /EHsc
//
// A portrait chooser landed as a relocation-blind twin of
// Code/GameEngine/Source/GameClient/GUI/ControlBar/GetSelectedPortraitImage_Thunk.cpp
// (0x00143890).  It differs from the model in its own statics and atexit
// registrations -- automatic once the function is distinct -- in the image it
// looks up ("HPGandalfGrey" rather than "HIGandalTheGrey") and in the
// template accessor it finally calls.
//
// The template flag word and the bit tested are the same in both, so the same
// alternate-form check is being made against a different portrait.

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Image;

class Open2Logic143730
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

class Open2Images143730
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class Open2Template143730
{
public:
	unsigned char m_beforeName[0x20];
	AsciiString m_name;
	unsigned char m_beforeKindOf[0x128 - 0x24];
	unsigned int m_kindOfWord;

	const Image *getSelectedPortraitImage() const;
};

extern Open2Logic143730 *TheOpen2Logic143730;
extern Open2Images143730 *TheOpen2Images143730;

// The relevant BFME template flags are in the word at +0x128.  Bit 17
// distinguishes the alternate GondorGandalf form at this call site.
static const unsigned int OPEN2_MOUNTED_MASK = 0x00020000;

// @?Open2SelectPortrait143730@@YAPBVImage@@PBVOpen2Template143730@@0@Z 0x00143730
const Image * __cdecl Open2SelectPortrait143730(
	const Open2Template143730 *portraitTemplate,
	const Open2Template143730 *objectTemplate)
{
	if (portraitTemplate == 0 || objectTemplate == 0)
		return 0;

	if (TheOpen2Logic143730->isInMultiplayerOrSkirmishGame())
	{
		static AsciiString overrideTemplate("GondorGandalf");
		if (portraitTemplate->m_name.compare(overrideTemplate) == 0 &&
			(objectTemplate->m_kindOfWord & OPEN2_MOUNTED_MASK) == 0)
		{
			static const Image *portraitOverride = 0;
			if (portraitOverride == 0)
				portraitOverride = TheOpen2Images143730->findImageByName(
					AsciiString("HPGandalfGrey"));
			if (portraitOverride != 0)
				return portraitOverride;
		}
	}

	return portraitTemplate->getSelectedPortraitImage();
}
