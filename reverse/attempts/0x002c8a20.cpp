// ?findGoodBuildOrRepairPosition@WorkerAIUpdate@@IAE_NPBVObject@@0AAUCoord3D@@@Z
// partial score=0.95 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// Scratch reconstruction for WorkerAIUpdate::findGoodBuildOrRepairPosition,
// retail RVA 0x002C8A20, size 1154.
struct Coord3D { float x,y,z; Coord3D(){} Coord3D(const Coord3D&v){x=v.x;y=v.y;z=v.z;} };
class WWMath { public: static float __fastcall Inv_Sqrt(float); };
struct Vector3 {
	float X,Y,Z;
	Vector3(float x,float y,float z):X(x),Y(y),Z(z){}
	Vector3(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;}
	Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
	__forceinline Vector3&operator*=(float s){X*=s;Y*=s;Z*=s;return *this;}
	__forceinline void Normalize() {
		float lengthSquared=X*X+Y*Y+Z*Z;
		if(lengthSquared!=0.0f) {
			float inverseLength=WWMath::Inv_Sqrt(lengthSquared);
			X*=inverseLength; Y*=inverseLength; Z*=inverseLength;
		}
	}
};
__forceinline Vector3 operator*(const Vector3&v,float s) { return Vector3(v.X*s,v.Y*s,v.Z*s); }
class Overridable { public: virtual ~Overridable(); const Overridable *getFinalOverride()const {if(next)return next->getFinalOverride();return this;} Overridable *next; };
template<class T>class OVERRIDE {const T*p;public:const T*operator*()const{if(!p)return 0;return(T*)p->getFinalOverride();}operator const T*()const{return operator*();}};
class AsciiString { public: char *data; const char *str()const{return data?data+8:"";} };
class ThingTemplate:public Overridable {public:char pad08[0x18];AsciiString name;const AsciiString&getName()const{return name;}};
class GeometryInfo { public: float majorRadius; float getMajorRadius()const{return majorRadius;} };
class Object { public:
	virtual ~Object(); OVERRIDE<ThingTemplate> m_template; char pad08[0x30]; Coord3D position; char pad44[0x30]; unsigned id; char pad78[0x44]; GeometryInfo geometry;
	const ThingTemplate*getTemplate()const{return m_template;} unsigned getID()const{return id;} const Coord3D*getPosition()const{return &position;}
	const GeometryInfo&getGeometryInfo()const{return geometry;} bool isUsingAirborneLocomotor()const;
};
class CRCParameterCheck; extern CRCParameterCheck *TheCRCParameterCheck; extern bool g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
struct FindPositionOptions {
	unsigned flags; float minRadius,maxRadius,startAngle,maxZDelta; Object *ignoreObject; const Object *sourceToPathToDest; Object *relationshipObject;
	FindPositionOptions():flags(0),minRadius(0),maxRadius(0),startAngle(-99999.9f),maxZDelta(1e10f),ignoreObject(0),sourceToPathToDest(0),relationshipObject(0){}
};
extern void findPositionAround(const Coord3D*,const FindPositionOptions*,Coord3D*);
class AIUpdateInterface {
public:
	bool findNearestLabeledContactPointOnTarget(Object*,Coord3D*,const Coord3D*,bool);
};
#pragma comment(linker, "/alternatename:?findNearestLabeledContactPointOnTarget@AIUpdateInterface@@QAE_NPAVObject@@PAUCoord3D@@PBU3@_N@Z=?j_00015ae6@@YAXXZ")
class WorkerAIUpdate:public AIUpdateInterface { protected: bool findGoodBuildOrRepairPosition(const Object*,const Object*,Coord3D&); };

bool WorkerAIUpdate::findGoodBuildOrRepairPosition(const Object *me,const Object *target,Coord3D &positionOut)
{
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  WorkerAIUpdate::findGoodBuildOrRepairPosition() BEGIN: Object %s(%d) with target %s(%d)",me->getTemplate()->getName().str(),me->getID(),target?target->getTemplate()->getName().str():"NULL",target?target->getID():0);
	Coord3D ourPosition=*me->getPosition();
	Coord3D theirPosition=*target->getPosition();
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    ourPosition=%g,%g,%g, theirPosition=%g,%g,%g",ourPosition.x,ourPosition.y,ourPosition.z,theirPosition.x,theirPosition.y,theirPosition.z);
	Coord3D bestPosition=theirPosition;
	Coord3D workingPosition=theirPosition;
	Vector3 offset(ourPosition.x-theirPosition.x,ourPosition.y-theirPosition.y,ourPosition.z-theirPosition.z);
	offset.Normalize();
	float targetRadius=target->getGeometryInfo().getMajorRadius();
	offset*=targetRadius;
	offset*=0.5f;
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    offset=%g,%g,%g, radius=%g",offset.X,offset.Y,offset.Z,targetRadius);
	workingPosition.x+=offset.X; workingPosition.y+=offset.Y; workingPosition.z+=offset.Z;
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    workingPosition=%g,%g,%g",workingPosition.x,workingPosition.y,workingPosition.z);
	FindPositionOptions options;
	options.minRadius=0.0f; options.maxRadius=100.0f; options.sourceToPathToDest=me;
	if(!me->isUsingAirborneLocomotor()) options.maxZDelta=10.0f;
	if(me->isUsingAirborneLocomotor()) options.ignoreObject=(Object*)target;
	bool skipCollideTest=true;
	if(g_bfmeDockingTraceActive) skipCollideTest=false;
	bool spotFound=findNearestLabeledContactPointOnTarget((Object*)target,&bestPosition,
		&workingPosition,skipCollideTest);
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    spotFound=%s, bestPosition=%g,%g,%g, workingPosition=%g,%g,%g",spotFound?"TRUE":"FALSE",bestPosition.x,bestPosition.y,bestPosition.z,workingPosition.x,workingPosition.y,workingPosition.z);
	if(!spotFound) {
		findPositionAround(&workingPosition,&options,&bestPosition);
		if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    TerrainLogic::FindPositionAround() workingPosition=%g,%g,%g, bestPosition=%g,%g,%g",workingPosition.x,workingPosition.y,workingPosition.z,bestPosition.x,bestPosition.y,bestPosition.z);
	}
	positionOut=spotFound?bestPosition:workingPosition;
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    positionOut=%g,%g,%g",positionOut.x,positionOut.y,positionOut.z);
	return spotFound;
}
