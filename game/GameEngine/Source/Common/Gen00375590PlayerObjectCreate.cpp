// ?createPlayerObject@Gen_00375590@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The entry is a BfmeOwnVVB: the call goes through ILT 0x0000504C to the
// matched BfmeOwnVVB::BfmeOwnVVB(void *) at 0x00190340.

extern void j_0003f0bc();
extern void j_0000bf2d();
extern void j_00004e35();

struct Gen00375590GetReceiver
{
	void *get();
};

class BfmeOwnVVB
{
public:
	BfmeOwnVVB(void *arg);
	unsigned char m_unmodelled_00[0x88];
};

class Gen00375590Entry
{
public:
	virtual ~Gen00375590Entry();
};

class Gen00375590PlayerList
{
};

class SidesList;
extern SidesList *TheSidesList;

struct Gen00375590AcceptReceiver
{
	bool accept(void *, int, BfmeOwnVVB *);
};

struct Gen00375590RemoveReceiver
{
	void remove(BfmeOwnVVB *);
};

void *__cdecl operator new(unsigned int);
inline void *operator new(unsigned int, void *place) { return place; }

class Gen_00375590
{
public:
	void createPlayerObject();
	void *getTemplate()
	{
		typedef void *(Gen00375590GetReceiver::*Get)();
		union
		{
			void *asVoid;
			Get asMember;
		} getFunction;
		getFunction.asVoid = (void *)j_0003f0bc;
		return (reinterpret_cast<Gen00375590GetReceiver *>(this)->*
			getFunction.asMember)();
	}
	void remove(BfmeOwnVVB *entry)
	{
		typedef void (Gen00375590RemoveReceiver::*Remove)(BfmeOwnVVB *);
		union
		{
			void *asVoid;
			Remove asMember;
		} removeFunction;
		removeFunction.asVoid = (void *)j_00004e35;
		(reinterpret_cast<Gen00375590RemoveReceiver *>(this)->*
			removeFunction.asMember)(entry);
	}
};

void Gen_00375590::createPlayerObject()
{
	typedef bool (Gen00375590AcceptReceiver::*Accept)(void *, int, BfmeOwnVVB *);
	Gen_00375590 *owner = this;
	void *templateObject = owner->getTemplate();
	register int index = 0;
	BfmeOwnVVB *entry = 0;

	while (true)
	{
		entry = new BfmeOwnVVB((void *)1);
		union
		{
			void *asVoid;
			Accept asMember;
		} acceptFunction;
		acceptFunction.asVoid = (void *)j_0000bf2d;
		if (!(reinterpret_cast<Gen00375590AcceptReceiver *>(
			(Gen00375590PlayerList *)TheSidesList)->*acceptFunction.asMember)(
			templateObject, index, entry))
			break;
		owner->remove(entry);
		++index;
	}

	if (entry != 0)
		delete (Gen00375590Entry *)entry;
}
