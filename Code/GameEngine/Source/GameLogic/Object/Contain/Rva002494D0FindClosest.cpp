// Open-BFME5: RVA-qualified containment findClosest body at 0x002494D0.
// ?findClosest@Rva002494D0Owner@@QAEPAVObject@@PBURva002494D0Coord@@@Z
// Exact clean C++ reconstruction; owner remains address-qualified because no named caller or vtable proof is available.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport


#include <list>

struct Rva002494D0Coord { float x; float y; float z; Rva002494D0Coord() {} Rva002494D0Coord(const Rva002494D0Coord &v) { x=v.x;y=v.y;z=v.z; } void sub(const Rva002494D0Coord *v) { x-=v->x;y-=v->y;z-=v->z; } float lengthSqr() const { return x*x+y*y+z*z; } };
inline float sqr(float x) { return x*x; }

class BfmeXCQE
{
public:
	char bfmeKindCQE(void);
};

class Rva002494D0Contain;

class Object
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9)
#undef RVASLOT
	virtual BfmeXCQE *getKind(void);

	char m_pad[0x34];
	Rva002494D0Coord m_position;
    const Rva002494D0Coord *getPosition() const { return &m_position; }
    char m_pad044[0x1fc-0x44];
    Rva002494D0Contain *m_contain;
};

class Rva002494D0Result
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
	RVASLOT(36) RVASLOT(37) RVASLOT(38) RVASLOT(39) RVASLOT(40) RVASLOT(41)
	RVASLOT(42) RVASLOT(43) RVASLOT(44) RVASLOT(45) RVASLOT(46) RVASLOT(47)
	RVASLOT(48) RVASLOT(49) RVASLOT(50) RVASLOT(51) RVASLOT(52) RVASLOT(53)
	RVASLOT(54) RVASLOT(55) RVASLOT(56) RVASLOT(57) RVASLOT(58)
#undef RVASLOT
	virtual _STL::list<Object *> *getVal(void);
};

class Rva002494D0Contain
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25)
#undef RVASLOT
	virtual Rva002494D0Result *getResult(void);
};

class Rva002494D0Owner
{
public:
	Object *findClosest(const Rva002494D0Coord *pos);

private:
	char m_pad[0x18];
	_STL::list<Object *> m_objects;
};

Object *Rva002494D0Owner::findClosest(const Rva002494D0Coord *pos)
{
	_STL::list<Object *> objects(m_objects);
	_STL::list<Object *> found;
	Object *best = 0;
	float bestDistSqr = 3.402823466e+38F;

    for (_STL::list<Object *>::iterator objectIt = objects.begin();
         objectIt != objects.end(); ++objectIt)
	{
		Rva002494D0Contain *contain = (*objectIt)->m_contain;
		if (contain == 0)
			continue;

		Rva002494D0Result *result = contain->getResult();
		if (result == 0)
			continue;

		found = *result->getVal();

        for (_STL::list<Object *>::iterator valueIt = found.begin();
             valueIt != found.end(); ++valueIt)
			{
				Object *item = *valueIt;
				if (item->getKind()->bfmeKindCQE() == 1)
					continue;

				Rva002494D0Coord difference = *pos;
                difference.sub(item->getPosition());
                difference.z = 0.0f;
                float distSqr = difference.lengthSqr();
                if (!best || bestDistSqr > distSqr)
				{
					bestDistSqr = distSqr;
					best = item;
				}
			}
		}

	return best;
}
