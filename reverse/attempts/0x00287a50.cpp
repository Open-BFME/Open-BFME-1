// ?d_00287a50@@YAXXZ
// partial score=0.9 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// readable body of ?onObjectCreated@BoneFXUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// Open-BFME5: TWIN lane. 0x00287A50 is a byte-twin (relocations masked) of
// BoneFXDamage::onObjectCreated (retail 0x00287A30-adjacent,
// Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage_onObjectCreated_Thunk.cpp)
// with the roles swapped: the pool name literal is "BoneFXDamage" (not
// "BoneFXUpdate") and the exception message is "BoneFXUpdate requires
// BoneFXDamage" (retail .rdata, read directly), matching the complementary
// DEBUG_CRASH string already in the ZH reference
// (GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp:105),
// whose real body has since been rewritten in BFME to the same
// MemoryPoolFactory::findMemoryPool + BFX_Member::bind + throw INIException
// shape as its BoneFXDamage sibling, member at the same +0x08 offset.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdate : public BFX_RootBase
{
protected:
    virtual void onObjectCreated();

private:
    BFX_Member *m_member;
};

// ?onObjectCreated@BoneFXUpdate@@MAEXXZ
void BoneFXUpdate::onObjectCreated()
{
    static MemoryPool *pool = TheMemoryPoolFactory->findMemoryPool("BoneFXDamage");
    if (!m_member->bind(pool)) {
        throw INIException(3, "BoneFXUpdate requires BoneFXDamage");
    }
}

