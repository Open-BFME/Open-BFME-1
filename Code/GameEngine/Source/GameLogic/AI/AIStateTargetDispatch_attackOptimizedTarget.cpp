// Retail 0x0027E070: optimized target dispatch.

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Coord2D
{
	float x;
	float y;
	__forceinline Coord2D(float xValue, float yValue) : x(xValue), y(yValue) {}
	__forceinline friend float operator *(const Coord2D &left, const Coord2D &right)
	{
		return left.x * right.x + left.y * right.y;
	}
};

class BfmeHordeMember
{
public:
	bool bfmeBlocksFormationRefresh();
};

class Thing;
class Object;

class AIStateTargetDispatch : public BfmeHordeMember
{
public:
	void attackOptimizedTarget(Thing *target);
	void attackOrdinaryTarget(Thing *target);

	unsigned char m_beforeObject[8];
	Object *m_object;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;

	unsigned char m_beforePos[0x38];
	Coord3D m_pos;
	unsigned char m_beforeAI[0x204 - 0x44];
	BfmeHordeMember *m_ai;
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;
	int getLayer() const;
};

class TerrainLogic
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual bool probePosition(const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

void AIStateTargetDispatch::attackOptimizedTarget(Thing *target)
{
	BfmeHordeMember *otherAI = target->m_ai;
	if (!otherAI)
		return;

	Object *self = m_object;
	bool selfBlocks = bfmeBlocksFormationRefresh();
	bool otherBlocks = otherAI->bfmeBlocksFormationRefresh();
	if (self->getRelationship(static_cast<Object *>(target)) != ALLIES)
		return;
	if (self->getLayer() != LAYER_GROUND)
		return;
	if (TheTerrainLogic->probePosition(&self->m_pos))
		return;
	if (!selfBlocks)
		return;
	if (!otherBlocks)
		return;

	const Coord3D *selfDir = self->getUnitDirectionVector2D();
	Coord3D dir;
	dir.x = selfDir->x;
	dir.y = selfDir->y;
	dir.z = selfDir->z;
	const Coord3D *targetDir = target->getUnitDirectionVector2D();
	Coord2D targetDir2(targetDir->x, targetDir->y);
	if (targetDir2 * *reinterpret_cast<const Coord2D *>(&dir) <= 0.0f)
		return;
	attackOrdinaryTarget(target);
}
