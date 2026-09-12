// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x006C6190 is the +4 slot in the BaseHeightMap cleanup vtable at
// 0x0111D8A4. The cleanup receiver points 0xC8 bytes into the complete object.
// The body reacquires BFME terrain resources through the observed member
// offsets and the existing resource thunks.

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
		thunk.function = TARGET;                                                 \
		(reinterpret_cast<Receiver *>(OBJECT)->*thunk.member)();                  \
	} while (0)

extern void j_000337df(void);
extern void j_000424ab(void);
extern void j_000423d4(void);
extern void j_000357d3(void);
extern void j_0000566e(void);
extern void j_00024d66(void);
extern void j_000129ef(void);
extern void j_0000acd1(void);
extern void j_00020ff9(void);
extern void j_0000bc71(void);
extern void j_00043acc(void);

class VDispatch
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094(); virtual void v095();
	virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109(); virtual void v110(); virtual void v111();
	virtual void v112(); virtual void v113(); virtual void v114(); virtual void v115();
	virtual void v116(); virtual void v117(); virtual void v118(); virtual void v119();
	virtual void v120(); virtual void v121(); virtual void v122(); virtual void v123();
	virtual void v124(); virtual void v125(); virtual void v126(); virtual void v127();
	virtual void v128(); virtual void v129(); virtual void v130(); virtual void v131();
	virtual void v132(int, int, void *, int);
	virtual void v133(); virtual void v134(); virtual void v135(); virtual void v136();
	virtual void v137(); virtual void v138(int);
};

class WorldHeightMap
{
public:
	char m_padding[8];
	int m_width;
	int m_height;
};

class BaseHeightMapRenderObjClass
{
public:
	virtual void ReAcquireResources(void);

private:
	char m_padding2f28[0x2f28];
	WorldHeightMap *m_map;
	char m_padding2f30[0x2fd8 - 0x2f30];
	void *m_treeBuffer;
	void *m_bibBuffer;
	char m_padding2fe0[0x2fe4 - 0x2fe0];
	void *m_bridgeBuffer;
	char m_padding2fe8[0x2fec - 0x2fe8];
	void *m_roadBuffer;
	void *m_shroud;
	void *m_shroudSecondary;
};

class GlobalVirtualResource
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void reacquire();
};

extern GlobalVirtualResource *TheSmudgeManager;

class TacticalView
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void forceRedraw();
};

class Display
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026();
	virtual void update();
};

extern TacticalView *TheTacticalView;
extern Display *TheDisplay;

#define TheTerrainTracks (*(void **)0x012f9d98)
#define TheShadow (*(void **)0x01306eec)
#define TheSnow (*(void **)0x012f15f4)

void BaseHeightMapRenderObjClass::ReAcquireResources(void)
{
	VDispatch *complete = reinterpret_cast<VDispatch *>(reinterpret_cast<char *>(this) - 0xc8);
	complete->v131();

	if (TheTerrainTracks != 0)
		CALL_TARGET(j_000337df, TheTerrainTracks);
	if (TheShadow != 0)
		CALL_TARGET(j_000424ab, TheShadow);
	if (m_shroud != 0)
		CALL_TARGET(j_000423d4, m_shroud);
	if (m_shroudSecondary != 0)
		CALL_TARGET(j_000357d3, m_shroudSecondary);
	if (m_map != 0)
		complete->v132(m_map->m_width, m_map->m_height, m_map, 0);
	if (m_roadBuffer != 0)
		CALL_TARGET(j_0000566e, m_roadBuffer);
	if (m_treeBuffer != 0)
		CALL_TARGET(j_00024d66, m_treeBuffer);
	if (m_bibBuffer != 0)
		CALL_TARGET(j_000129ef, m_bibBuffer);
	if (TheSmudgeManager != 0)
		TheSmudgeManager->reacquire();
	if (TheSnow != 0)
		CALL_TARGET(j_0000acd1, TheSnow);
	if (m_bridgeBuffer != 0)
	{
		CALL_TARGET(j_00020ff9, m_bridgeBuffer);
		CALL_TARGET(j_0000bc71, m_bridgeBuffer);
	}
	if (m_map != 0)
		complete->v138(1);
	if (TheTacticalView != 0)
	{
		TheTacticalView->forceRedraw();
		TheTacticalView->forceRedraw();
	}
	j_00043acc();
	if (TheDisplay != 0)
		TheDisplay->update();
}
