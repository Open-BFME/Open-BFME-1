// ?method@Rva0021D360Owner@@QAEXPAVObject@@@Z
// partial score=0.43 date=2026-09-21
// ?d_0021d360@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Address-derived method; the retail owner class is unknown, so the class
// itself and its unresolved vtable slots keep the address token, but the
// layout is well evidenced: this body is reached through a SECONDARY
// interface (ecx), with the PRIMARY module at ecx-0x20 -- the exact split
// GarrisonContain_onRemoving.cpp documents for GarrisonContain's own
// secondary interface.  It opens by direct-calling the known
// GarrisonContain::onRemoving(Object*) thunk (0x0021F0A0) on itself before
// doing its own cleanup, the usual Derived::onRemoving calling
// Base::onRemoving shape.  The cleanup walks a std::map<int,{int,int}> at
// secondary+0x9a4 (= primary+0x9c4, matching ContestableContain::m_objectData's
// documented offset in ContestableContain.cpp exactly once the +0x20 split is
// accounted for): find() with a key from a primary-vtable slot 0x6c query and
// an AttachedState-like accessor (bfmeParentAS, still a dump) defaulting to 0,
// then _M_increment (STLRbGlobalBoolIncrementThunk.cpp) forward through every
// remaining node clearing whichever of its two int fields equals the incoming
// Object* or that key.
//
// globals: none; callees: see reverse/functions.csv for 0x0021D360 neighbours.

#include <map>

class BfmeObjAS
{
public:
	int bfmeParentAS(int flags);		// ?bfmeParentAS@BfmeObjAS@@QAEPAV1@H@Z, still a dump; result used only as an int key
};

class Object : public BfmeObjAS
{
};

// Secondary interface vtable: onRemoving sits at +0x48 (matches
// GarrisonContain_onRemoving.cpp's own count), and this body also reaches an
// unresolved no-arg bool query at +0xC4.
class Rva0021D360Secondary
{
public:
	virtual void _sec_slot00();
	virtual void _sec_slot01();
	virtual void _sec_slot02();
	virtual void _sec_slot03();
	virtual void _sec_slot04();
	virtual void _sec_slot05();
	virtual void _sec_slot06();
	virtual void _sec_slot07();
	virtual void _sec_slot08();
	virtual void _sec_slot09();
	virtual void _sec_slot10();
	virtual void _sec_slot11();
	virtual void _sec_slot12();
	virtual void _sec_slot13();
	virtual void _sec_slot14();
	virtual void _sec_slot15();
	virtual void _sec_slot16();
	virtual void _sec_slot17();
	virtual void _sec_slot18();
	virtual void _sec_slot19();
	virtual void _sec_slot20();
	virtual void _sec_slot21();
	virtual void _sec_slot22();
	virtual void _sec_slot23();
	virtual void _sec_slot24();
	virtual void _sec_slot25();
	virtual void _sec_slot26();
	virtual void _sec_slot27();
	virtual void _sec_slot28();
	virtual void _sec_slot29();
	virtual void _sec_slot30();
	virtual void _sec_slot31();
	virtual void _sec_slot32();
	virtual void _sec_slot33();
	virtual void _sec_slot34();
	virtual void _sec_slot35();
	virtual void _sec_slot36();
	virtual void _sec_slot37();
	virtual void _sec_slot38();
	virtual void _sec_slot39();
	virtual void _sec_slot40();
	virtual void _sec_slot41();
	virtual void _sec_slot42();
	virtual void _sec_slot43();
	virtual void _sec_slot44();
	virtual void _sec_slot45();
	virtual void _sec_slot46();
	virtual void _sec_slot47();
	virtual void _sec_slot48();
	void onRemoving(Object *object);		// +0x48, direct (non-virtual) call to the known thunk
	virtual bool _sec_slotC4();			// +0xC4, unresolved
};

// Primary module (secondary - 0x20): an unresolved no-arg query at +0x6c.
class Rva0021D360Primary
{
public:
	virtual void _pri_slot00();
	virtual void _pri_slot01();
	virtual void _pri_slot02();
	virtual void _pri_slot03();
	virtual void _pri_slot04();
	virtual void _pri_slot05();
	virtual void _pri_slot06();
	virtual void _pri_slot07();
	virtual void _pri_slot08();
	virtual void _pri_slot09();
	virtual void _pri_slot10();
	virtual void _pri_slot11();
	virtual void _pri_slot12();
	virtual void _pri_slot13();
	virtual void _pri_slot14();
	virtual void _pri_slot15();
	virtual void _pri_slot16();
	virtual void _pri_slot17();
	virtual void _pri_slot18();
	virtual void _pri_slot19();
	virtual void _pri_slot20();
	virtual void _pri_slot21();
	virtual void _pri_slot22();
	virtual void _pri_slot23();
	virtual void _pri_slot24();
	virtual void _pri_slot25();
	virtual void _pri_slot26();
	virtual int _pri_slot6c(Object *object);	// +0x6c, unresolved
};

struct Rva0021D360Entry
{
	int m_bfme00;			// +0x00 (node value +0x14): matched against the Object* or the key
	unsigned char m_bfme04;	// +0x04 (node value +0x18): a second per-entry counter, byte-sized
	char m_pad_05[3];
};

typedef _STL::pair<const int, Rva0021D360Entry> Rva0021D360Pair;

typedef _STL::_Rb_tree<int,
	Rva0021D360Pair,
	_STL::_Select1st<Rva0021D360Pair>,
	_STL::less<int>,
	_STL::allocator<Rva0021D360Pair> > Rva0021D360Tree;

class Rva0021D360Owner : public Rva0021D360Secondary
{
public:
	void method(Object *object);
	void bfmeDoBDB(void *p, int h);	// ?bfmeDoBDB@BfmeSubBDB@@QAEXPAXH@Z, still a dump
	void updateContestStatus(void);	// ?updateContestStatus@ContestableContain@@QAEXXZ, matched (ContestableContain.cpp)

private:
	char m_pad_04[0x14 - 4];
	int m_bfme14;					// +0x14
	unsigned char m_bfme18;			// +0x18
	char m_pad_19[0x9a4 - 0x19];
	Rva0021D360Tree m_objectData;			// +0x9a4
};

// ?d_0021d360@@YAXXZ
void Rva0021D360Owner::method(Object *object)
{
	if (!object)
		return;

	onRemoving(object);

	if (!_sec_slotC4())
		return;

	Rva0021D360Primary *primary = (Rva0021D360Primary *)((char *)this - 0x20);

	int shape_frame_key_169[2];
	shape_frame_key_169[1] = 0;
	if (primary->_pri_slot6c(object))
		shape_frame_key_169[1] = object->bfmeParentAS(0);

	for (Rva0021D360Tree::iterator it = m_objectData.find(shape_frame_key_169[1]);
		it != m_objectData.end(); ++it)
	{
		Rva0021D360Entry &entry = it->second;
		if (entry.m_bfme00 == (int)object || entry.m_bfme00 == shape_frame_key_169[1])
		{
			entry.m_bfme00 = 0;
			--m_bfme18;
			if (shape_frame_key_169[1] == 0 && it->first == m_bfme14)
				--entry.m_bfme04;
		}
	}

	void *outParam;
	bfmeDoBDB(&outParam, (int)object);
	updateContestStatus();
}
