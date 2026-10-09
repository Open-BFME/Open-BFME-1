// ?rva00743F80@W3DView@@UAEXXZ
// cl: /I. /DNDEBUG /DWIN32 /MD /EHsc
// stlport
#include "game/Libraries/Include/Lib/Coord3D.h"
#define BFME_HAVE_COORD3D
// ?getPosition@Thing@@QBEPBUCoord3D@@XZ absent-from-retail
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#undef THING_TU_MEMBERS

class BfmeGameLogicPause { public: bool isGamePaused(); };
#include "game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;
void __fastcall normAngle(float &angle);

class Display { public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual unsigned int getWidth();
    virtual unsigned int getHeight();
};
extern Display *TheDisplay;
class Mouse;
extern Mouse *TheMouse;
struct Rva00743F80MouseFields {
    char padding0000[0x4d10];
    int x;
    int y;
};
struct Rva012F9E28Fields { char padding0000[0xb0]; float valueB0; };
extern Rva012F9E28Fields *g_Va012F9E28;
extern bool g_Va012BB218;
extern bool g_bfmeFlagEC;
extern float BfmeCameraGlobal12F9DBC;
extern float g_Va012BB1D8;
extern float g_Va012BB1DC;
extern float g_Va012BB1E0;
extern float g_Va012BB1E4;
extern float g_Va012BB1E8;
extern float g_Va012BB1F8;
extern float g_Va012BB1FC;
extern float g_Va012BB200;
extern float g_Va012BB204;
extern float g_Va012F9DE0;
extern float g_Va012F9DDC;

class W3DView { public:
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
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void rva0073D880SetInt23BC(int);
    virtual void slot028();
    virtual void slot029();
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
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual unsigned char rva00746080Gate();
    virtual void slot115();
    virtual int rva0045BF80ObjectID();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142();
    virtual void slot143();
    virtual void slot144();
    virtual void slot145();
    virtual void slot146();
    virtual void slot147();
    virtual void slot148();
    virtual void rva00743F80();
private:
    void setCameraTransform();
    char padding0004[0xc-4];
    Coord3D m_pos;
    char padding0018[0x28-0x18];
    float m_angle;
    char padding002c[0x70-0x2c];
    float m_float0070;
    char padding0074[0x1dc-0x74];
    bool m_doingMoveCameraOnWaypointPath;
    char padding01dd[0x27d-0x1dd];
    bool m_doingScriptedCameraLock;
    char padding027e[0x2354-0x27e];
    int m_int2354;
    char padding2358[0x2490-0x2358];
    int m_int2490;
};

// Evidence: targets/game/reverse/identity_evidence/00743f80-camera-callback.md
// ?rva00743F80@W3DView@@UAEXXZ
void W3DView::rva00743F80()
{
    if (rva00746080Gate() && !reinterpret_cast<BfmeGameLogicPause *>(TheGameLogic)->isGamePaused()) {
        // Reuse the coordinate storage when the tracked object replaces the cursor values.
        Coord3D position;
        if (!g_Va012BB218) {
            if (!g_bfmeFlagEC) {
                float horizontalEdge = float(TheDisplay->getWidth()) * g_Va012BB1D8;
                position.x = float(reinterpret_cast<Rva00743F80MouseFields *>(TheMouse)->x);
                float horizontalDistance = position.x - horizontalEdge;
                if (horizontalDistance > 0.0f) {
                    horizontalDistance = position.x - (float(TheDisplay->getWidth()) - horizontalEdge);
                    if (horizontalDistance < 0.0f) horizontalDistance = 0.0f;
                }
                g_Va012F9DE0 -= horizontalDistance * g_Va012BB1DC;
                g_Va012F9DE0 -= g_Va012F9DE0 * g_Va012BB1E0;
                if (g_Va012F9DE0 != 0.0f) {
                    if (!g_bfmeFlagEC) {
                        float angleDelta = BfmeCameraGlobal12F9DBC;
                        BfmeCameraGlobal12F9DBC = 0.0f;
                        m_angle += angleDelta;
                    }
                    m_angle += g_Va012F9DE0;
                    normAngle(m_angle);
                }
            }
            {
                float topEdge = float(TheDisplay->getHeight()) * g_Va012BB1E4;
                float bottomEdge = float(TheDisplay->getHeight()) * g_Va012BB1E8;
                position.y = float(reinterpret_cast<Rva00743F80MouseFields *>(TheMouse)->y);
                float verticalDistance = position.y - topEdge;
                if (verticalDistance > 0.0f) {
                    verticalDistance = position.y - (float(TheDisplay->getHeight()) - bottomEdge);
                    if (verticalDistance < 0.0f) goto dampVertical;
                }
                if ((verticalDistance > 0.0f && m_float0070 < g_Va012BB1F8) ||
                (verticalDistance < 0.0f && m_float0070 > g_Va012BB1FC)) {
                    g_Va012F9DDC += g_Va012BB200 * verticalDistance;
                }
                dampVertical:
                g_Va012F9DDC -= g_Va012BB204 * g_Va012F9DDC;
                if (g_Va012F9DDC != 0.0f) m_float0070 += g_Va012F9DDC;
            }
        }
        Object *object = TheGameLogic->findObjectByID(rva0045BF80ObjectID());
        if (object && !g_bfmeFlagEC) {
            position.x = object->getPosition()->x;
            position.y = object->getPosition()->y;
            position.z = 0.0f;
            m_pos = position;
            m_doingMoveCameraOnWaypointPath = false;
            m_int2354 = 0;
            rva0073D880SetInt23BC(0);
            m_doingScriptedCameraLock = false;
            setCameraTransform();
        }
        if (g_Va012F9E28) {
            g_Va012F9E28->valueB0 = 1.0f;
            g_Va012F9E28 = 0;
        }
        TheDisplay->getWidth();
        TheDisplay->getHeight();
    } else if (m_int2490 == 4) {
        setCameraTransform();
    }
}
