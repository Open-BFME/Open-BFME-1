// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?duplicate@Condition@@QBEPAV1@XZ: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
    Condition *duplicate() const;
};

class ConditionDuplicateShim
{
public:
    Condition *run() const;
};

Condition *Condition::duplicate() const
{
    return ((const ConditionDuplicateShim *)this)->run();
}
