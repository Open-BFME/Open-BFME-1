// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?duplicate@Condition@@QBEPAV1@XZ: game/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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
