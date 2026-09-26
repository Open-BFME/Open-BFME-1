// ?bfmeGoCB@BfmeThingCB@@QAEXE@Z
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS

typedef unsigned char BfmeBool;

class BfmeThingCBTarget
{
public:
	virtual void slot000(BfmeBool);
	virtual void slot001(BfmeBool);
	virtual void slot002(BfmeBool);
	virtual void slot003(BfmeBool);
	virtual void slot004(BfmeBool);
	virtual void slot005(BfmeBool);
	virtual void slot006(BfmeBool);
	virtual void slot007(BfmeBool);
	virtual void slot008(BfmeBool);
	virtual void slot009(BfmeBool);
	virtual void slot010(BfmeBool);
	virtual void slot011(BfmeBool);
	virtual void slot012(BfmeBool);
	virtual void slot013(BfmeBool);
	virtual void slot014(BfmeBool);
	virtual void slot015(BfmeBool);
	virtual void slot016(BfmeBool);
	virtual void slot017(BfmeBool);
	virtual void slot018(BfmeBool);
	virtual void slot019(BfmeBool);
	virtual void slot020(BfmeBool);
	virtual void slot021(BfmeBool);
	virtual void slot022(BfmeBool);
	virtual void slot023(BfmeBool);
	virtual void slot024(BfmeBool);
	virtual void slot025(BfmeBool);
	virtual void slot026(BfmeBool);
	virtual void slot027(BfmeBool);
	virtual void slot028(BfmeBool);
	virtual void slot029(BfmeBool);
	virtual void slot030(BfmeBool);
	virtual void slot031(BfmeBool);
	virtual void slot032(BfmeBool);
	virtual void slot033(BfmeBool);
	virtual void slot034(BfmeBool);
	virtual void slot035(BfmeBool);
	virtual void slot036(BfmeBool);
	virtual void slot037(BfmeBool);
	virtual void slot038(BfmeBool);
	virtual void slot039(BfmeBool);
	virtual void slot040(BfmeBool);
	virtual void slot041(BfmeBool);
	virtual void slot042(BfmeBool);
	virtual void slot043(BfmeBool);
	virtual void slot044(BfmeBool);
	virtual void slot045(BfmeBool);
	virtual void slot046(BfmeBool);
	virtual void slot047(BfmeBool);
	virtual void slot048(BfmeBool);
	virtual void slot049(BfmeBool);
	virtual void slot050(BfmeBool);
	virtual void slot051(BfmeBool);
	virtual void slot052(BfmeBool);
	virtual void slot053(BfmeBool);
	virtual void slot054(BfmeBool);
	virtual void slot055(BfmeBool);
	virtual void slot056(BfmeBool);
	virtual void slot057(BfmeBool);
	virtual void slot058(BfmeBool);
	virtual void slot059(BfmeBool);
	virtual void slot060(BfmeBool);
	virtual void slot061(BfmeBool);
	virtual void slot062(BfmeBool);
	virtual void slot063(BfmeBool);
	virtual void slot064(BfmeBool);
	virtual void slot065(BfmeBool);
	virtual void slot066(BfmeBool);
	virtual void slot067(BfmeBool);
	virtual void slot068(BfmeBool);
	virtual void slot069(BfmeBool);
	virtual void slot070(BfmeBool);
	virtual void slot071(BfmeBool);
	virtual void slot072(BfmeBool);
	virtual void slot073(BfmeBool);
	virtual void slot074(BfmeBool);
	virtual void slot075(BfmeBool);
	virtual void slot076(BfmeBool);
	virtual void slot077(BfmeBool);
	virtual void slot078(BfmeBool);
	virtual void slot079(BfmeBool);
	virtual void slot080(BfmeBool);
	virtual void slot081(BfmeBool);
	virtual void slot082(BfmeBool);
	virtual void slot083(BfmeBool);
	virtual void slot084(BfmeBool);
	virtual void slot085(BfmeBool);
	virtual void slot086(BfmeBool);
	virtual void slot087(BfmeBool);
	virtual void slot088(BfmeBool);
	virtual void slot089(BfmeBool);
	virtual void slot090(BfmeBool);
	virtual void slot091(BfmeBool);
	virtual void slot092(BfmeBool);
	virtual void slot093(BfmeBool);
	virtual void slot094(BfmeBool);
	virtual void slot095(BfmeBool);
	virtual void slot096(BfmeBool);
	virtual void slot097(BfmeBool);
	virtual void slot098(BfmeBool);
	virtual void slot099(BfmeBool);
	virtual void slot100(int);
	virtual void slot101(BfmeBool);
	virtual void slot102(BfmeBool);
	virtual void slot103(BfmeBool);
	virtual int slot104(int);
};

class BfmeThingCB
{
protected:
	char m_pad00[0x0c];
	BfmeThingCBTarget *m_target;

public:
	void bfmeGoCB(BfmeBool flag);
};

void BfmeThingCB::bfmeGoCB(BfmeBool flag)
{
	if (m_target)
	{
		register BfmeBool value = flag;
		m_target->slot104(!value);
		return m_target->slot100(value);
	}
}
