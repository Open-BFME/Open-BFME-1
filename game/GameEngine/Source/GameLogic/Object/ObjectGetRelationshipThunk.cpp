// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z: game/GameEngine/Source/GameLogic/Object/Object.cpp

enum Relationship
{
    Relationship_Thunk
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    Relationship getRelationship(const Object *) const;
};

class ObjectGetRelationshipShim
{
public:
    Relationship get(const Object *other) const;
};

Relationship Object::getRelationship(const Object *other) const
{
    return ((const ObjectGetRelationshipShim *)this)->get(other);
}
