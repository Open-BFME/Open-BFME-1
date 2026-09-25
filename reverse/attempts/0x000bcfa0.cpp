// ?d_000bcfa0@@YAXXZ
// partial score=0.83 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// INI field-parser callback at retail RVA 0x000BCFA0 (154 B). Its callees
// prove token-to-name-key conversion, upgrade lookup, and pointer-vector append.
// The owner remains address-derived because no caller or vtable proves its class.
//
// Retail reuses the incoming `store` argument slot for the plain-int exception
// object, then passes that same slot to _CxxThrowException with ThrowInfo 0x011E0004.

class INI
{
public:
    const char *getNextTokenOrNull(const char * = 0);
};

enum NameKeyType
{
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *);
};

class UpgradeTemplate;
class UpgradeCenter
{
public:
    const UpgradeTemplate *findUpgradeByKey(NameKeyType) const;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;

extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

struct Gen_t_000bc840_m4pod { int a[1]; };

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

// Address-derived model of the witnessed 12-byte vector prefix and helper ABI.
template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
    Type *m_start;
    Type *m_finish;
    Type *m_endOfStorage;

    void _M_insert_overflow(Type *position, const Type &value,
        const __false_type &tag, unsigned int n, bool atEnd);

    void push_back(const Type &value)
    {
        if (m_finish != m_endOfStorage)
        {
            if (m_finish != 0)
                *m_finish = value;
            ++m_finish;
        }
        else
        {
            // Retail aliases the overflow tag with the value's stack slot.
            const __false_type &tag =
                *reinterpret_cast<const __false_type *>(&value);
            _M_insert_overflow(m_finish, value, tag, 1, true);
        }
    }
};
}

class Rva000BCFA0
{
public:
    static void parseUpgradeKeyVector(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseUpgradeKeyVector@Rva000BCFA0@@SAXPAVINI@@PAX1PBX@Z
void Rva000BCFA0::parseUpgradeKeyVector(INI *ini, void *, void *store, const void *)
{
    if (!TheUpgradeCenter)
    {
        store = (void *)0xdead0001;
        _CxxThrowException(&store, (void *)0x011E0004);
    }


    const char *token = ini->getNextTokenOrNull();
    if (token != 0)
    {
        _STL::vector<Gen_t_000bc840_m4pod> *upgrades =
            (_STL::vector<Gen_t_000bc840_m4pod> *)store;
        do
        {
            store = (void *)TheUpgradeCenter->findUpgradeByKey(
                TheNameKeyGenerator->nameToKey(token));
            if (store != 0)
                upgrades->push_back(*(const Gen_t_000bc840_m4pod *)&store);
            token = ini->getNextTokenOrNull();
        } while (token != 0);
    }
}
