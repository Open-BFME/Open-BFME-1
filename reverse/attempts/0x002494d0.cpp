// ?findClosest@Rva002494D0Owner@@QAEPAVObject@@PAURva002494D0Coord@@@Z
// partial score=0.65 date=2026-09-09
// ?findClosest@Rva002494D0Owner@@QAEPAVObject@@PAURva002494D0Coord@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva002494D0Coord { float x; float y; };

class BfmeXCQE
{
public:
	char bfmeKindCQE(void);
};

class Object
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9)
#undef RVASLOT
	virtual BfmeXCQE *getKind(void);

	char m_pad[0x38];
	float m_x;
	float m_y;
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

class BfmeRva493A0Object
{
public:
	char m_pad[0x1fc];
	Rva002494D0Contain *m_contain;
};

class Rva002494D0Owner
{
public:
	Object *findClosest(Rva002494D0Coord *pos);

private:
	char m_pad[0x18];
	_STL::list<BfmeRva493A0Object *> m_objects;
};

struct Rva002494D0ObjectNode
{
	Rva002494D0ObjectNode *next;
	Rva002494D0ObjectNode *prev;
	BfmeRva493A0Object *value;
};

struct Rva002494D0ValueNode
{
	Rva002494D0ValueNode *next;
	Rva002494D0ValueNode *prev;
	Object *value;
};

Object *Rva002494D0Owner::findClosest(Rva002494D0Coord *pos)
{
	_STL::list<BfmeRva493A0Object *> objects(m_objects);
	_STL::list<Object *> found;
	Object *best = 0;
	float bestDistSqr = 3.402823466e+38F;

	Rva002494D0ValueNode *foundHeader =
		*(Rva002494D0ValueNode **)&found;
	Rva002494D0ObjectNode *objectsHeader =
		*(Rva002494D0ObjectNode **)&objects;
	Rva002494D0ObjectNode *objectNode = objectsHeader->next;
	for (; objectNode != objectsHeader; objectNode = objectNode->next)
	{
		Rva002494D0Contain *contain = objectNode->value->m_contain;
		if (contain == 0)
			continue;

		Rva002494D0Result *result = contain->getResult();
		if (result == 0)
			continue;

		_STL::list<Object *> *values = result->getVal();
		found = *values;

		for (Rva002494D0ValueNode *valueNode = foundHeader->next;
			valueNode != foundHeader; valueNode = valueNode->next)
			{
				Object *item = valueNode->value;
				if (item->getKind()->bfmeKindCQE() == 1)
					continue;

				float dx = pos->x - item->m_x;
				float dy = pos->y - item->m_y;
				float distSqr = dx * dx + dy * dy;
				if (distSqr < bestDistSqr)
				{
					bestDistSqr = distSqr;
					best = item;
				}
			}
		}

	return best;
}
