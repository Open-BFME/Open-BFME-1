// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Coord3D007AE900 { float x, y, z; };

class BfmeHolderNS
{
public:
	int bfmeQueryNS(void);
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0AAE();
	virtual void bfmeSlot1AAE();
	virtual void bfmeSlot2AAE();
	virtual void bfmeSlot3AAE();
	virtual void bfmeSlot4AAE();
	virtual void bfmeSlot5AAE();
	virtual void bfmeSlot6AAE();
	virtual float bfmeHeightAAE(float x, float y, int layer, Coord3D007AE900 *normal, int clip);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const float BfmeZeroRange;

#define G_BFME_007AE900_BIAS (*(const float *)0x0109B46C)

// Slot cap only: this reaches the retail vtable slot 0x158 (index 86) that
// 0x007AE900 calls twice on its incoming object; slots 0..85 are unproven
// filler, and the real slot returns an opaque pointer chain the body walks
// through +4 then +0xfc to reach a BfmeHolderNS.
struct Rva007AE900Src
{
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void slot4(void);
	virtual void slot5(void);
	virtual void slot6(void);
	virtual void slot7(void);
	virtual void slot8(void);
	virtual void slot9(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void slot47(void);
	virtual void slot48(void);
	virtual void slot49(void);
	virtual void slot50(void);
	virtual void slot51(void);
	virtual void slot52(void);
	virtual void slot53(void);
	virtual void slot54(void);
	virtual void slot55(void);
	virtual void slot56(void);
	virtual void slot57(void);
	virtual void slot58(void);
	virtual void slot59(void);
	virtual void slot60(void);
	virtual void slot61(void);
	virtual void slot62(void);
	virtual void slot63(void);
	virtual void slot64(void);
	virtual void slot65(void);
	virtual void slot66(void);
	virtual void slot67(void);
	virtual void slot68(void);
	virtual void slot69(void);
	virtual void slot70(void);
	virtual void slot71(void);
	virtual void slot72(void);
	virtual void slot73(void);
	virtual void slot74(void);
	virtual void slot75(void);
	virtual void slot76(void);
	virtual void slot77(void);
	virtual void slot78(void);
	virtual void slot79(void);
	virtual void slot80(void);
	virtual void slot81(void);
	virtual void slot82(void);
	virtual void slot83(void);
	virtual void slot84(void);
	virtual void slot85(void);
	virtual void *bfmeGetChain007AE900(void) const;
};

// ?d_007ae900@@YAXXZ
// Custom register convention (eax=obj, ebx=input ground position, esi=output
// normal), single caller inside the still-dumped carved body at 0x007B23F0.
static float Rva007AE900Body(Rva007AE900Src *obj, const Coord3D007AE900 *groundPos, Coord3D007AE900 *outNormal)
{
	if (obj)
	{
		void *r1 = obj->bfmeGetChain007AE900();
		if (r1)
		{
			void *r2 = obj->bfmeGetChain007AE900();
			void *field = *(void **)((char *)r2 + 4);
			BfmeHolderNS *holder = *(BfmeHolderNS **)((char *)field + 0xfc);
			if (holder)
			{
				int ns = holder->bfmeQueryNS();
				if (ns != 1)
				{
					if (TheTerrainLogic)
					{
						Coord3D007AE900 tmp;
						float h = TheTerrainLogic->bfmeHeightAAE(groundPos->x, groundPos->y, ns, &tmp, 1);
						h += G_BFME_007AE900_BIAS;
						*outNormal = tmp;
						return h;
					}
				}
			}
		}
	}

	float defaultResult = BfmeZeroRange;
	outNormal->x = 0.0f;
	outNormal->y = 0.0f;
	outNormal->z = 1.0f;
	return defaultResult;
}

// TU-local caller: not present in retail (the real caller is the still-dumped
// 0x007B23F0 body). Present only so MSVC 7.1 sees a single call site and can
// choose the eax/ebx/esi register convention the retail body expects.
// absent-from-retail
float Rva007AE900Caller(Rva007AE900Src *obj, const Coord3D007AE900 *pos, Coord3D007AE900 *normal)
{
	return Rva007AE900Body(obj, pos, normal);
}
