// cl: /DNDEBUG /MD /EHsc
// readable body of ?onObjectCreated@BoneFXDamage@@: Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp
// Open-BFME5: lift BoneFXDamage::onObjectCreated __emit thunk to clean C++.
// Function-static MemoryPool from the factory (guard byte + static store),
// a bind call on the member at +0x08, and a throw of a variadic exception
// object on failure.

class MemoryPool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolFactory
{
public:
    MemoryPool *findMemoryPool(const char *name);
};

extern MemoryPoolFactory *TheMemoryPoolFactory;

class BFX_Member
{
public:
    int bind(MemoryPool *pool);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
    INIException(int code, const char *message, ...);
    INIException(const INIException &that);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXDamage.h
class BoneFXDamage : public BFX_RootBase
{
protected:
    virtual void onObjectCreated();

private:
    BFX_Member *m_member;
};

// ?onObjectCreated@BoneFXDamage@@MAEXXZ
void BoneFXDamage::onObjectCreated()
{
    static MemoryPool *pool = TheMemoryPoolFactory->findMemoryPool("BoneFXUpdate");
    if (!m_member->bind(pool)) {
        throw INIException(3, "BoneFXDamage requires BoneFXUpdate");
    }
}
