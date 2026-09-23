// ?method@Rva00205440@@QAEXXZ
// partial score=0.2 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc-
struct Coord3D { float x, y, z; };
struct StringData { unsigned short refs, capacity, length, spare; };

template<class T> class StringBase {
public:
	StringBase(const StringBase<T>& other);
	const StringData* m_data;
};

class AsciiString : public StringBase<char> {
public:
	AsciiString(const AsciiString& other) : StringBase<char>(other) {}
	~AsciiString();
};

class Waypoint {
public:
	char pad[0x0c];
	Coord3D location;
};

class Thing {
public:
	const Coord3D* getUnitDirectionVector2D() const;
};

class TerrainLogic {
public:
	virtual void v0() = 0; virtual void v1() = 0; virtual void v2() = 0;
	virtual void v3() = 0; virtual void v4() = 0; virtual void v5() = 0;
	virtual float getGroundHeight(float x, float y, Coord3D* normal) = 0;
	virtual void v7() = 0; virtual void v8() = 0; virtual void v9() = 0;
	virtual void v10() = 0; virtual void v11() = 0; virtual void v12() = 0;
	virtual void v13() = 0; virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0; virtual void v18() = 0;
	virtual void v19() = 0; virtual void v20() = 0; virtual void v21() = 0;
	virtual void v22() = 0; virtual void v23() = 0; virtual void v24() = 0;
	virtual void v25() = 0; virtual void v26() = 0; virtual void v27() = 0;
	virtual void v28() = 0; virtual void v29() = 0; virtual void v30() = 0;
	virtual Waypoint* getWaypointByName(AsciiString name) = 0;
};

class ObjectView {
public:
	void setStatusBit(int bit, bool set);
	void notifyModelConditionChanged();
	void kill(int damage, int death);
};

class Pathfinder {
public:
	bool slowDoesPathExist(ObjectView* owner, const Coord3D* start,
		const Coord3D* end, int flags);
};

class AICommandInterface {
public:
	void aiBfmeCommand38(const Coord3D* pos, int source);
	void aiBfmeCommand41(const Coord3D* pos, int source);
};

class IDView {
public:
	virtual void v0() = 0; virtual void v1() = 0; virtual void v2() = 0;
	virtual void v3() = 0; virtual void v4() = 0; virtual void v5() = 0;
	virtual void v6() = 0; virtual void v7() = 0; virtual void v8() = 0;
	virtual void v9() = 0; virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0; virtual void v14() = 0;
	virtual int getID() = 0;
};

class GameLogicView {
public:
	ObjectView* findObjectByID(int id);
};

class ReportView {
public:
	void report(ObjectView* owner, int source);
};

extern TerrainLogic* TheTerrainLogic;
extern unsigned char* TheAI;
extern GameLogicView* TheBfmeGameLogic;
extern float Rva01083BBC;

class Rva00205440 {
public:
	void method();
};

void Rva00205440::method()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	ObjectView* owner = *reinterpret_cast<ObjectView**>(self - 8);
	unsigned char* data = *reinterpret_cast<unsigned char**>(self - 12);
	AICommandInterface* commands = *reinterpret_cast<AICommandInterface**>(
		reinterpret_cast<unsigned char*>(owner) + 0x204);
	Coord3D destination;
	Waypoint* waypoint = 0;
	if (commands != 0 && data != 0) {
		waypoint = TheTerrainLogic->getWaypointByName(
			*reinterpret_cast<AsciiString*>(data + 0x14));
		if (waypoint != 0) {
			destination = waypoint->location;
		} else {
			const Coord3D* heading = reinterpret_cast<const Thing*>(owner)->getUnitDirectionVector2D();
			float xOffset = heading->x * Rva01083BBC;
			float yOffset = heading->y * Rva01083BBC;
			destination.x = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(owner) + 0x38)[0] + xOffset;
			destination.y = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(owner) + 0x38)[1] + yOffset;
			destination.z = TheTerrainLogic->getGroundHeight(destination.x, destination.y, 0);
		}
		Pathfinder* pathfinder = *reinterpret_cast<Pathfinder**>(TheAI + 0x0c);
		if (pathfinder->slowDoesPathExist(owner,
			reinterpret_cast<Coord3D*>(reinterpret_cast<unsigned char*>(owner) + 0x38),
			&destination, 0)) {
			if (data[0x18] == 1)
				commands->aiBfmeCommand41(&destination, 2);
			else
				commands->aiBfmeCommand38(&destination, 2);
			owner->setStatusBit(0x31, true);
		} else {
			IDView* targetInterface = *reinterpret_cast<IDView**>(
				reinterpret_cast<unsigned char*>(owner) + 0x200);
			int id = 0;
			if (targetInterface != 0)
				id = targetInterface->getID();
			ObjectView* victim = TheBfmeGameLogic->findObjectByID(id);
			if (victim != 0)
				reinterpret_cast<ReportView*>(victim)->report(owner, 1);
			owner->kill(8, 0);
		}
	}
}
