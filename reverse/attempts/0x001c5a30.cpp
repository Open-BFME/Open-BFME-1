// ?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z
// partial score=0.81 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail 0x001C5A30..0x001C5B3E, 270 bytes including final ret4.
#include <bitset>
class UpgradeMask { public:
 std::bitset<192> bits;
 UpgradeMask &operator|=(const UpgradeMask &rhs) { bits |= rhs.bits; return *this; }
 void _Unchecked_set(unsigned int bit) { bits._Unchecked_set(bit); }
};
class Player { public: char pad[0x8c]; UpgradeMask completed; UpgradeMask getCompletedUpgradeMask() const { return completed; } };
class Team { public: Player *getControllingPlayer() const; };
class UpgradeTemplate { public: char pad[0x20]; unsigned int bit; };
class UpgradeModuleInterface {
public:
 virtual bool isAlreadyUpgraded() const;
 virtual void slot04();
 virtual bool wouldUpgrade(const UpgradeMask &) const;
 virtual void slot0c();
 virtual bool isSubObjectsUpgrade();
};
class BfmeUpgradeProvider {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual UpgradeModuleInterface *getUpgrade();
};
struct BfmeBehaviorView { char prefix[12]; BfmeUpgradeProvider provider; };
class Object {
public:
 bool affectedByUpgrade(const UpgradeTemplate *) const;
 char pad00[0x1f0];
 BfmeBehaviorView **behaviors;
 char pad1f4[0x30];
 UpgradeMask completed;
 Team *team;
};
bool Object::affectedByUpgrade(const UpgradeTemplate *upgradeT) const
{
 Player *player = team ? team->getControllingPlayer() : 0;
 if (!player) return false;
 UpgradeMask mask = player->completed;
 mask |= completed;
 mask._Unchecked_set(upgradeT->bit);
 for (BfmeBehaviorView **module=behaviors; *module; ++module) {
  UpgradeModuleInterface *upgrade=(*module)->provider.getUpgrade();
  if (upgrade && upgrade->wouldUpgrade(mask) && !upgrade->isSubObjectsUpgrade())
   return true;
 }
 return false;
}
