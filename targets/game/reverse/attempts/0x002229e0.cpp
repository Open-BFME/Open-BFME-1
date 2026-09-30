// ?nearest@C@@QAEPAVObject@@PBVCoord3D@@@Z
// partial score=0.0714 date=2026-09-30
// Banked partial for 0x002229E0 (112 B): nearest-2D scan over the Rva222970FilteredDispatch object list (+0x18).
// Opaque names; probe symbol ?nearest@C@@QAEPAVObject@@PBVCoord3D@@@Z
typedef float Real;
struct Coord3DBase { Coord3DBase &operator=(const Coord3DBase &that); float x,y,z; };
class Coord3D : public Coord3DBase { public: Coord3D(); Coord3D(const Coord3D &); ~Coord3D(); float GetLengthSqrd2D() const; Coord3D &Sub(const Coord3DBase &left, const Coord3DBase &right); };
inline float Coord3D::GetLengthSqrd2D() const { return x*x + y*y; }
inline Coord3D &Coord3D::Sub(const Coord3DBase &l, const Coord3DBase &r) { x=l.x-r.x; y=l.y-r.y; z=l.z-r.z; return *this; }
inline Real sqr(const Real &v){return v*v;}

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x;y=v.y;z=v.z; }
class Object;
struct N { N *next; N *prev; Object *object; };
struct Obj { char gap[0x38]; Coord3D pos; };
class C { public: Object *nearest(const Coord3D *pos); char gap[0x18]; N *objects; };

Object *C::nearest(const Coord3D *pos)
{
	Object *closest = 0;
	Real best = 3.4028235e38f;
	for (N *n = objects->next; n != objects; n = n->next) {
		Obj *o = (Obj *)n->object;
		if (!o) continue;
		Coord3D diff; diff.Sub(*pos, o->pos); Real d = diff.GetLengthSqrd2D();
		if (!closest || best > d) { best = d; closest = (Object*)o; }
	}
	return closest;
}
