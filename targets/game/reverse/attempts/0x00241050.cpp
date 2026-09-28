// ?updateFormationMembers@BfmeAODHordeContainOwner@@QAEXXZ
// partial score=0.996 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BfmeAODHordeContainOwner::updateFormationMembers, retail 0x00241050 / 1540 bytes
// (ret +0x603, INT3 at +0x604). Identity: the matched AOD formation update at
// 0x00230AE0 calls owner->updateFormationMembers() through ILT 0x00010D6B.
// Receiver is the horde contain module: +4 module data (float at +0x288),
// +8 owner object, +0x38 contained list, +0xE4 secondary interface (slots 7
// and 95), primary slot 33 places a member. Field names below are offsets only.
// The per-member body sits in its own block after the set test: member is then
// loaded outside pos's scope, so the three pos copies load all words first.
// relativeAngleTo stays routed: its landed symbol takes struct Coord3D while the
// Coord3D operators here are landed with class Coord3D.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <set>
#include <map>
// Coord3D as its out-of-line helpers mangle it: struct base, class derived,
// implicit (memberwise) copy; the dot product sums x, z, y as MemberMotion's length does.
struct Coord3DBase { float x, y, z; };
class Coord3D : public Coord3DBase {
public:
	Coord3D() {}
	Coord3D(float ax, float ay, float az) { x = ax; y = ay; z = az; }
	Coord3D(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
	Coord3D &operator*=(float scale);
	Coord3D &operator+=(const Coord3DBase &that);
	Coord3D &operator-=(const Coord3DBase &that);
	float length() const;
	void normalize();
	Coord3D &CrossProduct(const Coord3DBase &left, const Coord3DBase &right);
	void sub(const Coord3DBase *that) { x -= that->x; y -= that->y; z -= that->z; }
	void add(const Coord3DBase *that) { x += that->x; y += that->y; z += that->z; }
	float operator*(const Coord3DBase &that) const { float v = x * that.x; v = v + z * that.z; v = v + y * that.y; return v; }
	void scale(float s) { x *= s; y *= s; z *= s; }
};

typedef float Real;
typedef unsigned int UnsignedInt;

extern void j_00049413();

class Route00241050 {};
#define ROUTE(ret, name, thunk, params, args) \
	__forceinline ret name params { typedef ret (Route00241050::*Call) params; \
	union { void (*address)(); Call member; } route = { thunk }; \
	return (((Route00241050 *)this)->*route.member) args; }

class Object;
class BfmeSpotCN;
class Gen_0016E370 { public: Real bfmeDistanceSquared(const BfmeSpotCN *other) const; };
class OpenContain { public: virtual Object *getClosestRider(Object *referenceObject); };
class BfmeSubDSU { public: void **bfmeTwoDSU(void **what); };

class AIUpdateInterface {
public:
	bool bfmeBlocksFormationRefresh();
};
template<int N> class BitFlags { public: UnsignedInt m_bits[(N + 31) / 32]; };

class Object {
public:
	unsigned char pad000[0x38];
	Coord3D m_cachedPos;
	Real m_cachedAngle;
	unsigned char pad048[0x74 - 0x48];
	int m_id;
	unsigned char pad078[0x110 - 0x78];
	BitFlags<320> m_modelConditionFlags;
	unsigned char pad138[0x204 - 0x138];
	AIUpdateInterface *m_ai;
	int getID() const { return m_id; }
	void bfmeClearYG(const BitFlags<320> &flags);
	ROUTE(Real, relativeAngleTo, j_00049413, (const Coord3D *point), (point))
	Real distanceSquared(const Object *other) const { return ((const Gen_0016E370 *)this)->bfmeDistanceSquared((const BfmeSpotCN *)other); }
};

class Pathfinder {
public:
	void Rva003E4190(Object *obj);
	void removeGoal003E3D20(Object *obj);
};
class AI { public: unsigned char pad000[0xc]; Pathfinder *m_pathfinder; };
extern AI *TheAI;
class GameLogic {
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheGameLogic;
extern const Real BfmeZeroRange;

struct ModuleData00241050 { unsigned char pad000[0x288]; Real at288; };
struct Delay00241050 { Coord3D pos; UnsignedInt count; };
typedef _STL::map<int, Delay00241050> DelayMap00241050;
typedef _STL::map<int, int> IndexMap00241050;

template<int N> class Slots00241050 : public Slots00241050<N - 1> { public: virtual void unused(char (*)[N]) = 0; };
template<> class Slots00241050<0> {};
class Primary00241050 : public Slots00241050<33> {
public:
	virtual void placeMember(Object *member, Coord3D *pos, Real angle, bool moving) = 0;
};
class Iface7_00241050 : public Slots00241050<7> {
public:
	virtual void memberPosition(Coord3D *pos, Object *member, Real *angle) = 0;
};
template<int N> class Wide00241050 : public Wide00241050<N - 1> { public: virtual void wide(char (*)[N]) = 0; };
template<> class Wide00241050<0> : public Iface7_00241050 {};
class Iface00241050 : public Wide00241050<87> {
public:
	virtual void abortFormation() = 0;
};

class BfmeAODHordeContainOwner {
public:
	void updateFormationMembers();

	void *vtable000;
	ModuleData00241050 *m_moduleData;
	Object *m_object;
	unsigned char pad00c[0x38 - 0xc];
	_STL::list<Object *> m_list038;
	unsigned char pad03c[0x114 - 0x3c];
	_STL::set<int> m_set114;
	unsigned char pad120[0x144 - 0x120];
	DelayMap00241050 m_map144;
	int m_id150;
	int m_id154;
	BitFlags<320> m_flags158;
	BitFlags<320> m_flags180;
	IndexMap00241050 m_map1a8;
	unsigned char pad1b4[0x208 - 0x1b4];
	int m_id208;
	unsigned char pad20c[0x214 - 0x20c];
	Coord3D m_pos214;
	bool m_flag220;

	Iface00241050 *iface() { return (Iface00241050 *)((char *)this + 0xe4); }
	Primary00241050 *primary() { return (Primary00241050 *)this; }
	Object *closestRider(Object *member) { return ((OpenContain *)this)->OpenContain::getClosestRider(member); }
	int &indexOf(const int &id) { return *(int *)((BfmeSubDSU *)&m_map1a8)->bfmeTwoDSU((void **)&id); }
};

void BfmeAODHordeContainOwner::updateFormationMembers()
{
	_STL::list<Object *>::iterator it = m_list038.begin();
	Object *owner = m_object;
	TheAI->m_pathfinder->Rva003E4190(owner);
	Real orient = owner->m_cachedAngle;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return;
	if (!ai->bfmeBlocksFormationRefresh())
		TheAI->m_pathfinder->removeGoal003E3D20(owner);
	ModuleData00241050 *data = m_moduleData;
	if (!data)
		return;
	Object *target = TheGameLogic->findObjectByID(m_id208);
	while (it != m_list038.end()) {
		Object *member = *it;
		++it;
		if (m_set114.find(member->getID()) == m_set114.end()) {
			Coord3D pos;
			Real angle = 0.0f;
			iface()->memberPosition(&pos, member, &angle);
			angle += orient;
			if (!m_map1a8.empty()) {
				if (member->m_modelConditionFlags.m_bits[5] & 1) {
					iface()->abortFormation();
					return;
				}
				GameLogic *logic = TheGameLogic;
				Object *a = logic->findObjectByID(m_id154);
				Object *b = logic->findObjectByID(m_id150);
				if (!b || !a) {
					iface()->abortFormation();
					return;
				}
				const Coord3D *aPos = &a->m_cachedPos;
				const Coord3D *bPos = &b->m_cachedPos;
				Real dx = aPos->x - bPos->x;
				Real dy = aPos->y - bPos->y;
				Real distSq = dx * dx + dy * dy;
				if (member == a) {
					if (distSq < 410.0f) {
						member->bfmeClearYG(m_flags158);
						angle = member->relativeAngleTo(bPos) + member->m_cachedAngle;
					}
				} else if (member == b) {
					if (distSq < 410.0f)
						member->bfmeClearYG(m_flags158);
					pos = member->m_cachedPos;
					pos.sub(aPos);
					pos.normalize();
					pos.scale(20.0f);
					pos.add(aPos);
					angle = member->relativeAngleTo(aPos) + member->m_cachedAngle;
				} else if (distSq < 410.0f) {
					int index = indexOf(member->getID());
					member->bfmeClearYG(m_flags180);
					angle = member->relativeAngleTo(aPos) + member->m_cachedAngle;
					pos = member->m_cachedPos;
					pos.sub(aPos);
					pos.normalize();
					pos.scale((Real)index);
					pos.add(aPos);
					Object *rider = closestRider(member);
					if (rider && member->distanceSquared(rider) < 55.0f) {
						Coord3D up(0.0f, 0.0f, 1.0f);
						Coord3D diff = member->m_cachedPos;
						diff -= *aPos;
						Coord3D side;
						side.CrossProduct(up, diff);
						Coord3D toRider = rider->m_cachedPos;
						toRider -= member->m_cachedPos;
						side.normalize();
						int offset = (toRider * side > BfmeZeroRange) ? -4 : 4;
						side *= (Real)offset;
						pos.add(&side);
					}
				}
			} else if (!m_map144.empty()) {
				DelayMap00241050::iterator found = m_map144.find(member->getID());
				if (found != m_map144.end()) {
					if (target && data->at288 != BfmeZeroRange) {
						Coord3D delta = member->m_cachedPos;
						delta.sub(&target->m_cachedPos);
						Real len = delta.length();
						if (len < data->at288 * 0.9) {
							pos = delta;
							pos.normalize();
							pos.scale(5.0f);
							pos += member->m_cachedPos;
						} else if (len < data->at288) {
							pos = member->m_cachedPos;
						}
					} else {
						Delay00241050 &delay = found->second;
						if (delay.count <= 0) {
							pos = delay.pos;
						} else {
							delay.count--;
							continue;
						}
					}
				}
				if (target)
					angle = member->relativeAngleTo(&target->m_cachedPos) + member->m_cachedAngle;
			} else if (m_flag220) {
				angle = member->relativeAngleTo(&m_pos214) + member->m_cachedAngle;
			}
			primary()->placeMember(member, &pos, angle, !ai->bfmeBlocksFormationRefresh());
		}
	}
}
