// ?move@Rva002BB170@@QAE_NPBVThingTemplate@@PBVCoord3D@@MPAVPlayer@@@Z
// partial score=0.3488 date=2026-10-02
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWMath
// ?move@Rva002BB170@@QAE_NPBVThingTemplate@@PBVCoord3D@@MPAVPlayer@@@Z
// Resumed bank: native Object/Coord3D; correct 1.5 scale; declared real filter slot.
// Still unmatched: 1253/1261 bytes; 816 differing non-relocation bytes.
// stlport
#include <vector>
#include <math.h>
#pragma intrinsic(sin,cos)
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
inline Coord3D::~Coord3D() {}
inline Coord3D &Coord3D::operator=(const Coord3D &v) { x=v.x; y=v.y; z=v.z; return *this; }
#define BFME_HAVE_COORD3D

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
class GeometryInfo {
public:
 GeometryInfo(GeometryType,bool,float,float,float);
 virtual ~GeometryInfo();
 unsigned char at004[0x0c];
 float at010,at014;
 unsigned char at018[0x44];
 Real getBoundingSphereRadius()const{return at014;}
};
class BfmeGeometryInfo {public: float boxMajorRadius()const; float boxMinorRadius()const;};
enum KindOfMask
{
	KINDOF_SHRUBBERY_MASK = 0x00000040,
	KINDOF_CLEARED_BY_BUILD_MASK = 0x00040000,
	KINDOF_ALWAYS_SELECTABLE_MASK = 0x02000000,
	KINDOF_INERT_MASK = 0x01000000
};

// Retail stores geometry at +0x60 and the three kind words at +0xC8.
enum KindOfType { K_PLACEHOLDER=0 };
class ThingTemplate : public Overridable
{
public:
 bool isKindOf(KindOfType)const;
	UnsignedInt getKindOfWord(Int word) const
	{
		return m_kindof[word];
	}

	const GeometryInfo *getTemplateGeometryInfo() const
	{
		return &m_geometryInfo;
	}

private:
	unsigned char m_pad[0x58];
	GeometryInfo m_geometryInfo;
	unsigned char m_pad2[0x0c];
	UnsignedInt m_kindof[5];
};

#define THING_TU_MEMBERS \
 bool isKindOf(KindOfType) const; \
 void getUnitDirectionVector3D(Coord3D &) const; \
 const ThingTemplate *getTemplate() const;
#define OBJECT_TU_MEMBERS \
 UnsignedInt getKindOfWord(Int word) const { return getTemplate()->getKindOfWord(word); }
#include "GameLogic/Object/object.h"
inline const ThingTemplate *Thing::getTemplate() const {
 const ThingTemplate *tmpl=m_template;
 if (tmpl && tmpl->m_nextOverride) tmpl=(const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
 return tmpl;
}

// Each result entry stores an object pointer and a distance as two dwords.
struct SimpleObjectIteratorClump
{
	Int m_valueBits;
	Int m_distanceBits;
};

struct SimpleObjectIterator
{
	_STL::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);

	Object *next() const
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return 0;
		return reinterpret_cast<Object *>((m_mpo->m_cursor++)->m_valueBits);
	}

	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
};

class PartitionFilter
{
public:
	PartitionFilter() : m_base(0) { }
	virtual ~PartitionFilter() { }
	virtual Bool allow(Object *obj) = 0;
 virtual Int getPlayerMask();

private:
	UnsignedInt m_base;
};

class PartitionFilterWouldCollide : public PartitionFilter
{
public:
	PartitionFilterWouldCollide(const Coord3D &pos, const GeometryInfo *geometry,
		Real angle, Bool desired)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
		m_geometry = geometry;
		m_angle = angle;
		m_desired = desired;
	}

	virtual Bool allow(Object *obj);

	operator Int()
	{
		return (Int)this;
	}

private:
	Coord3D m_position;
	const GeometryInfo *m_geometry;
	Real m_angle;
	Bool m_desired;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionManager
{
};

class BfmeWideForwardC
{
private:
	unsigned char m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Real b, Int c, Int d, Int e);
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern PartitionManager *ThePartitionManager;
extern GameLogic *TheBfmeGameLogic;


class Team;
enum Relationship { R0, R1, R2 };
class Player {public: Relationship getRelationship(const Team *)const;};
enum CommandSourceType { CMD0,CMD1,CMD2 };
class AICommandInterface {public: void aiBfmeCommand54(const Coord3D *,CommandSourceType);};
class AIUpdateInterface {public: bool bfmeBlocksFormationRefresh();};
class BuildAssistant {public: bool isRemovableForConstruction(Object *);};
class Rva000CBA20Point;
class Rva000CBA20 {public: float distSq(const Rva000CBA20Point *);};
extern float GetGameLogicRandomValueReal(float,float,char*,int);
static char sourcePath[]="F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\FoundationAIUpdate.cpp";
struct Rva002BB170Vector {
 float x,y,z;
 Rva002BB170Vector(float a,float b,float c):x(a),y(b),z(c){}
 __forceinline void rotate(float angle) { float sa=(float)sin(angle),ca=(float)cos(angle); float ox=x,oy=y; x=ca*ox-sa*oy; y=sa*ox+ca*oy; }
};
class Rva002BB170 {
public: bool move(const ThingTemplate *,const Coord3D *,float,Player *);
};
bool Rva002BB170::move(const ThingTemplate *what,const Coord3D *pos,float angle,Player *player) {
 Rva002BB170 *self=this;
 const BfmeGeometryInfo *shape=(const BfmeGeometryInfo *)((const char*)what+0x60);
 GeometryInfo gi(GEOMETRY_BOX,false,50.0f,shape->boxMajorRadius()*1.5f,shape->boxMinorRadius()*1.5f);
 float radius=gi.at010*1.5f;
 bool anyUnmovables=false;
 const BfmeWideResult &found=((BfmeWideForwardC*)ThePartitionManager)->bfmeForwardWideC((int)pos,gi.at014*1.5f,3,PartitionFilterWouldCollide(*pos,&gi,angle,true),0);
 while(true) {
  Object *them=found.next();
  if(!them)break;
  Object *sub=*(Object**)((char*)them+0x214);
  if(sub)them=sub;
  if(!them)continue;
  if(them->getKindOfWord(2)&0x01000000)continue;
  if(them->getKindOfWord(3)&0x80)continue;
  if(them->getKindOfWord(1)&0x08000000)continue;
  if(them->getKindOfWord(4)&0x20)continue;
  if(them->isKindOf((KindOfType)0x39))continue;
  if(((BuildAssistant*)self)->isRemovableForConstruction(them))continue;
  Team *team=*(Team**)((char*)them+0x23c);
  Relationship rel=player->getRelationship(team);
  if(rel==R1 || rel==R2) {
   AIUpdateInterface *ai=*(AIUpdateInterface**)((char*)them+0x204);
   if(ai) {
    float variedRadius=GetGameLogicRandomValueReal(0.5f,1.5f,sourcePath,637)*radius;
    Coord3D dest1,dest2;
    if(!what->isKindOf((KindOfType)0x3b)) {
     float dir=GetGameLogicRandomValueReal(-3.14159265358979323846f,3.14159265358979323846f,sourcePath,641);
     Rva002BB170Vector vec(variedRadius,0,0);
     vec.rotate(dir);
     dest1.x=pos->x+vec.x;dest1.y=pos->y+vec.y;dest1.z=pos->z+vec.z;
     dir=GetGameLogicRandomValueReal(-3.14159265358979323846f,3.14159265358979323846f,sourcePath,649);
     vec.rotate(dir);
     dest2.x=pos->x+vec.x;dest2.y=pos->y+vec.y;dest2.z=pos->z+vec.z;
    } else {
     Coord3D vec;
     Object *owner=*(Object**)((char*)self+8);
     if(owner->isKindOf((KindOfType)0x77)) {
      vec=*(Coord3D*)((char*)owner+0x38);
      vec.Sub(*pos);
      vec.x*=0.5f;vec.y*=0.5f;vec.z*=0.5f;
     } else {
      them->getUnitDirectionVector3D(vec);
      float scale=variedRadius+radius;
      vec.x*=scale;vec.y*=scale;vec.z*=scale;
     }
     dest1.x=pos->x+vec.x;dest1.y=pos->y+vec.y;dest1.z=pos->z+vec.z;
     dest2.x=pos->x-vec.x;dest2.y=pos->y-vec.y;dest2.z=pos->z-vec.z;
    }
    Coord3D dest;
    float distance1=((Rva000CBA20*)them)->distSq((Rva000CBA20Point*)&dest1);
    if(((Rva000CBA20*)them)->distSq((Rva000CBA20Point*)&dest2)>distance1)dest=dest1;else dest=dest2;
    if(!ai->bfmeBlocksFormationRefresh()) ((AICommandInterface*)((char*)ai+0x20))->aiBfmeCommand54(&dest,CMD2);
   }else anyUnmovables=true;
  }else anyUnmovables=true;
 }
 return !anyUnmovables;
}
