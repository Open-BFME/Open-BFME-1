// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The retail initializer creates the three built-in veterancy upgrades.

#include "ascii_string.h"

#include "../../../Include/Common/Enums/VeterancyLevel.h"







class UpgradeTemplate
{
public:
	void friend_makeVeterancyUpgrade(VeterancyLevel level);
};

class UpgradeCenter
{
public:
	UpgradeTemplate *newUpgrade(const AsciiString &name);
	virtual void init();
};

// ?init@UpgradeCenter@@UAEXXZ
void UpgradeCenter::init()
{
	UpgradeTemplate *up;

	up = newUpgrade("");
	up->friend_makeVeterancyUpgrade(LEVEL_VETERAN);

	up = newUpgrade("");
	up->friend_makeVeterancyUpgrade(LEVEL_ELITE);

	up = newUpgrade("");
	up->friend_makeVeterancyUpgrade(LEVEL_HEROIC);
}
