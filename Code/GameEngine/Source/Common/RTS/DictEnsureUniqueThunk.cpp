// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?ensureUnique@Dict@@: Code/GameEngine/Source/Common/Dict.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
    struct DictPair;
    DictPair *ensureUnique(int, bool, DictPair *);
};

class DictEnsureUniqueShim
{
public:
    struct DictPair;
    DictPair *run(int count, bool flag, DictPair *pair);
};

Dict::DictPair *Dict::ensureUnique(int count, bool flag, DictPair *pair)
{
    return (Dict::DictPair *)((DictEnsureUniqueShim *)this)->run(count, flag, (DictEnsureUniqueShim::DictPair *)pair);
}
