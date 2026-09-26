// ?rva00579C30LevelText@BfmeAptScreenSkirmish@@QAEXVAsciiString@@00@Z
// Retail 0x00579C30/433B; owner and three-argument ABI are proven by
// BfmeAptScreenSkirmish::levelBar at 0x0057C340 (see identity evidence).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../../../../inputs/reference/shims/stringinline/StringInline.h"

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

class SkirmishBattleHonors
{
public:
	int getRank(AsciiString name) const;
	int getPointsToNextRank(AsciiString name, int rank) const;
};

extern GameTextInterface *TheGameText;
extern WindowManager *g_theWindowManager;
extern void j_00027093();
extern void j_0002639b();

class BfmeAptScreenSkirmish
{
public:
	void rva00579C30LevelText(AsciiString sideName, AsciiString currentName,
		AsciiString nextName);
private:
	char m_beforeHonors[0x3c4];
	SkirmishBattleHonors m_honorsAt3C4;
};

void BfmeAptScreenSkirmish::rva00579C30LevelText(AsciiString sideName,
	AsciiString currentName, AsciiString nextName)
{
	typedef int (SkirmishBattleHonors::*GetRank)(AsciiString) const;
	union { void (*raw)(); GetRank typed; } rankCall;
	rankCall.raw = j_00027093;
	typedef int (SkirmishBattleHonors::*GetNext)(AsciiString, int) const;
	union { void (*raw)(); GetNext typed; } nextCall;
	nextCall.raw = j_0002639b;

	UnicodeString text;
	int rank = (m_honorsAt3C4.*rankCall.typed)(sideName);
	text.format(TheGameText->fetch("APT:CurrentLevelNumFormat"), rank);
	{
		UnicodeString currentValue(text);
		g_theWindowManager->bfme_setAptText(currentName, currentValue);
	}

	int points = (m_honorsAt3C4.*nextCall.typed)(sideName, rank);
	if (points == 0)
		text.format(TheGameText->fetch("APT:NoNextLevel"));
	else if (points == 1)
		text.format(TheGameText->fetch("APT:NextLevelNumFormatForOnePoint"), points);
	else
		text.format(TheGameText->fetch("APT:NextLevelNumFormat"), points);
	{
		UnicodeString nextValue(text);
		g_theWindowManager->bfme_setAptText(nextName, nextValue);
	}
}
