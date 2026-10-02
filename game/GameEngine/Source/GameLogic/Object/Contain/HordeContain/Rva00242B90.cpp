// cl: /DNDEBUG /MD
// Retail reads the unit predicates from slots +0x184 and +0x18C.
// This address-derived interface calls slots +0x10 and +0x114.
// The list head sits at this interface's address minus 0xAC.
typedef int Int;
typedef unsigned char Bool;

class BfmeObjAS
{
public:
	BfmeObjAS *bfmeParentAS(Int which);
};

class BfmeItemHM : public BfmeObjAS
{
};

class Object;

// ILT 0x0000E570 reaches the existing matched StateMachine body 0x000A1490.
// It reads the goal ID at +0x20 and returns GameLogic::findObjectByID's result.
class StateMachine
{
public:
	Object *getGoalObject();
};

class BfmeInnerCPB
{
public:
	void bfmeOneCPB(Int first, Int second);

private:
	unsigned char m_unobserved00[0x10];
};

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
	virtual Bool testAt184();
	virtual void rvaSlot98();
	virtual Bool testAt18c();

public:
	unsigned char m_unobserved04[0x1c];
	BfmeInnerCPB m_inner20;
	StateMachine *m_holder30;
};

struct Rva00242B90Member
{
	unsigned char m_unobserved00[0x204];
	Rva00242B90Unit *m_unit204;
};

struct Rva00242B90Node
{
	Rva00242B90Node *m_next;
	void *m_unobserved04;
	Rva00242B90Member *m_member08;
};


class Rva00242B90This
{
public:
	virtual void rvaSlot00(); virtual void rvaSlot01(); virtual void rvaSlot02(); virtual void rvaSlot03();
	virtual void callAt10(Bool arg);
	virtual void rvaSlot05(); virtual void rvaSlot06(); virtual void rvaSlot07(); virtual void rvaSlot08();
	virtual void rvaSlot09(); virtual void rvaSlot10(); virtual void rvaSlot11(); virtual void rvaSlot12();
	virtual void rvaSlot13(); virtual void rvaSlot14(); virtual void rvaSlot15(); virtual void rvaSlot16();
	virtual void rvaSlot17(); virtual void rvaSlot18(); virtual void rvaSlot19(); virtual void rvaSlot20();
	virtual void rvaSlot21(); virtual void rvaSlot22(); virtual void rvaSlot23(); virtual void rvaSlot24();
	virtual void rvaSlot25(); virtual void rvaSlot26(); virtual void rvaSlot27(); virtual void rvaSlot28();
	virtual void rvaSlot29(); virtual void rvaSlot30(); virtual void rvaSlot31(); virtual void rvaSlot32();
	virtual void rvaSlot33(); virtual void rvaSlot34(); virtual void rvaSlot35(); virtual void rvaSlot36();
	virtual void rvaSlot37(); virtual void rvaSlot38(); virtual void rvaSlot39(); virtual void rvaSlot40();
	virtual void rvaSlot41(); virtual void rvaSlot42(); virtual void rvaSlot43(); virtual void rvaSlot44();
	virtual void rvaSlot45(); virtual void rvaSlot46(); virtual void rvaSlot47(); virtual void rvaSlot48();
	virtual void rvaSlot49(); virtual void rvaSlot50(); virtual void rvaSlot51(); virtual void rvaSlot52();
	virtual void rvaSlot53(); virtual void rvaSlot54(); virtual void rvaSlot55(); virtual void rvaSlot56();
	virtual void rvaSlot57(); virtual void rvaSlot58(); virtual void rvaSlot59(); virtual void rvaSlot60();
	virtual void rvaSlot61(); virtual void rvaSlot62(); virtual void rvaSlot63(); virtual void rvaSlot64();
	virtual void rvaSlot65(); virtual void rvaSlot66(); virtual void rvaSlot67(); virtual void rvaSlot68();
	virtual void callAt114();

	void rva00242B90(BfmeObjAS *param);

private:
	unsigned char m_unobserved04[0x30];
	Int m_field34;
	unsigned char m_unobserved38[0xe0];
	Bool m_field118;
};


void Rva00242B90This::rva00242B90(BfmeObjAS *param)
{
	Rva00242B90This *savedThis = this;
	if (savedThis->m_field34 != 0)
		savedThis->callAt10(0);

	if (savedThis->m_field118 != 0)
		savedThis->callAt114();

	Rva00242B90Node *head = *reinterpret_cast<Rva00242B90Node **>(
		reinterpret_cast<char *>(savedThis) - 0xac);
	Rva00242B90Node *node = head->m_next;
	if (node != *reinterpret_cast<Rva00242B90Node **>(
		reinterpret_cast<char *>(savedThis) - 0xac))
	{
		for (;;)
		{
			Rva00242B90Unit *unit = node->m_member08->m_unit204;
			if (unit != 0)
			{
				if (param != 0)
				{
					BfmeObjAS *parentOfParam = param->bfmeParentAS(0);
					if (unit->testAt184())
					{
						BfmeItemHM *goal = reinterpret_cast<BfmeItemHM *>(
							unit->m_holder30->getGoalObject());
						if (goal != 0)
						{
							if (param == static_cast<BfmeObjAS *>(goal))
								goto next_member;
							BfmeObjAS *parentOfGoal = goal->bfmeParentAS(0);
							if (parentOfGoal != 0 && parentOfParam == parentOfGoal)
								goto next_member;
						}
					}
				}

				if (!unit->testAt18c())
					unit->m_inner20.bfmeOneCPB(0, 2);
			}

		next_member:
			node = node->m_next;
			if (node == *reinterpret_cast<Rva00242B90Node **>(
					reinterpret_cast<char *>(savedThis) - 0xac))
				break;
		}
	}
}
