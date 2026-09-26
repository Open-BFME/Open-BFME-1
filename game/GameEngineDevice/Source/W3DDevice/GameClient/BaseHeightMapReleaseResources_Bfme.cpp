// cl: /DNDEBUG /MD /EHsc

typedef void (*FreeFunction)(void);

class Receiver
{
};

#define CALL_TARGET(TARGET, OBJECT)                                           \
	do                                                                          \
	{                                                                           \
		typedef void (Receiver::*MemberFunction)(void);                          \
		union                                                                     \
		{                                                                         \
			FreeFunction function;                                                 \
			MemberFunction member;                                                 \
		} thunk;                                                                  \
		thunk.function = TARGET;                                                  \
		(reinterpret_cast<Receiver *>(OBJECT)->*thunk.member)();                  \
	} while (0)

extern void j_0002b2bf(void);
extern void j_0000e683(void);
extern void j_000269a4(void);
extern void j_000315f2(void);
extern void j_0003445f(void);
extern void j_00009b60(void);
extern void j_0003552b(void);
extern void j_0000aa4c(void);
extern void j_0004a27d(void);
extern void j_000272ff(void);
extern void j_0004840a(void);
extern void j_000491c5(void);
extern void j_0004379d(void);
extern void j_00043469(void);

class WorldHeightMap
{
public:
	virtual void anchor(void);

	void Add_Ref(void)
	{
		++m_refCount;
	}

private:
	int m_refCount;
};

#define REF_PTR_SET(DST, SRC)                                                  \
	{                                                                           \
		if (SRC)                                                                  \
			(SRC)->Add_Ref();                                                       \
		(DST) = (SRC);                                                            \
	}

class CompleteObjectDispatch
{
public:
	virtual void slot000(void); virtual void slot001(void); virtual void slot002(void);
	virtual void slot003(void); virtual void slot004(void); virtual void slot005(void);
	virtual void slot006(void); virtual void slot007(void); virtual void slot008(void);
	virtual void slot009(void); virtual void slot010(void); virtual void slot011(void);
	virtual void slot012(void); virtual void slot013(void); virtual void slot014(void);
	virtual void slot015(void); virtual void slot016(void); virtual void slot017(void);
	virtual void slot018(void); virtual void slot019(void); virtual void slot020(void);
	virtual void slot021(void); virtual void slot022(void); virtual void slot023(void);
	virtual void slot024(void); virtual void slot025(void); virtual void slot026(void);
	virtual void slot027(void); virtual void slot028(void); virtual void slot029(void);
	virtual void slot030(void); virtual void slot031(void); virtual void slot032(void);
	virtual void slot033(void); virtual void slot034(void); virtual void slot035(void);
	virtual void slot036(void); virtual void slot037(void); virtual void slot038(void);
	virtual void slot039(void); virtual void slot040(void); virtual void slot041(void);
	virtual void slot042(void); virtual void slot043(void); virtual void slot044(void);
	virtual void slot045(void); virtual void slot046(void); virtual void slot047(void);
	virtual void slot048(void); virtual void slot049(void); virtual void slot050(void);
	virtual void slot051(void); virtual void slot052(void); virtual void slot053(void);
	virtual void slot054(void); virtual void slot055(void); virtual void slot056(void);
	virtual void slot057(void); virtual void slot058(void); virtual void slot059(void);
	virtual void slot060(void); virtual void slot061(void); virtual void slot062(void);
	virtual void slot063(void); virtual void slot064(void); virtual void slot065(void);
	virtual void slot066(void); virtual void slot067(void); virtual void slot068(void);
	virtual void slot069(void); virtual void slot070(void); virtual void slot071(void);
	virtual void slot072(void); virtual void slot073(void); virtual void slot074(void);
	virtual void slot075(void); virtual void slot076(void); virtual void slot077(void);
	virtual void slot078(void); virtual void slot079(void); virtual void slot080(void);
	virtual void slot081(void); virtual void slot082(void); virtual void slot083(void);
	virtual void slot084(void); virtual void slot085(void); virtual void slot086(void);
	virtual void slot087(void); virtual void slot088(void); virtual void slot089(void);
	virtual void slot090(void); virtual void slot091(void); virtual void slot092(void);
	virtual void slot093(void); virtual void slot094(void); virtual void slot095(void);
	virtual void slot096(void); virtual void slot097(void); virtual void slot098(void);
	virtual void slot099(void); virtual void slot100(void); virtual void slot101(void);
	virtual void slot102(void); virtual void slot103(void); virtual void slot104(void);
	virtual void slot105(void); virtual void slot106(void); virtual void slot107(void);
	virtual void slot108(void); virtual void slot109(void); virtual void slot110(void);
	virtual void slot111(void); virtual void slot112(void); virtual void slot113(void);
	virtual void slot114(void); virtual void slot115(void); virtual void slot116(void);
	virtual void slot117(void); virtual void slot118(void); virtual void slot119(void);
	virtual void slot120(void); virtual void slot121(void); virtual void slot122(void);
	virtual void slot123(void); virtual void slot124(void); virtual void slot125(void);
	virtual void slot126(void); virtual void slot127(void); virtual void slot128(void);
	virtual void slot129(void); virtual void slot130(void); virtual void slot131(void);
	virtual void slot132(void); virtual void slot133(void); virtual void slot134(void);
};

class GlobalDispatch
{
public:
	virtual void slot000(void); virtual void slot001(void); virtual void slot002(void);
	virtual void slot003(void); virtual void slot004(void); virtual void slot005(void);
	virtual void slot006(void); virtual void slot007(void); virtual void slot008(void);
	virtual void slot009(void); virtual void slot010(void); virtual void slot011(void);
	virtual void slot012(void); virtual void slot013(void); virtual void slot014(void);
	virtual void slot015(void); virtual void slot016(void); virtual void slot017(void);
	virtual void slot018(void); virtual void slot019(void); virtual void slot020(void);
	virtual void slot021(void); virtual void slot022(void); virtual void slot023(void);
	virtual void slot024(void); virtual void slot025(void); virtual void slot026(void);
};

#define TheTerrainTracks (*(void **)0x012F9D98)
#define TheShadow (*(void **)0x01306EEC)
#define TheWater (*(GlobalDispatch **)0x012F9D88)
#define TheSnow (*(void **)0x012F15F4)
#define TheSmudge (*(GlobalDispatch **)0x012F12CC)
#define TheDisplay (*(GlobalDispatch **)0x012F1270)

class BaseHeightMapRenderObjClass
{
public:
	virtual void ReleaseResources(void);

private:
	unsigned char m_pad0004[0x2F2C - 4];
	WorldHeightMap *m_map;                                    // +0x2F2C
	unsigned char m_pad2F30[0x2FD8 - 0x2F30];
	void *m_2FD8;
	void *m_2FDC;
	void *m_2FE0;
	void *m_2FE4;
	void *m_2FE8;
	void *m_2FEC;
	void *m_shroud;                                           // +0x2FF0
	void *m_shroudSecondary;                                  // +0x2FF4
};

// ?ReleaseResources@BaseHeightMapRenderObjClass@@UAEXXZ
void BaseHeightMapRenderObjClass::ReleaseResources(void)
{
	if (m_2FEC)
		CALL_TARGET(j_0002b2bf, m_2FEC);
	if (m_2FD8)
		CALL_TARGET(j_0000e683, m_2FD8);
	if (m_2FE8)
		CALL_TARGET(j_000269a4, m_2FE8);
	if (m_2FDC)
		CALL_TARGET(j_000315f2, m_2FDC);
	if (m_2FE0)
		CALL_TARGET(j_0003445f, m_2FE0);

	WorldHeightMap *pMap = 0;
	REF_PTR_SET(pMap, m_map);
	CompleteObjectDispatch *complete =
		reinterpret_cast<CompleteObjectDispatch *>(
			reinterpret_cast<unsigned char *>(this) - 0xC8);
	complete->slot134();
	m_map = pMap;

	if (TheTerrainTracks)
		CALL_TARGET(j_00009b60, TheTerrainTracks);
	if (TheShadow)
		CALL_TARGET(j_0003552b, TheShadow);
	if (m_shroud)
	{
		CALL_TARGET(j_0000aa4c, m_shroud);
		CALL_TARGET(j_0004a27d, m_shroud);
	}
	if (m_shroudSecondary)
	{
		CALL_TARGET(j_000272ff, m_shroudSecondary);
		CALL_TARGET(j_0004840a, m_shroudSecondary);
	}
	GlobalDispatch *water = TheWater;
	if (water)
		water->slot003();
	if (TheSnow)
		CALL_TARGET(j_000491c5, TheSnow);
	GlobalDispatch *smudge = TheSmudge;
	if (smudge)
		smudge->slot004();
	j_0004379d();
	if (m_2FE4)
		CALL_TARGET(j_00043469, m_2FE4);
	GlobalDispatch *display = TheDisplay;
	if (display)
		display->slot026();
	complete->slot130();
}
