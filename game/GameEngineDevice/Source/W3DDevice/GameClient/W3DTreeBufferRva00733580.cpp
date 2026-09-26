// Full retail 0x00733580..0x00733A37, 1207 bytes including all RET 4 tails.
// Ported from ZH W3DTreeBuffer::updateTopplingTree with the BFME record/type
// layouts witnessed by the surrounding matched tree-buffer bodies. Keep an
// address-derived owner rather than asserting the upstream class ABI.
// Matrix operations use the native WWMath header. Coord3D::set models the
// native three-argument helper and avoids an extra intermediate stack copy.
// BFME adds the changed flag, scaled sink countdown, and sinking byte.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims
#include "matrix3d.h"
#include <math.h>
struct Coord3D {
    float x,y,z;
    void set(float px,float py,float pz) { x=px; y=py; z=pz; }
};
enum ObjectShroudStatus { RvaShroud0, RvaShroud1, RvaShroud2, RvaShroudFogged };
class PartitionManager { public:
    ObjectShroudStatus getPropShroudStatusForPlayer(int,const Coord3D *) const;
};
extern PartitionManager *TheShroudManager;
class Player { public: char pad00[0x24]; int index; };
class PlayerList { public: char pad00[0xc]; Player *localPlayer; };
extern PlayerList *ThePlayerList;
class FXList { public:
    static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *);
};
struct Rva00733580TypeData {
    char pad00[0x24];
    FXList *bounceFX;
    char pad28[0xc];
    float bounceVelocityPercent;
    float minimumSpeed;
    unsigned char killWhenToppled;
    unsigned int sinkFrames;
};
struct Rva00733580Type {
    char pad00[0x20]; Rva00733580TypeData *data; char pad24[0x38];
};
struct Rva00733580Record {
    Vector3 location;
    char pad0c[0x34];
    int type;
    char pad44[0x28];
    float angularVelocity,angularAcceleration;
    Coord3D toppleDirection;
    int toppleState;
    float angularAccumulation;
    unsigned char field88;
    unsigned int options;
    Matrix3D matrix;
    int sinkFramesLeft;
    unsigned char sinking;
    char padc5[0x23];
};
class Rva00733580Owner {
public:
    void update(Rva00733580Record *tree);
    char pad000000[0x2a7cbc];
    Rva00733580Type types[64];
    char pad2a93bc[0x53c];
    float sinkScale;
    unsigned char changed;
};
static const float Rva00733580AngularLimit = 1.5217089653015137f;
void Rva00733580Owner::update(Rva00733580Record *tree)
{
    if (tree->toppleState == 0 || tree->toppleState == 3) return;
    const Rva00733580TypeData *data = types[tree->type].data;
    int playerIndex = ThePlayerList ? ThePlayerList->localPlayer->index : 0;
    Coord3D position;
    position.x = tree->location.X;
    position.y = tree->location.Y;
    position.z = tree->location.Z;
    ObjectShroudStatus status = TheShroudManager->getPropShroudStatusForPlayer(playerIndex,&position);
    if (status == RvaShroudFogged) {
        tree->toppleState = 2;
        return;
    } else if (tree->toppleState == 2) {
        tree->angularVelocity = 0;
        tree->toppleState = 3;
        tree->matrix.In_Place_Pre_Rotate_X(-Rva00733580AngularLimit * tree->toppleDirection.y);
        tree->matrix.In_Place_Pre_Rotate_Y(Rva00733580AngularLimit * tree->toppleDirection.x);
        if (data->killWhenToppled) {
            tree->sinkFramesLeft = 0;
            tree->sinking = 1;
        }
        return;
    }
    float velocity = tree->angularVelocity;
    if (tree->angularAccumulation + velocity > Rva00733580AngularLimit)
        velocity = Rva00733580AngularLimit - tree->angularAccumulation;
    tree->matrix.In_Place_Pre_Rotate_X(-velocity * tree->toppleDirection.y);
    tree->matrix.In_Place_Pre_Rotate_Y(velocity * tree->toppleDirection.x);
    tree->angularAccumulation += velocity;
    if (tree->angularAccumulation >= Rva00733580AngularLimit && tree->angularVelocity > 0) {
        tree->angularVelocity *= -data->bounceVelocityPercent;
        if ((tree->options & 1) || fabs(tree->angularVelocity) < 0.01f) {
            tree->angularVelocity = 0;
            tree->toppleState = 3;
            changed = 1;
            if (data->killWhenToppled) {
                tree->sinkFramesLeft = (int)((float)data->sinkFrames * sinkScale);
                tree->sinking = 1;
            }
        } else if (fabs(tree->angularVelocity) >= 0.03f) {
            if (!(tree->options & 2)) {
                Vector3 local(0,0,27.0f), transformed;
                Matrix3D::Transform_Vector(tree->matrix,local,&transformed);
                Coord3D effect;
                effect.set(transformed.X,transformed.Y,transformed.Z);
                FXList::doFXPos(data->bounceFX,&effect,0,0.0f,0);
            }
        }
    } else {
        tree->angularVelocity += tree->angularAcceleration;
    }
}
