// Retail 0x000FE640 / 695 B. Address-qualified owner: no semantic class identity claimed.
// Filters object template bits and kind categories; destroys a path when its
// current segment passes within field0C of field08. Always returns false.
// Object/Thing layouts come from the canonical headers. AIUpdateInterface+0x140
// is m_path (name_oracle witness); path/node offsets come from this retail body.
// queryAt001CF980 is the matched Object contract; slot 104 remains unnamed.
// Coord3D inline operations reproduce coord3d.cpp; strict greater-than rejection
// preserves retail floating-point comparison including unordered inputs.
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object
#include "coord3d.h"
// Inline coordinate operations preserve the matched implementation's raw copy.
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
inline Coord3D &Coord3D::operator=(const Coord3D &v) { struct Raw { unsigned x,y,z; }; *(Raw*)this=*(const Raw*)&v; return *this; }
inline Coord3D &Coord3D::operator-=(const Coord3DBase &v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
__forceinline Coord3D &Coord3D::operator+=(const Coord3DBase &v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
__forceinline Coord3D &Coord3D::operator*=(float s) { x*=s; y*=s; z*=s; return *this; }
inline float Coord3D::operator*(const Coord3DBase &v) const { return x*v.x+y*v.y+z*v.z; }
enum KindOfType { Kind000FE640 = 0 };
class Rva001CF980Result;
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const; const ThingTemplate *getTemplate() const;
#define OBJECT_TU_MEMBERS Rva001CF980Result *queryAt001CF980();
#include "object.h"
class Overridable { public:
    const Overridable *getFinalOverride() const;
    void *field00;
    Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable { public:
    char field08[0xc8];
    unsigned int fieldD0, fieldD4, fieldD8;
};
inline const ThingTemplate *Thing::getTemplate() const {
    const ThingTemplate *t=m_template;
    if(t && t->m_nextOverride) t=(const ThingTemplate*)t->m_nextOverride->getFinalOverride();
    return t;
}
class Rva001CF980Result { public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual bool slot104();
};
struct PathNode000FE640 { char field00[12]; Coord3D field0C; };
struct Path000FE640 { char field00[8]; PathNode000FE640 *field08; };
class AIUpdateInterface { public:
    void destroyPath();
    char field00[0x140];
    Path000FE640 *m_path;
};
class PathProximity000FE640 { public:
    bool apply(Object *obj);
    char field00[8];
    const Coord3D *field08;
    float field0C;
};
bool PathProximity000FE640::apply(Object *obj) {
    if(obj->getTemplate()->fieldD0 & 0x1000000 ||
       obj->getTemplate()->fieldD8 & 0x20 ||
       obj->isKindOf((KindOfType)0x67) ||
       obj->isKindOf((KindOfType)0x3b) ||
       obj->isKindOf((KindOfType)2) ||
       obj->isKindOf((KindOfType)0x39) ||
       obj->isKindOf((KindOfType)6) ||
       obj->isKindOf((KindOfType)0x32) ||
       obj->m_privateStatus & 1) return false;
    AIUpdateInterface *ai=obj->m_ai;
    if(ai && ai->m_path) {
        Rva001CF980Result *result=obj->queryAt001CF980();
        if(result && result->slot104()) return false;
        Coord3D start=obj->m_cachedPos;
        Coord3D end=ai->m_path->field08->field0C;
        Coord3D point=*field08;
        point-=start;
        Coord3D direction=end;
        direction-=start;
        float length=direction.GetLength();
        direction.Normalize();
        float projection=direction*point;
        if(projection<0.0f) point=start;
        else if(projection>length) point=end;
        else { point=direction; point*=projection; point.x+=start.x; point.y+=start.y; point.z+=start.z; }
        float dx=point.x-field08->x;
        float dy=point.y-field08->y;
        float dz=point.z-field08->z;
        float radius=field0C;
        if(dx*dx+dy*dy+dz*dz > radius*radius) return false;
        ai->destroyPath();
    }
    return false;
}
