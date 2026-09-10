// ?drawDisabled@Drawable@@AAEXXZ
// partial score=0.25 date=2026-09-09
// cl: /O2 /Ob1 /DNDEBUG /MD /EHs-c-
// BFME Drawable icon-stage body at retail 0x00420670 (373 bytes).
//
// The icon dispatcher at 0x00420AC0 enters this private no-argument stage
// through ILT 0x00038AAA.  The stage walks the BFME experience iterator and
// then applies the containment guard before handing the level to the Drawable
// rendering helper.  The iterator and the callee aliases below are kept
// address-derived: their retail spellings are not established by this body.

typedef unsigned char Bool;
typedef int Int;

extern void j_0000edc7();
extern void j_0000dfc1();
extern void j_000012a8();
extern void j_0000bc21();
extern void j_00041295();
extern void j_0001fc53();
extern void j_0003251f();
extern void d_00418600();

struct BfmeObject;

struct Rva0037F220Node
{
	Rva0037F220Node *next;
	unsigned char record[0xd8];
};

struct Rva0037F220Iterator
{
	Rva0037F220Node *sentinel;
	Rva0037F220Node *current;
};

class Drawable;

class ExperienceLevelSystem
{
public:
	void getIterator(Rva0037F220Iterator *out, BfmeObject *object);
	Bool iteratorUsable(Rva0037F220Iterator value);
	Int iteratorValueA(Rva0037F220Iterator value);
	Int iteratorValueB(Rva0037F220Iterator value);
	Rva0037F220Iterator iteratorAdvance(Rva0037F220Iterator value);
};

#define THE_EXPERIENCE_LEVEL_SYSTEM \
	(*(ExperienceLevelSystem **)0x012F0888)

union GetIteratorCall
{
	void (*freeFunction)();
	void (ExperienceLevelSystem::*memberFunction)(Rva0037F220Iterator *, BfmeObject *);
};

union IteratorUsableCall
{
	void (*freeFunction)();
	Bool (ExperienceLevelSystem::*memberFunction)(Rva0037F220Iterator);
};

union IteratorValueCall
{
	void (*freeFunction)();
	Int (ExperienceLevelSystem::*memberFunction)(Rva0037F220Iterator);
};

union IteratorAdvanceCall
{
	void (*freeFunction)();
	Rva0037F220Iterator (ExperienceLevelSystem::*memberFunction)(Rva0037F220Iterator);
};

union DrawableRenderCall
{
	void (*freeFunction)();
	void (Drawable::*memberFunction)(Bool, Int);
};

union DrawableQueryCall
{
	void (*freeFunction)();
	Bool (*function)(Drawable *);
};

class BfmeObjectModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e(); virtual void slot0f();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1a(); virtual void slot1b();
	virtual void slot1c(); virtual void slot1d(); virtual void slot1e(); virtual void slot1f();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2a(); virtual void slot2b();
	virtual void slot2c(); virtual void slot2d(); virtual void slot2e(); virtual void slot2f();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot3a(); virtual void slot3b();
	virtual void slot3c(); virtual void *slot3d(); virtual void slot3e();
	virtual void *slot3f();
	virtual void *slot40();
};

class BfmeContainModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e(); virtual void slot0f();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual BfmeObjectModule *slot1aObject();
};

struct BfmeObject
{
	unsigned char pad000[0x1fc];
	BfmeContainModule *contain;
	unsigned char pad200[0x210 - 0x200];
	void *experience;
	unsigned char pad214[4];
	BfmeObject *containedBy;

	Bool askAIA(Int kind);
};

union AskAiaCall
{
	void (*freeFunction)();
	Bool (BfmeObject::*memberFunction)(Int);
};

class Drawable
{
public:
	virtual void slot00();

private:
	void drawDisabled();
	unsigned char pad004[0xf8];
	BfmeObject *object;
};

static Bool drawableQuery(Drawable *drawable)
{
	DrawableQueryCall call;
	call.freeFunction = d_00418600;
	return call.function(drawable);
}

void Drawable::drawDisabled()
{
	BfmeObject *obj = *(BfmeObject **)((char *)this + 0xfc);
	if (obj == 0)
		return;
	if (obj->experience == 0)
		return;
	AskAiaCall ask;
	ask.freeFunction = j_0003251f;
	if (!((obj->*ask.memberFunction)(0x6c)) &&
		!((obj->*ask.memberFunction)(0x0a)))
		return;

	Rva0037F220Iterator value;
	GetIteratorCall get;
	get.freeFunction = j_0000edc7;
	(THE_EXPERIENCE_LEVEL_SYSTEM->*get.memberFunction)(&value, obj);

	IteratorUsableCall usable;
	usable.freeFunction = j_0000dfc1;
	if (!(THE_EXPERIENCE_LEVEL_SYSTEM->*usable.memberFunction)(value))
		return;

	IteratorValueCall valueA;
	valueA.freeFunction = j_000012a8;
	Int level = (THE_EXPERIENCE_LEVEL_SYSTEM->*valueA.memberFunction)(value);
	if (level <= 1)
		return;

	IteratorValueCall valueB;
	valueB.freeFunction = j_0000bc21;
	if ((THE_EXPERIENCE_LEVEL_SYSTEM->*valueB.memberFunction)(value) <= 1)
	{
		IteratorAdvanceCall advance;
		advance.freeFunction = j_00041295;
		Rva0037F220Iterator next =
			(THE_EXPERIENCE_LEVEL_SYSTEM->*advance.memberFunction)(value);
		if (!(THE_EXPERIENCE_LEVEL_SYSTEM->*usable.memberFunction)(next))
			return;
	}

	Bool query = drawableQuery(this);
	if ((obj->*ask.memberFunction)(0x6c))
	{
		BfmeObjectModule *module = obj->contain ? obj->contain->slot1aObject() : 0;
		if (module != 0)
		{
			if (module->slot3f() == 0)
			{
				BfmeObjectModule *child =
					(BfmeObjectModule *)module->slot3d();
				if (child == 0)
					return;
				child->slot0a();
				goto render;
			}
		}
	}

	if (obj->containedBy != 0 &&
		(obj->containedBy->*ask.memberFunction)(0x6c))
		return;

render:
	DrawableRenderCall renderCall;
	renderCall.freeFunction = j_0001fc53;
	if (this != 0)
		(this->*renderCall.memberFunction)(query, level);
}
