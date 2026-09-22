// ?placeNetworkBuildingsForPlayer@@YAXHPBVGameSlot@@PAVPlayer@@PBVPlayerTemplate@@@Z
// partial score=0.3 date=2026-09-22
// Recovered network starting-building placement helper.
// cl: /O2 /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

template <class T> struct StringData {
    int refCount;
    unsigned short length;
    unsigned short capacity;
    T text[1];
};

template <class T> class StringBase {
protected:
    StringData<T> *m_data;

    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase &source);
    ~StringBase();

    template <class U> friend class StringBase;
};

class AsciiString : private StringBase<char> {
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString() {}

    void __cdecl format(AsciiString formatString, ...);

    Bool isNotEmpty() const
    {
        return m_data != 0 && m_data->length != 0;
    }
};

struct Coord3D {
    float x;
    float y;
    float z;
};

struct FindPositionOptions {
    unsigned int flags;
    float minRadius;
    float maxRadius;
    float startAngle;
    float maxZDelta;
    void *ignoreObject;
    const void *sourceToPathToDest;
    void *relationshipObject;

    FindPositionOptions() : flags(0), minRadius(0.0f), maxRadius(0.0f),
        startAngle(-99999.9f), maxZDelta(10000000000.0f), ignoreObject(0),
        sourceToPathToDest(0), relationshipObject(0) {}
};

class Waypoint {
public:
    char m_pad[0xc];
    Coord3D m_location;

    const Coord3D *getLocation() const
    {
        return &m_location;
    }
};

class GameSlot {
    char m_pad[0x10];
    Int m_startPos;

public:
    Int getStartPos() const
    {
        return m_startPos;
    }
};

class Object {
    char m_pad[0xc0];
    float m_boundingSphereRadius;

public:
    float boundingSphereRadius() const
    {
        return m_boundingSphereRadius;
    }
};

class TerrainLogic {
public:
    virtual void unused0() = 0;
    virtual void unused1() = 0;
    virtual void unused2() = 0;
    virtual void unused3() = 0;
    virtual void unused4() = 0;
    virtual void unused5() = 0;
    virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const = 0;
};

class PartitionManager {
public:
    virtual void unused0() = 0;
    virtual void unused1() = 0;
    virtual void unused2() = 0;
    virtual void unused3() = 0;
    virtual void unused4() = 0;
    virtual void update() = 0;
};

class Player {
public:
    Object *rva0038A770(AsciiString name, Coord3D &position);
    void rva003AA8F(Object *thing, Object *object);
    void onStructureConstructionComplete(Object *thing, Object *object, Bool completed);
    void onUnitCreated(Object *thing, Object *object);
};

class PlayerTemplate {
    char m_pad[0x34];

public:
    AsciiString startingBuilding;
};

class Rva000E0AD0 {
    char m_pad[0x38];

public:
    void *get(Int index);
};

extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *ThePartitionManager;
extern float Rva0107533C;
extern float Rva01075C6C;
extern float Rva010EB40C;

extern Waypoint *Rva00388820_FindWaypointByName(AsciiString name);
extern Bool __cdecl findPositionAround(const Coord3D *center,
    const FindPositionOptions *options, Coord3D *result);

void placeNetworkBuildingsForPlayer(Int slotNum, const GameSlot *slot,
    register Player *player, const PlayerTemplate *playerTemplate)
{
    Int startPos = slot->getStartPos();
    AsciiString waypointName;
    waypointName.format("Player_%d_Start", startPos + 1);
    AsciiString rallyWaypointName;
    rallyWaypointName.format("Player_%d_Rally", startPos + 1);
    Waypoint *waypoint = Rva00388820_FindWaypointByName(waypointName);
    Waypoint *rallyWaypoint = Rva00388820_FindWaypointByName(rallyWaypointName);
    if (!waypoint) {
        return;
    }

    Coord3D position;
    position.x = waypoint->m_location.x;
    position.y = waypoint->m_location.y;
    position.z = waypoint->m_location.z;
    position.z = TheTerrainLogic->getGroundHeight(position.x, position.y);
    AsciiString buildingTemplateName(playerTemplate->startingBuilding);
    if (!buildingTemplateName.isNotEmpty()) {
        return;
    }

    Object *constructionYard = player->rva0038A770(buildingTemplateName, position);
    if (!constructionYard) {
        return;
    }

    player->rva003AA8F(0, constructionYard);
    player->onStructureConstructionComplete(0, constructionYard, false);
    position.y -= constructionYard->boundingSphereRadius() * Rva0107533C;
    position.z = TheTerrainLogic->getGroundHeight(position.x, position.y);
    if (rallyWaypoint) {
        position = rallyWaypoint->m_location;
        position.z = TheTerrainLogic->getGroundHeight(position.x, position.y);
    }

    for (Int i = 0; i < 10; ++i) {
        AsciiString objectName(*(const AsciiString *)
            ((Rva000E0AD0 *)playerTemplate)->get(i));
        if (!objectName.isNotEmpty()) {
            continue;
        }

        Coord3D objectPosition = position;
        FindPositionOptions options;
        options.minRadius = constructionYard->boundingSphereRadius() * Rva01075C6C;
        options.maxRadius = constructionYard->boundingSphereRadius() * Rva010EB40C;
        ThePartitionManager->update();
        Bool foundPosition = findPositionAround(&position, &options, &objectPosition);
        if (foundPosition) {
            Object *unit = player->rva0038A770(objectName, objectPosition);
            if (unit) {
                player->onUnitCreated(0, unit);
            }
        }
    }
}
