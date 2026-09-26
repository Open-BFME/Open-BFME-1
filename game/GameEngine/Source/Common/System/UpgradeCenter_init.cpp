// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The retail initializer creates the three built-in veterancy upgrades.

#include "ascii_string.h"

enum VeterancyLevel
{
	LEVEL_REGULAR = 0,
	LEVEL_VETERAN = 1,
	LEVEL_ELITE = 2,
	LEVEL_HEROIC = 3
};

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

	up = newUpgrade((const char *)0x0107301C);
	up->friend_makeVeterancyUpgrade(LEVEL_VETERAN);

	up = newUpgrade((const char *)0x0107301C);
	up->friend_makeVeterancyUpgrade(LEVEL_ELITE);

	up = newUpgrade((const char *)0x0107301C);
	up->friend_makeVeterancyUpgrade(LEVEL_HEROIC);
}
