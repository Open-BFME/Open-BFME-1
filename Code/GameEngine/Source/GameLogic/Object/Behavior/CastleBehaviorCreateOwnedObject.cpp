// ?createOwnedObject@CastleBehavior@@QAEPAVObject@@PAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;

	unsigned char m_unmodelled_00[0x38];
	Coord3D m_position;
	void *m_castleData;
};

class CastleOwnedObjectFactory
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual Object *create(Object *owner, void *definition, Coord3D *position,
		void *castleData, Player *player, int initialState);
};

class CastleBehavior
{
public:
	Object *createOwnedObject(void *definition);
	void registerOwnedObject(Object *object);

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0c[0x20 - 0x0c];
	CastleOwnedObjectFactory m_ownedObjectFactory;
};

Object *CastleBehavior::createOwnedObject(void *definition)
{
	Object *owner = m_object;
	void *castleData = owner->m_castleData;
	Object *created = m_ownedObjectFactory.create(owner, definition,
		&owner->m_position, castleData, owner->getControllingPlayer(), 0);
	if (created)
		registerOwnedObject(created);
	return created;
}
