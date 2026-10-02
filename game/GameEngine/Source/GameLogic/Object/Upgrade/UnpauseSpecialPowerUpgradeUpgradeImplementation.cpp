// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
// UnpauseSpecialPowerUpgrade, UpgradeMux table 0x010CE350 (stored at +0x10 by the registered constructor
// 0x002D9760):
//   slot 9 -> 0x002D9890 UnpauseSpecialPowerUpgrade::upgradeImplementation (ILT 0x000437B6, sole image ref)
//   slot 7 -> 0x002D9910 UnpauseSpecialPowerUpgrade::removeUpgrade (ILT 0x000145D8, sole image ref); slot 7 is
//            EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), undoing slot 9.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Slot 9 is the upgradeImplementation call in UpgradeMux::attemptUpgrade
// (0x002D9AD0). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

class Rva002D9910Result
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void *getValue();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24(void *value);
    virtual void apply(int value);
};

class Rva002D9910Nested
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual Rva002D9910Result *getResult();
};

class Rva002D9910Element
{
private:
    char m_pad00[0x0C];

public:
    Rva002D9910Nested m_nested;
};

class Rva002D9910Owner
{
private:
    char m_pad00[0x1F0];

public:
    Rva002D9910Element **m_elements;
};

class Rva002D9910State
{
private:
    char m_pad00[0x70];

public:
    void *m_compare;
    unsigned char m_flag;
};

class UnpauseSpecialPowerUpgrade
{
protected:
	virtual void upgradeImplementation();
	virtual void removeUpgrade();
};

struct Rva002D9890Global
{
    char m_pad00[0x3C];
    void *m_value;
};

// The game-logic singleton is declared with the retail class type so this TU
// references the canonical global. Rva002D9890Global is only the local view
// needed for the field read below.
class GameLogic;
extern GameLogic *TheGameLogic;

void UnpauseSpecialPowerUpgrade::removeUpgrade()
{
    Rva002D9910Owner *owner = *(Rva002D9910Owner **)((char *)this - 8);
    for (Rva002D9910Element **it = owner->m_elements; *it != 0; ++it)
    {
        Rva002D9910Result *result = (*it)->m_nested.getResult();
        if (result != 0)
        {
            Rva002D9910State *state = *(Rva002D9910State **)((char *)this - 0x0C);
            if (result->getValue() == state->m_compare)
                result->apply(1);
        }
    }
}

void UnpauseSpecialPowerUpgrade::upgradeImplementation()
{
    Rva002D9910Owner *owner = *(Rva002D9910Owner **)((char *)this - 8);
    for (Rva002D9910Element **it = owner->m_elements; *it != 0; ++it)
    {
        Rva002D9910Result *result = (*it)->m_nested.getResult();
        if (result != 0)
        {
            Rva002D9910State *state = *(Rva002D9910State **)((char *)this - 0x0C);
            if (result->getValue() == state->m_compare)
            {
                result->apply(0);
                if (!(*(Rva002D9910State **)((char *)this - 0x0C))->m_flag)
                    result->slot24(((Rva002D9890Global *)TheGameLogic)->m_value);
            }
        }
    }
}
