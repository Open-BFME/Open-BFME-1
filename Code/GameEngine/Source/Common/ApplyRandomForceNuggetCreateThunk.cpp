// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

struct Coord3D
{
    float x;
    float y;
    float z;
};

class Object;

class ApplyRandomForcePhysicsShim
{
public:
    Object *applyForce(const Coord3D *);
};

class Object
{
    unsigned char padding[0x208];

public:
    ApplyRandomForcePhysicsShim *physics;
};

void __cdecl calcApplyRandomForce(float, float, float, float, Coord3D *);

class ApplyRandomForceNugget
{
    float minMagnitude;
    float maxMagnitude;
    float minPitch;
    float maxPitch;

public:
    virtual Object *create(const Object *, const Object *, unsigned int) const;
};

// ?create@ApplyRandomForceNugget@@UBEPAVObject@@PBV2@0I@Z
Object *ApplyRandomForceNugget::create(const Object *primary, const Object *, unsigned int) const
{
    Object *result = const_cast<Object *>(primary);

    if (primary) {
        ApplyRandomForcePhysicsShim *physics = primary->physics;
        if (physics) {
            Coord3D force;
            calcApplyRandomForce(minMagnitude, maxMagnitude, minPitch, maxPitch, &force);
            result = physics->applyForce(&force);
        }
    }

    return result;
}
