// cl: /DNDEBUG /MD /EHsc
// readable body of ?onObjectCreated@BoneFXDamage@@: game/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp
// Open-BFME5: lift BoneFXDamage::onObjectCreated __emit thunk to clean C++.
// Function-static name key from TheNameKeyGenerator (guard byte + static store;
// retail ILT 0x0003ADD7 -> NameKeyGenerator::nameToKey 0x0008FFC0, global VA 0x012ED600),
// a findModule call on the member at +0x08 (retail's ILT thunk 0x0002AE23),
// and a throw of a variadic exception object on failure.

// The call below resolves through retail's Object::findModule (the ILT thunk
// 0x0002AE23 in the body's disassembly), whose parameter is a NameKeyType.
enum NameKeyType;
class Module;

// Retail's Object::findModule is a protected member, so the mangled call name
// carries that access; only the friend below may call it here.
class Object
{
protected:
    Module *findModule(NameKeyType key) const;
    friend class BoneFXDamage;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
#include "../../ScriptEngine/game_logic_dispatch.h"

extern NameKeyGenerator *TheNameKeyGenerator;

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXDamage.h
class BoneFXDamage : public BFX_RootBase
{
protected:
    virtual void onObjectCreated();

private:
    Object *m_object;
};

// ?onObjectCreated@BoneFXDamage@@MAEXXZ
void BoneFXDamage::onObjectCreated()
{
    static NameKeyType key = TheNameKeyGenerator->nameToKey("BoneFXUpdate");
    if (!m_object->findModule(key)) {
        throw INIException(3, "BoneFXDamage requires BoneFXUpdate");
    }
}
