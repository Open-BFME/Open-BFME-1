// cl: /DNDEBUG /MD /EHsc
// Retail 0x00579790: copy slot zero's current skirmish name into the
// by-reference UnicodeString supplied by the Skirmish APT callback.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}
};

class GameSlot
{
public:
	UnicodeString getName() const;
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);
};

class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;

class BfmeAptScreenSkirmish
{
public:
	void getPlayerName(UnicodeString &dest);
};

// ?getPlayerName@BfmeAptScreenSkirmish@@QAEXAAVUnicodeString@@@Z
void BfmeAptScreenSkirmish::getPlayerName(UnicodeString &dest)
{
	if(TheSkirmishGameInfo)
		dest.set(reinterpret_cast<GameInfo *>(TheSkirmishGameInfo)->getSlot(0)->getName());
}
