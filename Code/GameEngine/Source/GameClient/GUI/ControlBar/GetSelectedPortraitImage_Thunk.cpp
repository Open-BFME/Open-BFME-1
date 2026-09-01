// cl: /DNDEBUG /MD /EHsc
// BFME chooses a different portrait for unmounted Gandalf in game modes that
// use the live object portrait.

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Image;

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();

	char m_beforeGameType[0x10c];
	int m_gameType;
	char m_beforeRecorderMode[0x19c];
	int m_recorderMode;
};

enum RecorderModeType
{
	RECORDER_MODE_NONE = 0
};

class RecorderClass
{
public:
	RecorderModeType getMode();
};

class MappedImageCollectionPortraitShim
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class ThingTemplatePortraitShim
{
public:
	unsigned char m_beforeName[0x20];
	AsciiString m_name;
	unsigned char m_beforeKindOf[0x128 - 0x24];
	unsigned int m_kindOfWord;

	const Image *getSelectedPortraitImage() const;
};

extern GameLogicPortraitShim *TheGameLogic;
extern MappedImageCollectionPortraitShim *TheMappedImageCollection;

bool GameLogicPortraitShim::isInMultiplayerOrSkirmishGame()
{
	if (m_gameType == 1)
		goto true_result;
	if (m_gameType == 5)
		goto true_result;
	if (m_gameType == 2)
		goto true_result;
	if (!TheGameLogic)
		goto false_result;
	if (((RecorderClass *)TheGameLogic)->getMode() != 1)
		goto false_result;
	if (TheGameLogic->m_recorderMode == 2)
		goto true_result;
	if (TheGameLogic->m_recorderMode == 1)
		goto true_result;
	if (TheGameLogic->m_recorderMode == 5)
		goto true_result;
	goto false_result;

true_result:
	return true;
false_result:
	return false;
}

// The relevant BFME template flags are in the word at +0x128.  Bit 17
// distinguishes the alternate GondorGandalf form at this call site.
static const unsigned int GANDALF_MOUNTED_MASK = 0x00020000;

// ?_bfme_getSelectedPortraitImage@@YAPBVImage@@PBVThingTemplate@@0@Z
const Image * __cdecl _bfme_getSelectedPortraitImage(
	const ThingTemplatePortraitShim *portraitTemplate,
	const ThingTemplatePortraitShim *objectTemplate)
{
	if (portraitTemplate == 0 || objectTemplate == 0)
		return 0;

	if (TheGameLogic->isInMultiplayerOrSkirmishGame())
	{
		static AsciiString gandalfTemplate("GondorGandalf");
		if (portraitTemplate->m_name.compare(gandalfTemplate) == 0 &&
			(objectTemplate->m_kindOfWord & GANDALF_MOUNTED_MASK) == 0)
		{
			static const Image *gandalfTheGrey = 0;
			if (gandalfTheGrey == 0)
				gandalfTheGrey = TheMappedImageCollection->findImageByName(
					AsciiString("HIGandalTheGrey"));
			if (gandalfTheGrey != 0)
				return gandalfTheGrey;
		}
	}

	return portraitTemplate->getSelectedPortraitImage();
}
