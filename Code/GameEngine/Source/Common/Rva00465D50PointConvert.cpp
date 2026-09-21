// cl: /O2 /Ob0
// Retail 0x00465D50 (?d_00465d50@@YAXXZ, dump d_00460f80.asm).
// Full control-flow decode (tools/dis_retail.py): thiscall, one stack
// pointer param (a 2-int point), ret 4.
//   1. TheWindowManager->vtbl[0xc0]() (slot 48, no args) returns a window
//      pointer or null.
//   2. If non-null, window->vtbl[thunk j_00010e5b] fills a local 4-int quad
//      (matched Bfme5FortySix.cpp: Gen_00478220::bfmeGet(BfmeQuadDO*)).
//   3. If the point lies inside that quad (left<=x<=right, top<=y<=bottom),
//      call the matched BfmeConv1017::bfmeGo1017X(0, 0) and return.
//   4. Otherwise call this->vtbl[0x2c]() to get a scale object (two floats),
//      convert point.y*scale.y and point.x*scale.x to int (__ftol2, matched
//      Ftol2Thunk.cpp) and call bfmeGo1017X(scaledX, scaledY).
// callees: TheWindowManager global (0x012F1B40), j_00010e5b (thunk to
// matched Bfme5FortySix.cpp), bfmeGo1017X (matched BfmeConv1017.cpp),
// __ftol2 (matched Ftol2Thunk.cpp). No named caller; this-side vtable slot
// 0x2c and the point/quad/scale layouts are address-derived only.

struct Rva00465D50Point
{
	int x;
	int y;
};

// Matches the already-landed Bfme5FortySix.cpp layout exactly, so the call
// below resolves to its real matched ?bfmeGet@Gen_00478220@@QBEHPAVBfmeQuadDO@@@Z
// with no new pin needed.
class BfmeQuadDO
{
public:
	int m_bfmeFirst;
	int m_bfmeSecond;
	int m_bfmeThird;
	int m_bfmeFourth;
};

class Gen_00478220
{
public:
	int bfmeGet(BfmeQuadDO *out) const;

private:
	int m_bfmeHead[5];
	BfmeQuadDO m_bfmeQuad;
};

class GameWindowManager
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void);
	virtual void slot27(void); virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void); virtual void slot32(void);
	virtual void slot33(void); virtual void slot34(void); virtual void slot35(void);
	virtual void slot36(void); virtual void slot37(void); virtual void slot38(void);
	virtual void slot39(void); virtual void slot40(void); virtual void slot41(void);
	virtual void slot42(void); virtual void slot43(void); virtual void slot44(void);
	virtual void slot45(void); virtual void slot46(void); virtual void slot47(void);
	virtual Gen_00478220 *bfmeGetWindow(void);
};

extern GameWindowManager *TheWindowManager;

struct Rva00465D50Scale
{
	float x;
	float y;
};

void __cdecl bfmeGo1017X(int x, int y);

class Rva00465D50Owner
{
public:
	void apply(Rva00465D50Point *point);

	virtual void slot0(void); virtual void slot1(void); virtual void slot2(void);
	virtual void slot3(void); virtual void slot4(void); virtual void slot5(void);
	virtual void slot6(void); virtual void slot7(void); virtual void slot8(void);
	virtual void slot9(void); virtual void slot10(void);
	virtual Rva00465D50Scale *bfmeGetScale(void);
};

void Rva00465D50Owner::apply(Rva00465D50Point *point)
{
	Gen_00478220 *window = TheWindowManager->bfmeGetWindow();

	if (window != 0)
	{
		BfmeQuadDO quad;
		window->bfmeGet(&quad);

		if (point->x >= quad.m_bfmeFirst && point->y >= quad.m_bfmeSecond &&
			point->x <= quad.m_bfmeThird && point->y <= quad.m_bfmeFourth)
		{
			bfmeGo1017X(0, 0);
			return;
		}
	}

	Rva00465D50Scale *scale = bfmeGetScale();
	int y = (int)((float)point->y * scale->y);
	int x = (int)((float)point->x * scale->x);
	bfmeGo1017X(x, y);
}
