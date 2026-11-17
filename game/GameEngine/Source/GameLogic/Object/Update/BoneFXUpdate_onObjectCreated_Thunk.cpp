// cl: /DNDEBUG /MD /EHsc
// readable body of ?onObjectCreated@BoneFXUpdate@@: game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// Open-BFME5: TWIN lane. 0x00287A50 is a byte-twin (relocations masked) of
// BoneFXDamage::onObjectCreated (retail 0x00287A30-adjacent,
// game/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage_onObjectCreated_Thunk.cpp)
// with the roles swapped: the pool name literal is "BoneFXDamage" (not
// "BoneFXUpdate") and the exception message is "BoneFXUpdate requires
// BoneFXDamage" (retail .rdata, read directly), matching the complementary
// DEBUG_CRASH string already in the ZH reference
// (GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp:105),
// whose real body has since been rewritten in BFME to the same
// NameKeyGenerator::nameToKey + Object::findModule + throw INIException
// shape as its BoneFXDamage sibling, member at the same +0x08 offset.

enum NameKeyType;
class Module;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
// Retail ILT 0x0003ADD7 -> NameKeyGenerator::nameToKey 0x0008FFC0; global VA 0x012ED600.
#include "../../ScriptEngine/game_logic_dispatch.h"

extern NameKeyGenerator *TheNameKeyGenerator;

// Retail ILT 0x0002AE23 -> Object::findModule 0x001BEE60 (protected member).
class Object
{
protected:
    Module *findModule(NameKeyType key) const;
    friend class BoneFXUpdate;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
    INIException(int code, const char *message, ...);
    INIException(const INIException &that);
    ~INIException();

private:
    int m_code;
    int m_line;
};

class BFX_RootBase
{
public:
    virtual void onObjectCreated();

private:
    unsigned int m_f4;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdate : public BFX_RootBase
{
protected:
    virtual void onObjectCreated();

private:
    Object *m_object;
};

// ?onObjectCreated@BoneFXUpdate@@MAEXXZ
void BoneFXUpdate::onObjectCreated()
{
    static NameKeyType key = TheNameKeyGenerator->nameToKey("BoneFXDamage");
    if (!m_object->findModule(key)) {
        throw INIException(3, "BoneFXUpdate requires BoneFXDamage");
    }
}

