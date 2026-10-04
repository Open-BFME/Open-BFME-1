// cl: /DNDEBUG /MD /EHsc
// readable body of ?onObjectCreated@BoneFXDamage@@: game/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp
// Open-BFME5: lift BoneFXDamage::onObjectCreated __emit thunk to clean C++.
// Function-static MemoryPool from the factory (guard byte + static store),
// a findModule call on the member at +0x08 (retail's ILT thunk 0x0002AE23),
// and a throw of a variadic exception object on failure.

class MemoryPool;

// The static key and the call below resolve through retail's Object::findModule
// (the ILT thunk 0x0002AE23 in the body's disassembly), whose parameter is a
// NameKeyType, so the parameter type is only forward-declared here.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolFactory
{
public:
    MemoryPool *findMemoryPool(const char *name);
};

extern MemoryPoolFactory *TheMemoryPoolFactory;

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
    static MemoryPool *pool = TheMemoryPoolFactory->findMemoryPool("BoneFXUpdate");
    if (!m_object->findModule((NameKeyType)(size_t)pool)) {
        throw INIException(3, "BoneFXDamage requires BoneFXUpdate");
    }
}
