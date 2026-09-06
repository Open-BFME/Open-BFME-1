// ?findClosest@Rva002494D0Owner@@QAEPAVRva002494D0Val@@PAURva002494D0Coord@@@Z
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: STLport list-copy find-closest helper, family 0x002494D0 /
// 0x0024BE00 (411 B each, identical body but a different owning class per
// its own SEH scope table) and 0x0024CAE0 (436 B, same core loop plus extra
// cleanup calls). Copies this->m_objects (offset 0x18), then for each
// element whose ->m_contain (offset 0x1FC) yields a non-null result via a
// vcall at vtable+0x68 (slot 26), pulls a candidate via vtable+0xEC (slot
// 59) on that result, push_back()s it into a local scratch list, and
// rescans that scratch list picking the candidate with the smallest
// squared 2D distance to the incoming Coord3D* (rejecting any candidate
// whose vtable+0x28 (slot 10) kind-lookup ->bfmeKindCQE() == 1). Real
// owner classes are HordeGarrisonContain/HordeTransportContain (see
// HordeGarrisonContainDestructorThunk.cpp / HordeTransportContainDestructorThunk.cpp,
// landed neighbours of these two RVAs) but the exact method name/signature
// is unrecovered, so this file uses address-derived stand-ins per the
// identity policy.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva002494D0Coord
{
	float x;
	float y;
};

class Rva002494D0Kind
{
public:
	char bfmeKindCQE( void );
};

class Rva002494D0Val
{
public:
	#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9)
	#undef RVASLOT
	virtual Rva002494D0Kind *getKind( void );

	char m_pad[ 0x38 ];
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
	virtual Rva002494D0Val *getVal( void );
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
	virtual Rva002494D0Result *getResult( void );
};

class Rva002494D0Obj
{
public:
	char m_pad[ 0x1fc ];
	Rva002494D0Contain *m_contain;
};

class Rva002494D0Owner
{
public:
	Rva002494D0Val *findClosest( Rva002494D0Coord *pos );

private:
	char m_pad[ 0x18 ];
	_STL::list<Rva002494D0Obj *> m_objects;
};

struct Rva002494D0Node
{
	Rva002494D0Node *next;
	Rva002494D0Node *prev;
	Rva002494D0Val *value;
};

Rva002494D0Val *Rva002494D0Owner::findClosest( Rva002494D0Coord *pos )
{
	_STL::list<Rva002494D0Obj *> objects( m_objects );
	_STL::list<Rva002494D0Val *> found;
	Rva002494D0Node *header = *(Rva002494D0Node **)&found;
	Rva002494D0Val *best = 0;
	float bestDistSqr = 3.402823466e+38F;

	for ( _STL::list<Rva002494D0Obj *>::iterator it = objects.begin();
		it != objects.end(); ++it )
	{
		Rva002494D0Contain *contain = (*it)->m_contain;
		if ( contain == 0 )
			continue;

		Rva002494D0Result *result = contain->getResult();
		if ( result == 0 )
			continue;

		Rva002494D0Val *val = result->getVal();
		found.push_back( val );

		for ( Rva002494D0Node *node = header->next; node != header; node = node->next )
		{
			Rva002494D0Val *item = node->value;
			if ( item->getKind()->bfmeKindCQE() == 1 )
				continue;

			float dx = pos->x - item->m_x;
			float dy = pos->y - item->m_y;
			float distSqr = dx * dx + dy * dy;
			if ( distSqr < bestDistSqr )
			{
				bestDistSqr = distSqr;
				best = item;
			}
		}
	}

	return best;
}
