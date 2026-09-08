// cl: /O2 /Ob2 /GR- /EHsc-
// BFME stores selectability at +0x1ac and passes the collision category as
// the first argument to RenderObjClass::Set_Collision_Type.

class RenderObjClass
{
public:
	virtual void slot000() = 0;
	virtual void slot001() = 0;
	virtual void slot002() = 0;
	virtual void slot003() = 0;
	virtual void slot004() = 0;
	virtual void slot005() = 0;
	virtual void slot006() = 0;
	virtual void slot007() = 0;
	virtual void slot008() = 0;
	virtual void slot009() = 0;
	virtual void slot010() = 0;
	virtual void slot011() = 0;
	virtual void slot012() = 0;
	virtual void slot013() = 0;
	virtual void slot014() = 0;
	virtual void slot015() = 0;
	virtual void slot016() = 0;
	virtual void slot017() = 0;
	virtual void slot018() = 0;
	virtual void slot019() = 0;
	virtual void slot020() = 0;
	virtual void slot021() = 0;
	virtual void slot022() = 0;
	virtual void slot023() = 0;
	virtual void slot024() = 0;
	virtual void slot025() = 0;
	virtual void slot026() = 0;
	virtual void slot027() = 0;
	virtual void slot028() = 0;
	virtual void slot029() = 0;
	virtual void slot030() = 0;
	virtual void slot031() = 0;
	virtual void slot032() = 0;
	virtual void slot033() = 0;
	virtual void slot034() = 0;
	virtual void slot035() = 0;
	virtual void slot036() = 0;
	virtual void slot037() = 0;
	virtual void slot038() = 0;
	virtual void slot039() = 0;
	virtual void slot040() = 0;
	virtual void slot041() = 0;
	virtual void slot042() = 0;
	virtual void slot043() = 0;
	virtual void slot044() = 0;
	virtual void slot045() = 0;
	virtual void slot046() = 0;
	virtual void slot047() = 0;
	virtual void slot048() = 0;
	virtual void slot049() = 0;
	virtual void slot050() = 0;
	virtual void slot051() = 0;
	virtual void slot052() = 0;
	virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual void slot055() = 0;
	virtual void slot056() = 0;
	virtual void slot057() = 0;
	virtual void slot058() = 0;
	virtual void slot059() = 0;
	virtual void slot060() = 0;
	virtual void slot061() = 0;
	virtual void slot062() = 0;
	virtual void slot063() = 0;
	virtual void slot064() = 0;
	virtual void slot065() = 0;
	virtual void slot066() = 0;
	virtual void slot067() = 0;
	virtual void slot068() = 0;
	virtual void slot069() = 0;
	virtual void slot070() = 0;
	virtual void slot071() = 0;
	virtual void slot072() = 0;
	virtual void slot073() = 0;
	virtual void slot074() = 0;
	virtual void slot075() = 0;
	virtual void slot076() = 0;
	virtual void slot077() = 0;
	virtual void slot078() = 0;
	virtual void slot079() = 0;
	virtual void slot080() = 0;
	virtual void slot081() = 0;
	virtual void slot082() = 0;
	virtual void slot083() = 0;
	virtual void slot084() = 0;
	virtual void slot085() = 0;
	virtual void slot086() = 0;
	virtual void slot087() = 0;
	virtual void slot088() = 0;
	virtual void slot089() = 0;
	virtual void slot090() = 0;
	virtual void slot091() = 0;
	virtual void slot092() = 0;
	virtual void slot093() = 0;
	virtual void slot094() = 0;
	virtual void slot095() = 0;
	virtual void slot096() = 0;
	virtual void slot097() = 0;
	virtual void slot098() = 0;
	virtual void slot099() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual int Get_Collision_Type() = 0;
	virtual void Set_Collision_Type(int collisionType, int unknown) = 0;
};

class W3DModelDraw
{
public:
	virtual void setSelectable(bool selectable);

private:
	unsigned char m_pad[0x24];
	RenderObjClass *m_renderObject;
	unsigned char m_middle[0x1ac - 0x2c];
	unsigned int m_selectable;
};

void W3DModelDraw::setSelectable(bool selectable)
{
	m_selectable = selectable;
	if (m_renderObject) {
		int current = m_renderObject->Get_Collision_Type();
		if (selectable)
			current |= 4;
		else
			current &= ~4;
		m_renderObject->Set_Collision_Type(current, 1);
	}
}
