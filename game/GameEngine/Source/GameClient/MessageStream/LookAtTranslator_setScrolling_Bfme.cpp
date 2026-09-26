// BFME LookAtTranslator::setScrolling body at retail RVA 0x005B51D0.

typedef unsigned char Bool;

class InGameUI
{
public:
	virtual void v00() = 0; virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0; virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0; virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0; virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0; virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0; virtual void v26() = 0; virtual void v27() = 0;
	virtual void v28() = 0; virtual void v29() = 0; virtual void v30() = 0; virtual void v31() = 0;
	virtual void v32() = 0; virtual void v33() = 0; virtual void v34() = 0; virtual void v35() = 0;
	virtual void v36() = 0; virtual void v37() = 0; virtual void v38() = 0; virtual void v39() = 0;
	virtual void setScrolling(Bool value) = 0;

	Bool getInputEnabled() const
	{
		return m_inputEnabled && m_inputAllowed;
	}

private:
	unsigned char m_pad00[0x09];
	Bool m_inputEnabled;
	Bool m_inputAllowed;
};

class View
{
public:
	virtual void v000() = 0; virtual void v004() = 0; virtual void v008() = 0; virtual void v00C() = 0;
	virtual void v010() = 0; virtual void v014() = 0; virtual void v018() = 0; virtual void v01C() = 0;
	virtual void v020() = 0; virtual void v024() = 0; virtual void v028() = 0; virtual void v02C() = 0;
	virtual void v030() = 0; virtual void v034() = 0; virtual void v038() = 0; virtual void v03C() = 0;
	virtual void v040() = 0; virtual void v044() = 0; virtual void v048() = 0; virtual void v04C() = 0;
	virtual void v050() = 0; virtual void v054() = 0; virtual void v058() = 0; virtual void v05C() = 0;
	virtual void v060() = 0; virtual void v064() = 0; virtual void v068() = 0; virtual void v06C() = 0;
	virtual void v070() = 0; virtual void v074() = 0; virtual void v078() = 0; virtual void v07C() = 0;
	virtual void v080() = 0; virtual void v084() = 0; virtual void v088() = 0; virtual void v08C() = 0;
	virtual void v090() = 0; virtual void v094() = 0; virtual void v098() = 0; virtual void v09C() = 0;
	virtual void v0A0() = 0; virtual void v0A4() = 0; virtual void v0A8() = 0; virtual void v0AC() = 0;
	virtual void v0B0() = 0; virtual void v0B4() = 0; virtual void v0B8() = 0; virtual void v0BC() = 0;
	virtual void v0C0() = 0; virtual void v0C4() = 0; virtual void v0C8() = 0; virtual void v0CC() = 0;
	virtual void v0D0() = 0; virtual void v0D4() = 0; virtual void v0D8() = 0; virtual void v0DC() = 0;
	virtual void v0E0() = 0; virtual void v0E4() = 0; virtual void v0E8() = 0; virtual void v0EC() = 0;
	virtual void v0F0() = 0; virtual void v0F4() = 0; virtual void v0F8() = 0; virtual void v0FC() = 0;
	virtual void v100() = 0; virtual void v104() = 0; virtual void v108() = 0; virtual void v10C() = 0;
	virtual void v110() = 0; virtual void v114() = 0; virtual void v118() = 0; virtual void v11C() = 0;
	virtual void v120() = 0; virtual void v124() = 0; virtual void v128() = 0; virtual void v12C() = 0;
	virtual void v130() = 0; virtual void v134() = 0; virtual void v138() = 0; virtual void v13C() = 0;
	virtual void v140() = 0; virtual void v144() = 0; virtual void v148() = 0; virtual void v14C() = 0;
	virtual void v150() = 0; virtual void v154() = 0; virtual void v158() = 0; virtual void v15C() = 0;
	virtual void v160() = 0; virtual void v164() = 0; virtual void v168() = 0; virtual void v16C() = 0;
	virtual void v170() = 0; virtual void v174() = 0; virtual void v178() = 0; virtual void v17C() = 0;
	virtual void v180() = 0; virtual void v184() = 0; virtual void v188() = 0; virtual void v18C() = 0;
	virtual void v190() = 0; virtual void v194() = 0; virtual void v198() = 0; virtual void v19C() = 0;
	virtual void setMouseLock(Bool value) = 0;
	virtual void v1A4() = 0; virtual void v1A8() = 0; virtual void v1AC() = 0; virtual void v1B0() = 0;
	virtual void v1B4() = 0; virtual void v1B8() = 0; virtual void v1BC() = 0; virtual void v1C0() = 0;
	virtual void v1C4() = 0;
	virtual Bool isCameraMovementFinished() = 0;
};

class ClientRoot4120
{
private:
	unsigned char m_pad00[0xBC];

public:
	Bool m_inputBlocked;
};

class Mouse
{
public:
	unsigned char m_pad00[0x4DA8];
	int m_mouseCursor;
};

class StatsCollector
{
public:
	void startScrollTime(void);
};

class LookAtTranslator
{
private:
	void setScrolling(int type);
	unsigned char m_pad00[0x38];
	Bool m_isScrolling;
	Bool m_isRotating;
	unsigned char m_pad3A[0x10E];
	int m_scrollType;
	int m_scrollResult;
};

extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern ClientRoot4120 *TheGameClient;
extern Mouse *TheMouse;
extern StatsCollector *g_bfmeT1095;
extern int (__cdecl *g_bfmeNowVNH)(void);
void j_000174c7(void);

static int g_bfmeV1095;


// ?setScrolling@LookAtTranslator@@AAEXH@Z
void LookAtTranslator::setScrolling(int type)
{
	if (!TheInGameUI->getInputEnabled())
		return;
	if (TheTacticalView->isCameraMovementFinished())
		return;
	if (TheGameClient->m_inputBlocked)
		return;

	g_bfmeV1095 = TheMouse->m_mouseCursor;
	m_isScrolling = true;
	TheInGameUI->setScrolling(1);
	if (!m_isRotating)
	{
		TheTacticalView->setMouseLock(1);
	}

	if (type != m_scrollType)
	{
		m_scrollType = type;
		m_scrollResult = g_bfmeNowVNH();
	}
	if (g_bfmeT1095)
		g_bfmeT1095->startScrollTime();
}
