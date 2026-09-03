// ?bfmeGo4D0@Gen_0022F4D0@@QAEXPAX@Z
// partial score=0.91 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F4D0. Multi-stage dispatch with one pass-through
// argument over the same neighborhood as the 0x0022F260 forwarder: init
// through the Gen object, disable-clearing, a no-arg call, a position set
// from the coordinate at obj+0x38, a bare virtual slot-16 call that gates
// everything, a frame computation from TheGameLogic with a guarded
// override walk, a second virtual slot-16 call with a zero whose slot
// stays live for the void set call, and a closing virtual slot-33 call on
// the object at this-0x20. Callees without recovered identities are
// pinned at their thunks; setPosition reuses its existing pin.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing
{
public:
	void setPosition(const Coord3D *p);
};

class GameLogic
{
public:
	char m_pad[0x3C];
	int m_frame;
};

extern GameLogic *TheGameLogic;

class BfmeClear4D0
{
public:
	bool bfmeClear4D0(int x);
};

class BfmeCall4D0
{
public:
	void bfmeCall4D0();
};

class BfmeMid4D0
{
public:
	void *bfmeFinal4D0();
};

class BfmeV10A
{
public:
	virtual void bfmeV00(); virtual void bfmeV01(); virtual void bfmeV02();
	virtual void bfmeV03(); virtual void bfmeV04(); virtual void bfmeV05();
	virtual void bfmeV06(); virtual void bfmeV07(); virtual void bfmeV08();
	virtual void bfmeV09();
	virtual void *bfmeV10A();
};

class BfmeV10B
{
public:
	virtual void bfmeV00(); virtual void bfmeV01(); virtual void bfmeV02();
	virtual void bfmeV03(); virtual void bfmeV04(); virtual void bfmeV05();
	virtual void bfmeV06(); virtual void bfmeV07(); virtual void bfmeV08();
	virtual void bfmeV09();
	virtual void *bfmeV10B(int x);
};

class BfmeV54
{
public:
	virtual void bfmeW00(); virtual void bfmeW01(); virtual void bfmeW02();
	virtual void bfmeW03(); virtual void bfmeW04(); virtual void bfmeW05();
	virtual void bfmeW06(); virtual void bfmeW07(); virtual void bfmeW08();
	virtual void bfmeW09(); virtual void bfmeW10(); virtual void bfmeW11();
	virtual void bfmeW12(); virtual void bfmeW13(); virtual void bfmeW14();
	virtual void bfmeW15(); virtual void bfmeW16(); virtual void bfmeW17();
	virtual void bfmeW18(); virtual void bfmeW19(); virtual void bfmeW20();
	virtual void bfmeV54();
};

class BfmeSet4D0
{
public:
	void bfmeSetVoid4D0();
};

class Gen_0022F4D0
{
public:
	void bfmeGo4D0(void *a);
	void bfmeInit4D0(void *a);
};

// ?bfmeGo4D0@Gen_0022F4D0@@QAEXPAX@Z
void Gen_0022F4D0::bfmeGo4D0(void *a)
{
	bfmeInit4D0(a);
	((BfmeClear4D0 *)a)->bfmeClear4D0(3);
	((BfmeCall4D0 *)a)->bfmeCall4D0();
	((Thing *)a)->setPosition((const Coord3D *)((char *)*(void **)((char *)this - 0x18) + 0x38));
	if (((BfmeV10A *)a)->bfmeV10A() == 0)
		return;
	{
		int frame = TheGameLogic->m_frame;
		void *sub = *(void **)((char *)a + 4);
		if (sub) {
			BfmeMid4D0 *inner = *(BfmeMid4D0 **)((char *)sub + 4);
			if (inner)
				sub = inner->bfmeFinal4D0();
		}
		int v = *(int *)((char *)sub + 0x424);
		v += frame;
		*(int *)((char *)a + 0x330) = v;
	}
	((BfmeSet4D0 *)((BfmeV10B *)a)->bfmeV10B(0))->bfmeSetVoid4D0();
	((BfmeV54 *)((char *)this - 0x20))->bfmeV54();
}
