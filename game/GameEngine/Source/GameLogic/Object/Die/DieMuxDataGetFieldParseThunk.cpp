// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?getFieldParse@DieMuxData@@: game/GameEngine/Source/GameLogic/Object/Die/DieModule.cpp

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
