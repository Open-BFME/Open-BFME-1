// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
//
// BezierProjectileBehavior secondary-interface slot 3, retail 0x001F1CE0,
// 296 bytes.  The semantic slot name is not yet proven, so the method keeps
// the address-derived identity.  Its this pointer is the +0x20 interface;
// the complete class has the 12-byte path vector at module +0x44 and the
// circular record list at module +0x7C (the constructor/destructor evidence
// is in the neighboring landed Bezier sources).

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_unreconstructed00[0x38];
	Coord3D m_position;
	char m_unreconstructed44[0x74 - 0x44];
	int m_id;
};

class BfmeThingDI;

class BfmeThingCOF
{
public:
	Bool bfmeAskCOF();
	void bfmeRunCOF(void *a, void *b, void *c, void *d);
};

class ObjectCreationListStore
{
public:
	void bfmeCreate(void *owner, Object *object, void *position);
};

extern ObjectCreationListStore *TheObjectCreationListStore;

class Gen_001EFD20
{
public:
	Bool bfmeIsNew(const BfmeThingDI *thing) const;
};

class BezierProjectileBehaviorModuleData
{
public:
	char m_unreconstructed00[0x18];
	Bool m_killInsteadOfDestroy;
	char m_unreconstructed19[3];
	int m_effectFrame;
	char m_unreconstructed20[0x94 - 0x20];
	BfmeThingCOF *m_effect94;
	BfmeThingCOF *m_effect98;
	BfmeThingCOF *m_effect9C;
	BfmeThingCOF *m_effectA0;
};

class Rva001F01D0
{
public:
	void fireAndRecord(Object *target);
};

class BezierPathPod
{
	int m_values[3];
};

class BezierProjectileBehavior
{
public:
	void rva001EFB20(Object *target);
	void projectileFire();
	void rva001F1B90(Bool flag);
	void rva001F1620(Bool flag);
	Bool rva001F1CE0(Object *other);

private:
	char m_unreconstructed00[0x24];
	BezierPathPod *m_pathBegin;
	BezierPathPod *m_pathEnd;
};

// Neighboring primary-object helpers are independently pinned retail callees.
// Their declarations preserve the proven Object-pointer or boolean argument.

// ?rva001F1CE0@BezierProjectileBehavior@@QAE_NPAVObject@@@Z
Bool BezierProjectileBehavior::rva001F1CE0(Object *other)
{
	int pathCount = (int)(m_pathEnd - m_pathBegin);
	if (pathCount == 0)
		return false;

	Object *object = *(Object **)((char *)this - 0x18);
	BezierProjectileBehaviorModuleData *data =
		*(BezierProjectileBehaviorModuleData **)((char *)this - 0x1C);

	if (other != 0)
	{
		((BezierProjectileBehavior *)((char *)this - 0x20))->rva001EFB20(other);
		if (!data->m_killInsteadOfDestroy)
			((BezierProjectileBehavior *)((char *)this - 0x20))->projectileFire();
		else if (((Gen_001EFD20 *)((char *)this - 0x20))->bfmeIsNew(
				(const BfmeThingDI *)other))
			((Rva001F01D0 *)((char *)this - 0x20))->fireAndRecord(other);
		return true;
	}

	if (*(int *)((char *)this + 0x58) == 0)
	{
		BfmeThingCOF *effect = data->m_effect94;
		if (effect != 0 && !effect->bfmeAskCOF())
			effect->bfmeRunCOF(&object->m_position, 0, 0, 0);

		BfmeThingCOF *ocl = data->m_effect9C;
		if (ocl != 0)
		{
			Coord3D *position = &object->m_position;
			TheObjectCreationListStore->bfmeCreate(ocl, object, position);
		}
	}
	else
	{
		BfmeThingCOF *effect = data->m_effect98;
		if (effect != 0 && !effect->bfmeAskCOF())
			effect->bfmeRunCOF(&object->m_position, 0, 0, 0);

		effect = data->m_effectA0;
		if (effect != 0)
		{
			Coord3D *position = &object->m_position;
			TheObjectCreationListStore->bfmeCreate(effect, object, position);
		}
	}

	if (*(int *)((char *)this + 0x58) < data->m_effectFrame)
	{
		((BezierProjectileBehavior *)((char *)this - 0x20))->rva001F1B90(false);
		return true;
	}

	if (!data->m_killInsteadOfDestroy)
		((BezierProjectileBehavior *)((char *)this - 0x20))->projectileFire();
	else
		((BezierProjectileBehavior *)((char *)this - 0x20))->rva001F1620(false);
	return true;
}
