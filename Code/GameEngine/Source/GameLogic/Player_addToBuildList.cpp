// cl: /DNDEBUG /MD /EHsc
// readable body of ?addToBuildList@Player@@QAEXPAVObject@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// Open-BFME5: ZH Player::addToBuildList. Coord3D copy ctor keeps the by-value
// location argument in the 16-byte frame retail uses.

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &src);

private:
	StringBase(const StringBase<T> &src);
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }
	AsciiString &operator=(const AsciiString &src)
	{
		set(src);
		return *this;
	}
};

struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
};

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vftable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return m_name; }

	unsigned char m_pad08[0x18];
	AsciiString m_name;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thing = m_thingTemplate;
		if (thing && thing->m_nextOverride)
			thing = (const ThingTemplate *)thing->m_nextOverride->getFinalOverride();
		return thing;
	}

	const Coord3D *getPosition() const { return &m_pos; }
	float getOrientation() const { return m_angle; }
	unsigned int getID() const { return m_id; }

	void *m_vftable;
	ThingTemplate *m_thingTemplate;
	unsigned char m_pad08[0x30];
	Coord3D m_pos;
	float m_angle;
	unsigned char m_pad48[0x2C];
	unsigned int m_id;
};

class BuildListInfo
{
public:
	BuildListInfo();

	void setObjectID(unsigned int id) { m_objectID = id; }
	void setTemplateName(AsciiString name) { m_templateName = name; }
	void setLocation(Coord3D loc) { m_location = loc; }
	void setAngle(float angle) { m_angle = angle; }
	void setNumRebuilds(unsigned int n) { m_numRebuilds = n; }
	void setNextBuildList(BuildListInfo *next) { m_nextBuildList = next; }

private:
	void *m_vftable;
	AsciiString m_buildingName;
	AsciiString m_templateName;
	Coord3D m_location;
	float m_rallyX;
	float m_rallyY;
	float m_angle;
	bool m_initiallyBuilt;
 unsigned char m_pad25[3];
	unsigned int m_numRebuilds;
	BuildListInfo *m_nextBuildList;
	unsigned char m_pad30[0x18];
	unsigned int m_objectID;
	unsigned char m_tail[0x40];
};

class Player
{
public:
	void addToBuildList(Object *obj);

private:
	unsigned char m_pad[0x1C0];
	BuildListInfo *m_pBuildList;
};

void Player::addToBuildList(Object *obj)
{
	BuildListInfo *newInfo = new BuildListInfo;
	newInfo->setObjectID(obj->getID());
	newInfo->setTemplateName(obj->getTemplate()->getName());
	newInfo->setLocation(*obj->getPosition());
	newInfo->setAngle(obj->getOrientation());
	newInfo->setNumRebuilds(0);
	newInfo->setNextBuildList(m_pBuildList);
	m_pBuildList = newInfo;
}
