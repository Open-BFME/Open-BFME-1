// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <string.h>

#include "ascii_string.h"

class WeaponTemplate;
#include "../../../Include/Common/NameKeyType.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(AsciiString) const;

protected:
	WeaponTemplate *findWeaponTemplatePrivate(NameKeyType) const;
};

// ?findWeaponTemplate@WeaponStore@@QBEPBVWeaponTemplate@@VAsciiString@@@Z
const WeaponTemplate *WeaponStore::findWeaponTemplate(AsciiString name) const
{
	if (_strcmpi(name.str(), "None") == 0) {
		return 0;
	}
	return findWeaponTemplatePrivate(TheNameKeyGenerator->nameToKey(name.str()));
}
