// ?update@RenderObjectParticleUpdateModule@FXParticleSystem@@UAEXPAURva006E0580State@2@@Z
// partial score=0.35 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Partial reconstruction of retail 0x006E0580.  The caller at 0x00B421B5
// invokes this on its +0xB4 update module and passes a 0xD8-byte camera state.

#include "Common/AsciiString.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"
#include "W3DDevice/GameClient/camerashakesystem.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "WW3D2/Camera.h"

extern ScriptEngine *TheScriptEngine;

namespace FXParticleSystem {

struct Rva006E0580State {
    Matrix3D *transform;             // 00
    float distance;                 // 04
    Vector3 source;                 // 08
    Vector3 target;                 // 14
    Vector3 shakerAngles;           // 20
    float pad2C;
    float groundLevel;              // 30
    unsigned char pad34[8];
    float lookAngle;                // 3c
    float pitchAngle;               // 40
    float finalAngle;               // 44
    unsigned char pad48[4];
    Vector3 velocity;               // 4c
    Vector3 position;               // 58
    Vector3 direction;              // 64
    float accelerationX;            // 70
    float accelerationY;            // 74
    bool clampVelocity;             // 78
    unsigned char pad79[3];
    float minVelocityX;
    float minVelocityY;
    float maxVelocityX;
    float maxVelocityY;
    bool clampAngle;                // 8c
    unsigned char pad8D[3];
    Vector3 angleAxis;              // 90
    unsigned char pad9C[0x0c];
    bool flagA8;
    bool flagA9;
    bool cameraSlaved;              // aa
    unsigned char padAB;
    AsciiString slaveObjectName;    // ac
    AsciiString slaveBoneName;      // b0
    unsigned char padB4[0x1c];
    bool useRealZoom;               // d0
    unsigned char padD1;
    bool finalLookAt;               // d2
    unsigned char padD3;
    int updateMode;                 // d4
};

class RenderObjectParticleUpdateModule {
public:
    virtual void update(Rva006E0580State *state);
    void adjustTarget(Vector3 *source, Vector3 *target, Rva006E0580State *state);
};

void RenderObjectParticleUpdateModule::update(Rva006E0580State *state)
{
    state->velocity.X += state->accelerationX;
    state->velocity.Y += state->accelerationY;

    if (state->updateMode == 2) {
        Vector3 target(state->velocity.X, state->velocity.Y, 0.0f);
        Vector3 source(state->direction);
        state->transform->Make_Identity();
        state->transform->Look_At(source, target, state->lookAngle);
        return;
    }

    if (state->clampVelocity) {
        if (state->velocity.X < state->minVelocityX) state->velocity.X = state->minVelocityX;
        if (state->velocity.X > state->maxVelocityX) state->velocity.X = state->maxVelocityX;
        if (state->velocity.Y < state->minVelocityY) state->velocity.Y = state->minVelocityY;
        if (state->velocity.Y > state->maxVelocityY) state->velocity.Y = state->maxVelocityY;
    }

    if (state->clampAngle) {
        state->direction = state->angleAxis;
        if (state->groundLevel > 0.0f)
            state->pitchAngle = state->groundLevel;
    }

    Vector3 source = state->source;
    Vector3 target = state->target;
    source.X += state->position.X;
    source.Y += state->position.Y;
    source.Z += state->position.Z;
    target.X += state->position.X;
    target.Y += state->position.Y;
    target.Z += state->position.Z;

    state->source = source;
    state->target = target;
    state->distance = (source - target).Length();

    if (!state->useRealZoom)
        adjustTarget(&source, &target, state);

    if (state->direction.Length2() != 0.0f)
        target = state->direction;

    state->transform->Make_Identity();
    state->transform->Look_At(source, target, state->lookAngle);

    if (!state->useRealZoom) {
        CameraShakerSystem.Timestep(1.0f / 30.0f);
        CameraShakerSystem.Update_Camera_Shaker(source, &state->shakerAngles);
        state->transform->Rotate_X(state->shakerAngles.X);
        state->transform->Rotate_Y(state->shakerAngles.Y);
        state->transform->Rotate_Z(state->shakerAngles.Z);
    }

    if (state->cameraSlaved) {
        Object *obj = TheScriptEngine->getUnitNamed(state->slaveObjectName);
        if (obj != 0) {
            Drawable *draw = obj->getDrawable();
            if (draw != 0) {
                for (DrawModule **dm = draw->getDrawModules(); *dm; ++dm) {
                    const ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
                    if (di != 0) {
                        Matrix3D tm;
                        di->clientOnly_getRenderObjBoneTransform(state->slaveBoneName, &tm);
                        *state->transform = tm;
                        state->position = state->transform->Get_Translation();
                        break;
                    }
                }
            } else {
                state->cameraSlaved = false;
            }
        } else {
            state->cameraSlaved = false;
        }
    }

    state->transform->Rotate_Y(state->finalAngle);
    if (state->useRealZoom && state->finalLookAt) {
        Vector3 finalTarget = target;
        finalTarget.X += (source.X - target.X) / (state->groundLevel + 1.0f);
        finalTarget.Y += (source.Y - target.Y) / (state->groundLevel + 1.0f);
        state->transform->Look_At(source, finalTarget, 0.0f);
        state->source = source;
        state->target = finalTarget;
    }
}

} // namespace FXParticleSystem
