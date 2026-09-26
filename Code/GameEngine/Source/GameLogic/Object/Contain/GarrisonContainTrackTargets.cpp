// cl: /DNDEBUG /MD /EHsc
// readable body of ?removeObjectFromGarrisonPoint@GarrisonContain@@IAEXPAVObject@@H@Z: Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp
// readable body of ?trackTargets@GarrisonContain@@IAEXXZ: Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp

#include <float.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x;
    float y;
    float z;
};

class Object;

enum ObjectID
{
    INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
    Object *getCurrentVictim() const;
    const Coord3D *getCurrentVictimPos() const;
};

class BodyStateInterface
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual int getDamageState() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
    const Coord3D *getPosition() const { return &m_cachedPos; }
    void setPosition(const Coord3D *position);

private:
    unsigned char m_pad00[0x38];
    Coord3D m_cachedPos;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
    ObjectID getID() const { return m_id; }
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
    BodyStateInterface *getBody() const { return m_body; }

private:
    unsigned char m_pad44[0x30];
    ObjectID m_id;
    unsigned char m_pad78[0x188];
    BodyStateInterface *m_body;
    AIUpdateInterface *m_ai;
};

struct ContainedNode
{
    ContainedNode *next;
    ContainedNode *previous;
    Object *object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
struct GarrisonPointData
{
    ObjectID objectID;
    ObjectID targetID;
    unsigned int placeFrame;
    unsigned int lastEffectFrame;
    void *effect;
};

static float calcDistanceSquared(const Coord3D &first, const Coord3D &second)
{
    const float dx = first.x - second.x;
    const float dy = first.y - second.y;
    const float dz = first.z - second.z;
    return dx * dx + dy * dy + dz * dz;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual int getObjectGarrisonPointIndex(ObjectID objectID);

protected:
    void trackTargets();
    int findClosestFreeGarrisonPointIndex(int conditionIndex,
                                          const Coord3D *targetPosition);
    void removeObjectFromGarrisonPoint(Object *occupant, int pointIndex);
    void putObjectAtGarrisonPoint(Object *object, ObjectID targetID,
                                  int conditionIndex, int index);

private:
    unsigned char m_pad04[4];
    Object *m_object;
    unsigned char m_pad0c[0x2c];
    ContainedNode *m_containedItems;
    unsigned char m_pad3c[0x9c];
    GarrisonPointData m_garrisonPointData[40];
    int m_garrisonPointsInUse;
    Coord3D m_garrisonPoints[3][40];
    int m_unmodelled_99c[3];
};

// ?removeObjectFromGarrisonPoint@GarrisonContain@@IAEXPAVObject@@H@Z
void GarrisonContain::removeObjectFromGarrisonPoint(Object *occupant, int pointIndex)
{
    if (!occupant)
        return;

    if (pointIndex == -1)
    {
        for (int candidateIndex = 0; candidateIndex < 40; ++candidateIndex)
        {
            if (m_garrisonPointData[candidateIndex].objectID == occupant->getID())
                removeObjectFromGarrisonPoint(occupant, candidateIndex);
        }
        return;
    }

    if (pointIndex < 0 || pointIndex >= 40)
        return;

    m_garrisonPointData[pointIndex].objectID = INVALID_OBJECT_ID;
    m_garrisonPointData[pointIndex].targetID = INVALID_OBJECT_ID;
    m_garrisonPointData[pointIndex].placeFrame = 0;
    m_garrisonPointData[pointIndex].lastEffectFrame = 0;
    --m_garrisonPointsInUse;

    occupant->setPosition(m_object->getPosition());
}

// ?findClosestFreeGarrisonPointIndex@GarrisonContain@@IAEHHPBUCoord3D@@@Z
int GarrisonContain::findClosestFreeGarrisonPointIndex(
    int conditionIndex, const Coord3D *targetPosition)
{
    if (!targetPosition || m_garrisonPointsInUse == 40)
        return -1;

    const int pointCount = m_unmodelled_99c[conditionIndex];
    if (m_garrisonPointsInUse >= pointCount)
        return -1;

    const Coord3D *const objectPosition = m_object->getPosition();
    if (targetPosition->x == objectPosition->x &&
        targetPosition->y == objectPosition->y &&
        targetPosition->z == objectPosition->z)
    {
        for (int freePointIndex = 0; freePointIndex < 40; ++freePointIndex)
        {
            if (m_garrisonPointData[freePointIndex].objectID == INVALID_OBJECT_ID)
                return freePointIndex;
        }
        return conditionIndex;
    }

    int closestIndex = -1;
    float closestDistanceSquared = FLT_MAX;
    for (int candidatePointIndex = 0; candidatePointIndex < pointCount; ++candidatePointIndex)
    {
        if (m_garrisonPointData[candidatePointIndex].objectID == INVALID_OBJECT_ID)
        {
            const float distanceSquared = calcDistanceSquared(
                *targetPosition, m_garrisonPoints[conditionIndex][candidatePointIndex]);
            if (distanceSquared < closestDistanceSquared)
            {
                closestDistanceSquared = distanceSquared;
                closestIndex = candidatePointIndex;
            }
        }
    }
    return closestIndex;
}

// ?trackTargets@GarrisonContain@@IAEXXZ
void GarrisonContain::trackTargets()
{
    int conditionIndex = -1;
    switch (m_object->getBody()->getDamageState())
    {
        case 0: conditionIndex = 0; break;
        case 1: conditionIndex = 1; break;
        case 2: conditionIndex = 2; break;
        case 3: conditionIndex = 2; break;
    }

    for (ContainedNode *containedNode = m_containedItems->next;
         containedNode != m_containedItems;
         containedNode = containedNode->next)
    {
        Object *const occupant = containedNode->object;
        const int currentIndex = getObjectGarrisonPointIndex(occupant->getID());
        if (currentIndex == -1)
            continue;

        AIUpdateInterface *const aiUpdate = occupant->getAIUpdateInterface();
        if (!aiUpdate)
            continue;

        Object *const victim = aiUpdate->getCurrentVictim();
        const Coord3D *victimPosition = aiUpdate->getCurrentVictimPos();
        if (!victim && !victimPosition)
            continue;
        if (victim)
            victimPosition = victim->getPosition();

        const Coord3D *const objectPosition = occupant->getPosition();
        const int newIndex = findClosestFreeGarrisonPointIndex(
            conditionIndex, victimPosition);
        if (newIndex == -1)
            continue;

        const float currentDistanceSquared = calcDistanceSquared(
            *victimPosition, *objectPosition);
        const float newDistanceSquared = calcDistanceSquared(
            *victimPosition, m_garrisonPoints[conditionIndex][newIndex]);
        if (newDistanceSquared < currentDistanceSquared)
        {
            removeObjectFromGarrisonPoint(occupant, currentIndex);
            putObjectAtGarrisonPoint(occupant,
                                     victim ? victim->getID() : INVALID_OBJECT_ID,
                                     conditionIndex, newIndex);
        }
    }
}
