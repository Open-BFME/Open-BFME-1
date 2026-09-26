// cl: /DNDEBUG /MD /EHsc
struct Coord3D { float x,y,z; };
typedef bool Bool; typedef int Int;
class Overridable { public: virtual ~Overridable(); const Overridable *getFinalOverride()const {if(next)return next->getFinalOverride();return this;} Overridable *next; };
template<class T>class OVERRIDE {const T*p;public:const T*operator*()const{if(!p)return 0;return(T*)p->getFinalOverride();}operator const T*()const{return operator*();}};
class AsciiString { public: char *data; const char *str()const{return data?data+8:"";} };
class ThingTemplate:public Overridable {public:char pad08[0x18];AsciiString name;const AsciiString&getName()const{return name;}};
class Object { public:
 virtual ~Object(); OVERRIDE<ThingTemplate> m_template; char pad08[0x6c]; unsigned id;
 const ThingTemplate*getTemplate()const{return m_template;} unsigned getID()const{return id;}
 Bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,Int,Int,Bool)const;
};
class CRCParameterCheck; extern CRCParameterCheck *TheCRCParameterCheck; extern bool g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
struct ContactPointModuleData { char pad[0x58]; AsciiString *begin,*end; };
class AIUpdateInterface { public:
 char pad0[4]; ContactPointModuleData *moduleData; Object *owner;
 Bool findNearestLabeledContactPointOnTarget(Object*,Coord3D*,const Coord3D*,Bool);
};
Bool AIUpdateInterface::findNearestLabeledContactPointOnTarget(Object *target,Coord3D *result,const Coord3D *workingPosition,Bool skipCollideTest)
{
 Object *me;
 if(g_bfmeDockingTraceActive&&(me=owner,TheCRCParameterCheck)) {
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"      AIUpdateInterface::findNearestLabeledContactPointOnTarget BEGIN: Object %s(%d), target %s(%d), workingPos %g,%g,%g, skipCollideTest=%s",
   me->getTemplate()->getName().str(),me->getID(),target?target->getTemplate()->getName().str():"NULL",target?target->getID():0,
   workingPosition->x,workingPosition->y,workingPosition->z,skipCollideTest?"TRUE":"FALSE");
 }
 ContactPointModuleData *data=moduleData;
 for(AsciiString *name=data->begin;name!=data->end;++name) {
  if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        handling contactPointName %s",name->str());
  if(target->getWorldspaceBestContactPoint(result,workingPosition,name->str(),0,0,skipCollideTest)) {
   if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
    bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        handling contactPointName %s succeeded - result=%g,%g,%g, RETURN TRUE",name->str(),result->x,result->y,result->z);
   return true;
  }
  if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        handling contactPointName %s failed",name->str());
 }
 if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        end of contactPoints. return FALSE");
 return false;
}
