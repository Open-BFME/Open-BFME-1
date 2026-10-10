// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/turretai /Iinputs/reference/shims/aiupdatelayout /Iinputs/reference/shims/aicommandoutofline /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotorpreferredheight /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "GameLogic/TerrainLogic.h"

class Rva003FD790
{
public:
    Rva003FD790();
    int m_00, m_04, m_08;
    char m_0C, m_0D;
    int m_10, m_14, m_18, m_1C, m_20;
};
struct PathNode0026F460
{
    char m_beforeCost[0x20];
    int m_costSoFar;
};
struct Path0026F460Fields
{
    void *m_unknown00;
    void *m_path;
    PathNode0026F460 *m_pathTail;
    bool m_isOptimized;
};
class PathAppendNodeILT
{
public:
    void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};
class BFMEObjectLayerQuery
{
public:
    int getLayer() const;
};
struct Object0026F460Fields
{
    char m_beforePosition[0x38];
    Coord3D m_position;
};
class Rva0026F460
{
public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot00A();
    virtual void slot00B();
    virtual void slot00C();
    virtual void slot00D();
    virtual void slot00E();
    virtual void slot00F();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot01A();
    virtual void slot01B();
    virtual void slot01C();
    virtual void slot01D();
    virtual void slot01E();
    virtual void slot01F();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot02A();
    virtual void slot02B();
    virtual void slot02C();
    virtual void slot02D();
    virtual void slot02E();
    virtual void slot02F();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot03A();
    virtual void slot03B();
    virtual void slot03C();
    virtual void slot03D();
    virtual void slot03E();
    virtual void slot03F();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot04A();
    virtual void slot04B();
    virtual void slot04C();
    virtual void slot04D();
    virtual void slot04E();
    virtual void slot04F();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot05A();
    virtual void slot05B();
    virtual void slot05C();
    virtual void slot05D();
    virtual void slot05E();
    virtual void slot05F();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot06A();
    virtual void slot06B();
    virtual void slot06C();
    virtual void slot06D();
    virtual void slot06E();
    virtual void slot06F();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot1DC(const Coord3D *position);
    void method(const Coord3D *position, int cost);
    int m_unknown04;
    Object *m_object;
    char m_beforePath[0x134];
    Rva003FD790 *m_path;
};

// ?method@Rva0026F460@@QAEXPBUCoord3D@@H@Z
void Rva0026F460::method(const Coord3D *position, int cost)
{
    slot1DC(position);
    if (!m_path)
    {
        m_path = new Rva003FD790;
        Object *object = m_object;
        int layer = reinterpret_cast<BFMEObjectLayerQuery *>(object)->getLayer();
        reinterpret_cast<PathAppendNodeILT *>(m_path)->appendNode(&reinterpret_cast<Object0026F460Fields *>(object)->m_position, static_cast<PathfindLayerEnum>(layer));
        reinterpret_cast<Path0026F460Fields *>(m_path)->m_isOptimized = true;
    }
    reinterpret_cast<Path0026F460Fields *>(m_path)->m_pathTail->m_costSoFar = cost;
    Object *object = m_object;
    TerrainLogic *terrain = TheTerrainLogic;
    PathfindLayerEnum layer = terrain->getLayerForDestination(object, position);
    reinterpret_cast<PathAppendNodeILT *>(m_path)->appendNode(position, layer);
    reinterpret_cast<Path0026F460Fields *>(m_path)->m_pathTail->m_costSoFar = cost;
}
