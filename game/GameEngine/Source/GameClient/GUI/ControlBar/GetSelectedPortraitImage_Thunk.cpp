// cl: /DNDEBUG /MD /EHsc
// BFME chooses a different portrait for unmounted Gandalf in game modes that
// use the live object portrait.

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	RecorderModeType getMode();
};

// Retail's singleton at 0x012F6924 is ?TheMappedImageCollection@@3PAVImageCollection@@A
// (defined in game/GameEngine/Source/GameClient/System/Image.cpp), so the pointee
// must be spelled ImageCollection for this extern to resolve to it. No game header
// declares ImageCollection, so this TU declares the one member it calls.
class ImageCollection
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

class GameLogic;
// 0x012F0898 is retail's `GameLogic *TheGameLogic`; GameLogicPortraitShim is
// this TU's local view of the same global, so cast at the use.
extern GameLogic *TheGameLogic;
extern ImageCollection *TheMappedImageCollection;	///< retail 0x012F6924
// Retail loads 0x012ED62C for the playback checks, not TheGameLogic (0x012F0898).
// GameEngine::init names 0x012ED62C TheRecorder; this method's `this` is GameLogic
// and only the nested getMode/+0x2AC reads go through the recorder singleton.
extern RecorderClass *TheRecorder;	///< retail 0x012ED62C

bool GameLogicPortraitShim::isInMultiplayerOrSkirmishGame()
{
	if (m_gameType == 1)
		goto true_result;
	if (m_gameType == 5)
		goto true_result;
	if (m_gameType == 2)
		goto true_result;
	if (!TheRecorder)
		goto false_result;
	if (TheRecorder->getMode() != 1)
		goto false_result;
	if (((GameLogicPortraitShim *)TheRecorder)->m_recorderMode == 2)
		goto true_result;
	if (((GameLogicPortraitShim *)TheRecorder)->m_recorderMode == 1)
		goto true_result;
	if (((GameLogicPortraitShim *)TheRecorder)->m_recorderMode == 5)
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

	if (((GameLogicPortraitShim *)TheGameLogic)->isInMultiplayerOrSkirmishGame())
	{
		static AsciiString gandalfTemplate("GondorGandalf");
		if (portraitTemplate->m_name.StringBase<char>::compare(gandalfTemplate) == 0 &&
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
