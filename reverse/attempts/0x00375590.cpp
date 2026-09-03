// ?d_00375590@@YAXXZ
// partial score=0.98 date=2026-09-03
// ?createPlayerObject@Gen_00375590@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void j_0003f0bc();
extern void j_0000504c();
extern void j_0000bf2d();
extern void j_00004e35();

struct Gen00375590GetReceiver
{
	void *get();
};

class Gen00375590EntryStorage
{
public:
	__declspec(noinline) Gen00375590EntryStorage(int value);
	unsigned char m_unmodelled_00[0x88];
};

struct Gen00375590ConstructorReceiver
{
	Gen00375590EntryStorage *construct(int);
};

Gen00375590EntryStorage::Gen00375590EntryStorage(int value)
{
	typedef Gen00375590EntryStorage *
		(Gen00375590ConstructorReceiver::*Initialize)(int);
	union
	{
		void *asVoid;
		Initialize asMember;
	} initializeFunction;
	initializeFunction.asVoid = (void *)j_0000504c;
	(reinterpret_cast<Gen00375590ConstructorReceiver *>(this)->*
		initializeFunction.asMember)(value);
}

class Gen00375590Entry
{
public:
	virtual ~Gen00375590Entry();
};

class Gen00375590PlayerList
{
};

struct Gen00375590AcceptReceiver
{
	bool accept(void *, int, Gen00375590EntryStorage *);
};

struct Gen00375590RemoveReceiver
{
	void remove(Gen00375590EntryStorage *);
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
	void remove(Gen00375590EntryStorage *entry)
	{
		typedef void (Gen00375590RemoveReceiver::*Remove)(Gen00375590EntryStorage *);
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
	typedef bool (Gen00375590AcceptReceiver::*Accept)(void *, int, Gen00375590EntryStorage *);
	Gen_00375590 *owner = this;
	void *templateObject = owner->getTemplate();
	register int index = 0;
	Gen00375590EntryStorage *entry = 0;

	while (true)
	{
		entry = new Gen00375590EntryStorage(1);
		union
		{
			void *asVoid;
			Accept asMember;
		} acceptFunction;
		acceptFunction.asVoid = (void *)j_0000bf2d;
		if (!(reinterpret_cast<Gen00375590AcceptReceiver *>(
			((Gen00375590PlayerList **)0x012ef428)[0])->*acceptFunction.asMember)(
			templateObject, index, entry))
			break;
		owner->remove(entry);
		++index;
	}

	if (entry != 0)
		delete (Gen00375590Entry *)entry;
}
