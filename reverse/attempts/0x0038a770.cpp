// ?placeObjectAtPosition@@YAPAVObject@@HVAsciiString@@AAUCoord3D@@PAVPlayer@@PBVPlayerTemplate@@@Z
// partial score=0.46 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: isolated placeObjectAtPosition reconstruction for 0x0038A770.

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};

class AsciiString
{
public:
    AsciiString() {}
    AsciiString(const AsciiString &) {}
    ~AsciiString();

private:
    char *m_buffer;
    char *m_end;
    char *m_capacity;
};

class ThingTemplate;
class PlayerTemplate;
class Team;
class BehaviorModule;
class CreateModuleInterface;
class LocomotorSet;

class ThingTemplate
{
public:
    Real getPlacementViewAngle() const;
};

class Object
{
public:
    void setOrientation(Real angle);
    ThingTemplate *getTemplate() const;
    void setPosition(const Coord3D *position);
    BehaviorModule **getBehaviorModules() const;
    class AIUpdateInterface *getAIUpdateInterface() const;
    Bool isKindOf(Int kind) const;
};

class CreateModuleInterface
{
public:
    void onBuildComplete();
};

class BehaviorModule
{
public:
    CreateModuleInterface *getCreate() const;
};

class Player
{
public:
    Team *getDefaultTeam() const;
};

class ThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &name);
    Object *newObject(const ThingTemplate *objectTemplate, Team *team);
};

class AIUpdateInterface
{
public:
    const LocomotorSet &getLocomotorSet() const;
};

class Pathfinder
{
public:
    void addObjectToPathfindMap(Object *object);
    Bool adjustDestination(Object *object, const LocomotorSet &locomotors,
        Coord3D *position);
    void updateGoal(Object *object, const Coord3D *position, Int layer);
};

class AI
{
public:
    Pathfinder *pathfinder() const;
};

class Team
{
public:
    void setActive();
};

extern ThingFactory *TheThingFactory;
extern AI *TheAI;

enum
{
    KINDOF_IMMOBILE = 0x00000001,
    LAYER_GROUND = 1
};

// ?placeObjectAtPosition@@YAPAVObject@@HVAsciiString@@AAUCoord3D@@PAVPlayer@@PBVPlayerTemplate@@@Z
Object *placeObjectAtPosition(Int slotNum, AsciiString objectTemplateName,
    Coord3D &pos, Player *player, const PlayerTemplate *playerTemplate)
{
    const ThingTemplate *objectTemplate =
        TheThingFactory->findTemplate(objectTemplateName);
    Object *object = TheThingFactory->newObject(
        objectTemplate, player->getDefaultTeam());
    if (object)
    {
        object->setOrientation(object->getTemplate()->getPlacementViewAngle());
        object->setPosition(&pos);

        Team *team = player->getDefaultTeam();
        for (BehaviorModule **module = object->getBehaviorModules(); *module;
            ++module)
        {
            CreateModuleInterface *create = (*module)->getCreate();
            if (!create)
                continue;
            create->onBuildComplete();
        }

        if (team)
            team->setActive();
        TheAI->pathfinder()->addObjectToPathfindMap(object);
        AIUpdateInterface *aiUpdate = object->getAIUpdateInterface();
        if (aiUpdate && !object->isKindOf(KINDOF_IMMOBILE))
        {
            if (TheAI->pathfinder()->adjustDestination(
                object, aiUpdate->getLocomotorSet(), &pos))
            {
                TheAI->pathfinder()->updateGoal(object, &pos, LAYER_GROUND);
                object->setPosition(&pos);
            }
        }
    }
    return object;
}
