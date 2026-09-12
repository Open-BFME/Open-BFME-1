// ?findGoodBuildOrRepairPosition@WorkerAIUpdate@@IAE_NPBVObject@@0AAUCoord3D@@@Z
// partial score=0.89 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// Scratch reconstruction for WorkerAIUpdate::findGoodBuildOrRepairPosition,
// retail RVA 0x002C8A20, size 1154.
struct Coord3D { float x,y,z; };
struct Vector3 {
	float X,Y,Z;
	Vector3(float x,float y,float z):X(x),Y(y),Z(z){}
	void Normalize();
	Vector3 operator*(float s) const { return Vector3(X*s,Y*s,Z*s); }
};
class Overridable { public: virtual ~Overridable(); const Overridable *getFinalOverride()const {if(next)return next->getFinalOverride();return this;} Overridable *next; };
template<class T>class OVERRIDE {const T*p;public:const T*operator*()const{if(!p)return 0;return(T*)p->getFinalOverride();}operator const T*()const{return operator*();}};
class AsciiString { public: char *data; const char *str()const{return data?data+8:"";} };
class ThingTemplate:public Overridable {public:char pad08[0x18];AsciiString name;const AsciiString&getName()const{return name;}};
class GeometryInfo { public: char pad[0x44]; float getMajorRadius()const{return *(const float*)((const char*)this+0x44);} };
class Object { public:
	virtual ~Object(); OVERRIDE<ThingTemplate> m_template; char pad08[0x30]; Coord3D position; char pad44[0x30]; unsigned id; char pad78[0x44]; GeometryInfo geometry;
	const ThingTemplate*getTemplate()const{return m_template;} unsigned getID()const{return id;} const Coord3D*getPosition()const{return &position;}
	const GeometryInfo&getGeometryInfo()const{return geometry;} bool isUsingAirborneLocomotor()const;
};
class CRCParameterCheck; extern CRCParameterCheck *TheCRCParameterCheck; extern bool g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
struct FindPositionOptions {
	float minRadius,maxRadius,minZ,maxZDelta; Object *ignoreObject; unsigned flags; const Object *sourceToPathToDest; unsigned flags2;
	FindPositionOptions():minRadius(0),maxRadius(0),minZ(-99999.9f),maxZDelta(1e10f),ignoreObject(0),flags(0),sourceToPathToDest(0),flags2(0){}
};
extern bool findPositionAround(const Coord3D*,const FindPositionOptions*,Coord3D*);
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
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    ourPosition=(%f,%f,%f), theirPosition=(%f,%f,%f)",ourPosition.x,ourPosition.y,ourPosition.z,theirPosition.x,theirPosition.y,theirPosition.z);
	Coord3D bestPosition=theirPosition;
	Coord3D workingPosition=theirPosition;
	Vector3 offset(ourPosition.x-theirPosition.x,ourPosition.y-theirPosition.y,ourPosition.z-theirPosition.z);
	offset.Normalize();
	offset=offset*(target->getGeometryInfo().getMajorRadius()/2.0f);
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    scaled offset=(%f,%f,%f), radius=%f",offset.X,offset.Y,offset.Z,target->getGeometryInfo().getMajorRadius());
	workingPosition.x+=offset.X; workingPosition.y+=offset.Y; workingPosition.z+=offset.Z;
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    workingPosition=(%f,%f,%f), offset=(%f,%f,%f)",workingPosition.x,workingPosition.y,workingPosition.z,offset.X,offset.Y,offset.Z);
	FindPositionOptions options;
	options.minRadius=0.0f; options.maxRadius=100.0f; options.sourceToPathToDest=me;
	if(!me->isUsingAirborneLocomotor()) options.maxZDelta=10.0f;
	if(me->isUsingAirborneLocomotor()) options.ignoreObject=(Object*)target;
	bool spotFound=findNearestLabeledContactPointOnTarget((Object*)target,&bestPosition,
		&workingPosition,!g_bfmeDockingTraceActive);
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    findPositionAround returned %s; bestPosition=(%f,%f,%f)",spotFound?"TRUE":"FALSE",bestPosition.x,bestPosition.y,bestPosition.z);
	if(!spotFound)
		spotFound=findPositionAround(&workingPosition,&options,&bestPosition);
	positionOut=spotFound?bestPosition:workingPosition;
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"    selected position=(%f,%f,%f), workingPosition=(%f,%f,%f)",positionOut.x,positionOut.y,positionOut.z,workingPosition.x,workingPosition.y,workingPosition.z);
	if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  WorkerAIUpdate::findGoodBuildOrRepairPosition() END: positionOut=(%f,%f,%f)",positionOut.x,positionOut.y,positionOut.z);
	return spotFound;
}
