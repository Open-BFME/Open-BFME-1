// cl: /DNDEBUG /MD /EHsc
#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : "";
	}

private:
	void *m_data;
};

class WeaponTemplate;
enum NameKeyType { INVALID_NAME_KEY = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
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
	if (_stricmp(name.str(), "None") == 0) {
		return 0;
	}
	return findWeaponTemplatePrivate(TheNameKeyGenerator->nameToKey(name.str()));
}
