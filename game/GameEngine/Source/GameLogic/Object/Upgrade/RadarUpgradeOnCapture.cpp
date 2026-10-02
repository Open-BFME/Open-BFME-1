// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// RadarUpgrade::onCapture, retail RVA 0x002D7CD0.
// Identity and interface evidence: identity_evidence/002d7cd0-radar-capture.md.
#include "../object.h"
typedef bool Bool;

class Player
{
public:
    void removeRadar(Bool disableProof);
    void addRadar(Bool disableProof);
};

struct RadarUpgradeModuleData
{
    unsigned char m_unmodelled00[0x70];
    Bool m_isDisableProof;
};

class ObjectModule
{
public:
    virtual void objectModuleAnchor() = 0;
protected:
    const RadarUpgradeModuleData *m_moduleData;
    Object *m_object;
    unsigned int m_unmodelled0C;
};

class UpgradeMux
{
public:
    virtual Bool isAlreadyUpgraded() const = 0;
    virtual void upgradeMuxSlot1() = 0;
    virtual void upgradeMuxSlot2() = 0;
    virtual void upgradeMuxSlot3() = 0;
    virtual void upgradeMuxSlot4() = 0;
    virtual void upgradeMuxSlot5() = 0;
    virtual void upgradeMuxSlot6() = 0;
    virtual void upgradeMuxSlot7() = 0;
    virtual void setUpgradeExecuted(Bool value) = 0;
};

class RadarUpgrade : public ObjectModule, public UpgradeMux
{
public:
    virtual void onCapture(Player *oldOwner, Player *newOwner);
};

void RadarUpgrade::onCapture(Player *oldOwner, Player *newOwner)
{
    const RadarUpgradeModuleData *moduleData = m_moduleData;
    if (!isAlreadyUpgraded())
        return;
    if (m_object->m_disabledMask)
        return;
    if (oldOwner)
    {
        oldOwner->removeRadar(moduleData->m_isDisableProof);
        setUpgradeExecuted(false);
    }
    if (newOwner)
    {
        newOwner->addRadar(moduleData->m_isDisableProof);
        setUpgradeExecuted(true);
    }
}
