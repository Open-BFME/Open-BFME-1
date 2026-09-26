// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/Scripts.h"

// BFME's scalar Parameter fields precede the Zero Hour fields by four bytes.
class Rva003239A0ParameterView {
public:
    char m_beforeInt[8];
    int m_int;
    float m_real;
    AsciiString m_string;
    char m_beforeObjectID[0x10];
    int m_objectID;
};

class Rva003239A0Object {
public:
    char m_beforePosition[0x38];
    Coord3D m_position;
};

// BFME ScriptEngine::resolveUnit occupies vtable slot 26 (+0x68).
class Rva003239A0ScriptEngineView {
public:
    virtual void slot00() = 0; virtual void slot01() = 0;
    virtual void slot02() = 0; virtual void slot03() = 0;
    virtual void slot04() = 0; virtual void slot05() = 0;
    virtual void slot06() = 0; virtual void slot07() = 0;
    virtual void slot08() = 0; virtual void slot09() = 0;
    virtual void slot10() = 0; virtual void slot11() = 0;
    virtual void slot12() = 0; virtual void slot13() = 0;
    virtual void slot14() = 0; virtual void slot15() = 0;
    virtual void slot16() = 0; virtual void slot17() = 0;
    virtual void slot18() = 0; virtual void slot19() = 0;
    virtual void slot20() = 0; virtual void slot21() = 0;
    virtual void slot22() = 0; virtual void slot23() = 0;
    virtual void slot24() = 0; virtual void slot25() = 0;
    virtual Rva003239A0Object *resolveUnit(Rva003239A0ParameterView *) = 0;
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class ScriptConditions {
protected:
    bool evaluateRva003239A0ObjectDistance(Condition *);
};

// Condition template 113 is DISTANCE_BETWEEN_OBJ in the retail template table.
bool ScriptConditions::evaluateRva003239A0ObjectDistance(Condition *condition)
{
    Rva003239A0Object *first = ((Rva003239A0ScriptEngineView *)TheScriptEngine)->resolveUnit(
        (Rva003239A0ParameterView *)condition->getParameter(0));
    Rva003239A0Object *second = ((Rva003239A0ScriptEngineView *)TheScriptEngine)->resolveUnit(
        (Rva003239A0ParameterView *)condition->getParameter(1));
    if (first && second) {
        Coord3D delta;
        delta.set(&first->m_position);
        delta.sub(&second->m_position);
        float distance = delta.length();
        Parameter *value = condition->getParameter(3);
        float threshold = ((Rva003239A0ParameterView *)value)->m_real;
        Parameter *comparison = condition->getParameter(2);
        switch (((Rva003239A0ParameterView *)comparison)->m_int) {
        case 0: if (distance < threshold) return true; break;
        case 1: if (distance <= threshold) return true; break;
        case 2: if (distance == threshold) return true; break;
        case 3: if (distance >= threshold) return true; break;
        case 4: if (distance > threshold) return true; break;
        case 5: if (distance != threshold) return true; break;
        }
    }
    return false;
}
