// ?rva00242B90@Rva00242B90This@@QAEXPAVBfmeObjAS@@@Z
// partial score=0.51 date=2026-09-21
// cl: /DNDEBUG /MD
// Retail 0x00242B90, 194 bytes, __thiscall (ret 4, one stack arg: a
// BfmeObjAS* "param"). Optionally fires two of this object's own virtual
// slots (vtbl+0x10 when +0x34 is set, vtbl+0x114 when the +0x118 flag byte
// is set), then walks the intrusive list hanging off *(this-0xac) (a
// secondary-base back-pointer): for each node's member->+0x204 "unit", when
// param is non-null and the unit's vtbl+0x184 predicate is true and the
// unit's +0x30 holder has a goal (bfmeGetHM), a match on the goal itself or
// on a shared bfmeParentAS(0) ancestor skips the unit; otherwise the unit's
// vtbl+0x18c predicate decides whether to leave it alone or deactivate its
// embedded +0x20 sub-object via bfmeOneCPB(0, 2).
//
// vtable_lookup found no pin on any of the three candidate tables (slot 5 of
// 0x010AE230/0x010AED58/0x010B07E0) and callers_of finds no named caller, so
// no real class or method name is provable; this keeps the address token.

typedef int Int;
typedef unsigned char Bool;

class BfmeObjAS
{
public:
	BfmeObjAS *bfmeParentAS(Int arg);
};

class BfmeItemHM;

class BfmeHolderHM
{
public:
	BfmeItemHM *bfmeGetHM();
};

class BfmeInnerCPB
{
public:
	void bfmeOneCPB(Int a, Int b);
};

// The +0x204 "unit" object hanging off each list member: two unnamed virtual
// predicates (vtbl+0x184, vtbl+0x18c) plus a +0x30 BfmeHolderHM* and an
// embedded +0x20 BfmeInnerCPB sub-object, both reached by raw offset since
// no witnessed layout exists for this class.
class Rva00242B90Unit
{
public:
	virtual void rvaSlot00(); virtual void rvaSlot01(); virtual void rvaSlot02(); virtual void rvaSlot03();
	virtual void rvaSlot04(); virtual void rvaSlot05(); virtual void rvaSlot06(); virtual void rvaSlot07();
	virtual void rvaSlot08(); virtual void rvaSlot09(); virtual void rvaSlot10(); virtual void rvaSlot11();
	virtual void rvaSlot12(); virtual void rvaSlot13(); virtual void rvaSlot14(); virtual void rvaSlot15();
	virtual void rvaSlot16(); virtual void rvaSlot17(); virtual void rvaSlot18(); virtual void rvaSlot19();
	virtual void rvaSlot20(); virtual void rvaSlot21(); virtual void rvaSlot22(); virtual void rvaSlot23();
	virtual void rvaSlot24(); virtual void rvaSlot25(); virtual void rvaSlot26(); virtual void rvaSlot27();
	virtual void rvaSlot28(); virtual void rvaSlot29(); virtual void rvaSlot30(); virtual void rvaSlot31();
	virtual void rvaSlot32(); virtual void rvaSlot33(); virtual void rvaSlot34(); virtual void rvaSlot35();
	virtual void rvaSlot36(); virtual void rvaSlot37(); virtual void rvaSlot38(); virtual void rvaSlot39();
	virtual void rvaSlot40(); virtual void rvaSlot41(); virtual void rvaSlot42(); virtual void rvaSlot43();
	virtual void rvaSlot44(); virtual void rvaSlot45(); virtual void rvaSlot46(); virtual void rvaSlot47();
	virtual void rvaSlot48(); virtual void rvaSlot49(); virtual void rvaSlot50(); virtual void rvaSlot51();
	virtual void rvaSlot52(); virtual void rvaSlot53(); virtual void rvaSlot54(); virtual void rvaSlot55();
	virtual void rvaSlot56(); virtual void rvaSlot57(); virtual void rvaSlot58(); virtual void rvaSlot59();
	virtual void rvaSlot60(); virtual void rvaSlot61(); virtual void rvaSlot62(); virtual void rvaSlot63();
	virtual void rvaSlot64(); virtual void rvaSlot65(); virtual void rvaSlot66(); virtual void rvaSlot67();
	virtual void rvaSlot68(); virtual void rvaSlot69(); virtual void rvaSlot70(); virtual void rvaSlot71();
	virtual void rvaSlot72(); virtual void rvaSlot73(); virtual void rvaSlot74(); virtual void rvaSlot75();
	virtual void rvaSlot76(); virtual void rvaSlot77(); virtual void rvaSlot78(); virtual void rvaSlot79();
	virtual void rvaSlot80(); virtual void rvaSlot81(); virtual void rvaSlot82(); virtual void rvaSlot83();
	virtual void rvaSlot84(); virtual void rvaSlot85(); virtual void rvaSlot86(); virtual void rvaSlot87();
	virtual void rvaSlot88(); virtual void rvaSlot89(); virtual void rvaSlot90(); virtual void rvaSlot91();
	virtual void rvaSlot92(); virtual void rvaSlot93(); virtual void rvaSlot94(); virtual void rvaSlot95();
	virtual void rvaSlot96();
	virtual Bool vtbl184();			///< vtbl+0x184 (slot 97)
	virtual void rvaSlot98();
	virtual Bool vtbl18c();			///< vtbl+0x18c (slot 99)

	BfmeHolderHM *holderAt30() const { return *(BfmeHolderHM **)((char *)this + 0x30); }
	BfmeInnerCPB *innerAt20() const { return (BfmeInnerCPB *)((char *)this + 0x20); }
};

struct Rva00242B90Member
{
	Rva00242B90Unit *unitAt204() const { return *(Rva00242B90Unit **)((char *)this + 0x204); }
};

struct Rva00242B90Node
{
	Rva00242B90Node *m_next;			///< +0x00
	void *m_pad4;						///< +0x04
	Rva00242B90Member *memberAt8() const { return *(Rva00242B90Member **)((char *)this + 8); }
};

// The object whose own vtable this method dispatches through: +0x34 and
// +0x118 own fields, +0x10/+0x114 own virtual slots, and the list is reached
// through a secondary-base back-pointer at this-0xac (not provably owned, so
// modelled as a raw offset rather than a real multiple-inheritance base).
class Rva00242B90This
{
public:
	virtual void tSlot00(); virtual void tSlot01(); virtual void tSlot02(); virtual void tSlot03();
	virtual void tvbl10(Bool arg);		///< vtbl+0x10 (slot 4)
	virtual void tSlot05(); virtual void tSlot06(); virtual void tSlot07(); virtual void tSlot08();
	virtual void tSlot09(); virtual void tSlot10(); virtual void tSlot11(); virtual void tSlot12();
	virtual void tSlot13(); virtual void tSlot14(); virtual void tSlot15(); virtual void tSlot16();
	virtual void tSlot17(); virtual void tSlot18(); virtual void tSlot19(); virtual void tSlot20();
	virtual void tSlot21(); virtual void tSlot22(); virtual void tSlot23(); virtual void tSlot24();
	virtual void tSlot25(); virtual void tSlot26(); virtual void tSlot27(); virtual void tSlot28();
	virtual void tSlot29(); virtual void tSlot30(); virtual void tSlot31(); virtual void tSlot32();
	virtual void tSlot33(); virtual void tSlot34(); virtual void tSlot35(); virtual void tSlot36();
	virtual void tSlot37(); virtual void tSlot38(); virtual void tSlot39(); virtual void tSlot40();
	virtual void tSlot41(); virtual void tSlot42(); virtual void tSlot43(); virtual void tSlot44();
	virtual void tSlot45(); virtual void tSlot46(); virtual void tSlot47(); virtual void tSlot48();
	virtual void tSlot49(); virtual void tSlot50(); virtual void tSlot51(); virtual void tSlot52();
	virtual void tSlot53(); virtual void tSlot54(); virtual void tSlot55(); virtual void tSlot56();
	virtual void tSlot57(); virtual void tSlot58(); virtual void tSlot59(); virtual void tSlot60();
	virtual void tSlot61(); virtual void tSlot62(); virtual void tSlot63(); virtual void tSlot64();
	virtual void tSlot65(); virtual void tSlot66(); virtual void tSlot67(); virtual void tSlot68();
	virtual void tvbl114();			///< vtbl+0x114 (slot 69)

	Int fieldAt34() const { return *(Int *)((char *)this + 0x34); }
	Bool fieldAt118() const { return *(Bool *)((char *)this + 0x118); }
	Rva00242B90Node *listHead() const { return *(Rva00242B90Node **)((char *)this - 0xac); }

	void rva00242B90(BfmeObjAS *param);
};

void Rva00242B90This::rva00242B90(BfmeObjAS *param)
{
	if (fieldAt34())
		tvbl10(0);

	if (fieldAt118())
		tvbl114();

	for (Rva00242B90Node *node = listHead(); node != (Rva00242B90Node *)((char *)this - 0xac); node = node->m_next)
	{
		Rva00242B90Unit *unit = node->memberAt8()->unitAt204();
		if (!unit)
			continue;

		bool skip = false;
		if (param)
		{
			BfmeObjAS *parentOfParam = param->bfmeParentAS(0);
			if (unit->vtbl184())
			{
				BfmeItemHM *goal = unit->holderAt30()->bfmeGetHM();
				if (goal)
				{
					if ((BfmeObjAS *)goal == param)
						continue;

					BfmeObjAS *parentOfGoal = ((BfmeObjAS *)goal)->bfmeParentAS(0);
					if (parentOfGoal && parentOfGoal == parentOfParam)
						continue;
				}
			}
		}

		if (unit->vtbl18c())
			continue;

		unit->innerAt20()->bfmeOneCPB(0, 2);
	}
}
