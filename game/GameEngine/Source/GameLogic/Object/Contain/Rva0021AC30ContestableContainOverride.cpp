// cl: /DNDEBUG /MD /EHsc
// stlport
// ?method@Rva0021AC30ContestableContain@@QAE_NPAVObject@@@Z
// Retail 0x0021AC30, 178 bytes, thiscall with one Object* argument, ret 4.
//
// The matched ContestableContain constructor (0x0021BEE0) and destructor
// (0x0021B6F0) install the primary vtable 0x010AB3C0, whose slot +0x48 is this
// body; OpenContain's primary vtable 0x010AC2B8 holds 0x00228050 in the same
// slot, and this body falls back to that base implementation. The method name
// is unproven, so the owner stays address-derived.
//
// With the contain list non-empty and its first rider under another player,
// the contest is decided by the contain interface at this+0x20 (+0xC4, +0x100,
// +0x110, +0xCC), the relationship to the owning object and the contest list
// at this+0x9BC.
#include <list>
typedef bool Bool;

extern "C" void __cdecl __identifier("?d_00228050@@YAXXZ")();
class Player;
class Object;
enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };

class Object
{
public:
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
};

typedef std::list<Object *> ContainedItemsList;

class ContainInterface0021AC30
{
public:
#define S(n) virtual void slot##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11)
	S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23)
	S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35)
	S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48)
	virtual Bool queryC4();					// +0xC4
	S(50)
	virtual Player *queryCC();				// +0xCC
	S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59) S(60) S(61) S(62) S(63)
	virtual int query100(int);				// +0x100
	S(65) S(66) S(67)
	virtual int query110();					// +0x110
#undef S
};

// OpenContain's primary-vtable slot +0x48 body (retail 0x00228050, still a
// dump), reached through ILT 0x00005943; address-derived until it is named.
class Rva00228050OpenContain
{
public:
	Bool method(Object * a0) {
	 // retail body is still the gen-dump row ?d_00228050@@YAXXZ (no C++ row yet); call it by that defined name
	 union { void (__cdecl *symbol)(); Bool (Rva00228050OpenContain::*member)(Object *); } c;
	 c.symbol = &__identifier("?d_00228050@@YAXXZ");
	 return (this->*c.member)(a0);
	}
};

class Rva0021AC30ContestableContain : public Rva00228050OpenContain
{
public:
	Bool method(Object *other);

private:
	Object *getObject() { return m_object; }

	unsigned char m_unreconstructed_000[8];
	Object *m_object;							// +0x08
	unsigned char m_unreconstructed_00c[0x20 - 0x0c];
	ContainInterface0021AC30 m_containInterface;		// +0x20
	unsigned char m_unreconstructed_024[0x38 - 0x24];
	ContainedItemsList m_containList;			// +0x38
	unsigned char m_unreconstructed_03c[0x9bc - 0x3c];
	ContainedItemsList m_contestList;			// +0x9BC
};

Bool Rva0021AC30ContestableContain::method(Object *other)
{
	ContainedItemsList::iterator it = m_containList.begin();
	if (it == m_containList.end())
		return true;
	if (other->getControllingPlayer() == (*it)->getControllingPlayer())
		return true;
	ContainInterface0021AC30 *contain = &m_containInterface;
	if (!contain->queryC4() && contain->query100(0) == contain->query110())
		return Rva00228050OpenContain::method(other);
	if (other->getRelationship(getObject()) != ENEMIES)
		return false;
	if (m_contestList.empty())
		return true;
	if (contain->queryCC() == other->getControllingPlayer())
		return true;
	return false;
}
