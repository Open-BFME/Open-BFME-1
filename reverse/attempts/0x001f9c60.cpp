// ?run@Rva001F9C60UpdateModule@@QAEXXZ
// partial score=0.56 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail 0x001F9C60: an UpdateModule-interface method whose receiver is an
// interior pointer (multiple-inheritance layout not modelled; sibling
// fields at this-0x8, this-0xc, this-0x10 are read with raw pointer
// arithmetic, matching the established idiom in Rva002D55F0Teardown.cpp
// and BfmeConv1308.cpp). It initialises its TCB base, gets
// Object::getDrawable, forwards a nonempty module-name string through the
// 0x00414230 guarded drawable dispatch, reclassifies the object in the AI
// pathfinder, calls a second TCB-family base method, and finally queries
// the object's projectile update interface. No named caller or owning
// module survived one prior pass, so every name keeps its address token.

class BfmeBaseTCB
{
public:
	void bfmeInitTCB();
};

class BfmeBaseFW
{
public:
	void bfmeDoFW();
};

class Drawable;
class ProjectileUpdateInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
// (m_field74 and m_ai@0x204 witnessed here; getDrawable at slot 10 per
// Rva00419E40DrawablePredicate.cpp and siblings)
class Object
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot01();
	virtual void bfmeSlot02();
	virtual void bfmeSlot03();
	virtual void bfmeSlot04();
	virtual void bfmeSlot05();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual Drawable *getDrawable() const;

	ProjectileUpdateInterface *getProjectileUpdateInterface() const;

	unsigned char m_unmodelled_004[0x74 - 4];
	void *m_field74;
	unsigned char m_unmodelled_078[0x204 - 0x78];
	void *m_ai;
};

class ProjectileUpdateInterface
{
public:
	virtual void puiSlot0();
	virtual void puiSlot1();
	virtual void puiSlot2(void *arg);
};

// Already-landed guarded virtual forwarder; companion class per body, kept
// declaration-only here to link against the existing definition.
class Rva00414230GuardedVCall
{
public:
	void forward(int a0);
};

extern const char Rva006A16B0Empty[];

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct AsciiStringData
{
	int m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numTrueMBChars;
};

__forceinline const char *bfmeEffectiveStr(AsciiStringData *data)
{
	return data ? (const char *)data + 8 : Rva006A16B0Empty;
}

__forceinline int bfmeGetLength(AsciiStringData *data)
{
	return data ? data->m_numCharsAllocated : 0;
}

class UpdateModuleName
{
public:
	AsciiStringData *m_data;
};

struct UpdateModuleData
{
	unsigned char m_unmodelled_000[0xc0];
	UpdateModuleName m_moduleName;
};

class BfmeHostCL;

class BfmePathCL
{
public:
	void bfmeDropOneCL(BfmeHostCL *o);
};

class AI
{
public:
	unsigned char m_bfmeHeadCL[0xc];
	BfmePathCL *m_bfmePathCL;
};

extern AI *TheAI;

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

class Rva001F9C60UpdateModule
{
public:
	void run(void);
};

void Rva001F9C60UpdateModule::run(void)
{
	((BfmeBaseTCB *)((char *)this - 0x10))->bfmeInitTCB();

	Object *obj = *(Object **)((char *)this - 8);
	Drawable *drawable = obj->getDrawable();

	if (drawable != 0)
	{
		UpdateModuleData *moduleData = *(UpdateModuleData **)((char *)this - 0xc);

		AsciiStringData *name = moduleData->m_moduleName.m_data;

		if (bfmeGetLength(name) > 0)
		{
			_ReadWriteBarrier();
			((Rva00414230GuardedVCall *)drawable)->forward((int)bfmeEffectiveStr(name));
		}
	}

	TheAI->m_bfmePathCL->bfmeDropOneCL((BfmeHostCL *)obj);
	((BFMEPathfinderMapShim *)TheAI->m_bfmePathCL)->addObjectToPathfindMap(obj);

	((BfmeBaseFW *)((char *)this - 0x10))->bfmeDoFW();

	if (obj->m_ai != 0)
	{
		ProjectileUpdateInterface *pui = obj->getProjectileUpdateInterface();
		if (pui != 0)
			pui->puiSlot2(obj->m_field74);
	}
}
