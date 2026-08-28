// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?getFieldParse@DieMuxData@@: Code/GameEngine/Source/GameLogic/Object/Die/DieModule.cpp

struct FieldParse;

class DieMuxData
{
public:
    static const FieldParse *getFieldParse();
};

class DieMuxDataGetFieldParseShim
{
public:
    static const FieldParse *run();
};

const FieldParse *DieMuxData::getFieldParse()
{
    return DieMuxDataGetFieldParseShim::run();
}
