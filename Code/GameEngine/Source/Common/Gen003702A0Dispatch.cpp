// ?bfmeDispatch@Gen_003702A0@@QAEXPAX@Z
// cl: /DNDEBUG /MD /EHsc
#pragma optimize("a", on)

typedef int ObjectID;

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *value, int argument);
};

class Gen00370200Thunk
{
public:
	void dispatch(void **range, void *argument);
};

extern void j_000328da();

class Gen_003702A0
{
public:
	void bfmeDispatch(void *argument);
	unsigned char m_pad00[0xac];
	void *m_first;
	unsigned char m_padb0[8];
	void *m_third;
	unsigned char m_padbc[8];
	void *m_fourth;
	unsigned char m_padc8[8];
	void *m_second;
};

void Gen_003702A0::bfmeDispatch(void *argument)
{
	unsigned int field94 = *(unsigned int *)((unsigned char *)this + 0x94);
	*(void **)((unsigned char *)this + 0xf8) = argument;
	BfmeGlobFEA *global = *(BfmeGlobFEA **)0x012f0898;
	void *found = ((GameLogic *)global)->findObjectByID((ObjectID)field94);
	if (found)
		global->bfmeCallFEA(found, (int)argument);

	Gen00370200Thunk *helper =
		(Gen00370200Thunk *)((unsigned char *)this - 0x0c);
	typedef void (Gen00370200Thunk::*Dispatch)(void **, void *);
	union
	{
		void *asVoid;
		Dispatch asMember;
	} dispatchFunction;
	dispatchFunction.asVoid = (void *)j_000328da;
	(helper->*dispatchFunction.asMember)(&m_first, argument);
	(helper->*dispatchFunction.asMember)(&m_second, argument);
	(helper->*dispatchFunction.asMember)(&m_third, argument);
	(helper->*dispatchFunction.asMember)(&m_fourth, argument);
}
