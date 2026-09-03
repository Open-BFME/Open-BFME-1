// ?bfmeSpawnB950@BfmeModB950@@QAEXPBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.72 date=2026-09-03
// cl: /DNDEBUG /MD /EHs-c-
// Convert 0x0026B950: ThingFactory findTemplate/newObject + setPosition.

struct Coord3D
{
	float x, y, z;
};

class AsciiString
{
};

class ThingTemplate
{
};

class Team
{
};

struct BfmeStatusB950
{
	int m_a;
	int m_b;
	int m_c;
};

class Object
{
public:
	void setPosition(const Coord3D *pos);
	virtual void bfmeSpare00B950(void);
	virtual void bfmeSpare01B950(void);
	virtual void bfmeSpare02B950(void);
	virtual void bfmeSpare03B950(void);
	virtual void bfmeSpare04B950(void);
	virtual void bfmeSpare05B950(void);
	virtual void bfmeSpare06B950(void);
	virtual void bfmeSpare07B950(void);
	virtual void bfmeSpare08B950(void);
	virtual void bfmeSpare09B950(void);
	virtual void bfmeSpare10B950(void);
	virtual void bfmeSpare11B950(void);
	virtual void bfmeSpare12B950(void);
	virtual void bfmeSpare13B950(void);
	virtual void bfmeSpare14B950(void);
	virtual void bfmeSpare15B950(void);
	virtual void bfmeSpare16B950(void);
	virtual void bfmeSpare17B950(void);
	virtual void bfmeSpare18B950(void);
	virtual void bfmeSpare19B950(void);
	virtual void bfmeTakeB950(Team *team);

	char m_bfmePad[0x238];
	Team *m_bfmeTeam;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(ThingTemplate *tmplate, Team *team, const BfmeStatusB950 &status, void *extra);
};

extern ThingFactory *TheThingFactory;

class BfmeModB950
{
public:
	void bfmeSpawnB950(const Coord3D *pos, const AsciiString *name);

private:
	char m_bfmePad00[8];
	Object *m_bfmeObject;
};

void BfmeModB950::bfmeSpawnB950(const Coord3D *pos, const AsciiString *name)
{
	Object *obj;
	ThingTemplate *tmplate = TheThingFactory->findTemplate(*name);
	if (!tmplate)
		return;

	Team *none = 0;
	BfmeStatusB950 status;
	status.m_a = (int)none;
	status.m_b = (int)none;
	status.m_c = (int)none;
	obj = TheThingFactory->newObject(tmplate, none, status, none);
	if (obj)
	{
		obj->setPosition(pos);
		obj->bfmeTakeB950(m_bfmeObject->m_bfmeTeam);
	}
}
