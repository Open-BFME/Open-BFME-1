// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class WindowLayout;

void ReleaseWindowLayout(WindowLayout *layout);

struct ReferenceCountedReleaseValue
{
	virtual void release(int deletingFlag);
	int referenceCount;
};

struct ReferencePointerAssignmentThunk
{
	ReferenceCountedReleaseValue *value;

	__declspec(noinline) ReferencePointerAssignmentThunk *assign(const ReferencePointerAssignmentThunk *other)
	{
		if (this != other)
		{
			ReferenceCountedReleaseValue *newValue = other->value;
			if (newValue != 0)
			{
				++newValue->referenceCount;
			}

			ReferenceCountedReleaseValue *oldValue = value;
			if (oldValue != 0 && --oldValue->referenceCount <= 0)
			{
				oldValue->release(1);
			}

			value = other->value;
		}

		return this;
	}
};

struct ReleaseWindowLayoutTempRef
{
	ReferenceCountedReleaseValue *value;

	ReleaseWindowLayoutTempRef() : value(0) { }
	~ReleaseWindowLayoutTempRef()
	{
		if (value != 0 && --value->referenceCount <= 0)
		{
			value->release(1);
		}
	}
};

struct BfmeOne924G
{
	void bfmeCall924G();
};

struct Rva00579160Manager
{
	unsigned char padding[0x1ae];
	unsigned char flag;
};

class BfmeThingCB
{
public:
	unsigned char padding0[0x34];
	int mode;
	int state;
	ReferencePointerAssignmentThunk current;
	unsigned char padding1[4];
	int index;
	unsigned char padding2;
	unsigned char released;
};

extern void *g_rva012F49D0;

// retail 0x012F19E8: the canonical spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, defined once in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU reads one
// flag through its own Rva00579160Manager view, so it casts at the use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

class ReleaseWindowLayoutShim
{
public:
	static void run(WindowLayout *layout);
};

void ReleaseWindowLayoutShim::run(WindowLayout *layout)
{
	if (g_rva012F49D0 == 0)
	{
		return;
	}

	if (static_cast<BfmeThingCB *>(g_rva012F49D0)->state == 4)
	{
		return;
	}

	static_cast<BfmeThingCB *>(g_rva012F49D0)->state = 4;

	{
		ReleaseWindowLayoutTempRef temp;
		static_cast<BfmeThingCB *>(g_rva012F49D0)->current.assign(reinterpret_cast<const ReferencePointerAssignmentThunk *>(&temp));
	}

	static_cast<BfmeThingCB *>(g_rva012F49D0)->index = -1;

	if (static_cast<BfmeThingCB *>(g_rva012F49D0)->mode != 0 && static_cast<BfmeThingCB *>(g_rva012F49D0)->mode != 3)
	{
		static_cast<BfmeThingCB *>(g_rva012F49D0)->mode = 3;
	}

	if (*reinterpret_cast<unsigned char *>(&layout) != 0)
	{
		static_cast<BfmeThingCB *>(g_rva012F49D0)->released = 1;
	}

	if (g_rva012F19E8WindowManager != 0 && ((Rva00579160Manager *)g_rva012F19E8WindowManager)->flag == 0)
	{
		reinterpret_cast<BfmeOne924G *>(g_rva012F49D0)->bfmeCall924G();
	}
}

void Rva004C5490()
{
	ReleaseWindowLayout(0);
}
