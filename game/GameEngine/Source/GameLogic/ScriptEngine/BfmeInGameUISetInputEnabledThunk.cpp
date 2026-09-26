// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: BfmeInGameUI::setInputEnabled
// Retail 20B: virtual call [vtbl+0x120](bool, this+0x0e); ret 4.

class BfmeInGameUI_setInputEnabled
{
public:
	void setInputEnabled(bool enabled);
	void setEngineInputEnabled(bool enabled);

	// vtable slots 0x00 .. 0x11c, then impl at +0x120.
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6c();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual void v7c();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8c();
	virtual void v90();
	virtual void v94();
	virtual void v98();
	virtual void v9c();
	virtual void va0();
	virtual void va4();
	virtual void va8();
	virtual void vac();
	virtual void vb0();
	virtual void vb4();
	virtual void vb8();
	virtual void vbc();
	virtual void vc0();
	virtual void vc4();
	virtual void vc8();
	virtual void vcc();
	virtual void vd0();
	virtual void vd4();
	virtual void vd8();
	virtual void vdc();
	virtual void ve0();
	virtual void ve4();
	virtual void ve8();
	virtual void vec();
	virtual void vf0();
	virtual void vf4();
	virtual void vf8();
	virtual void vfc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void setInputEnabledImpl(bool enabled, unsigned char *flag);

private:
	char m_pad[9];
	unsigned char m_engineFlag;
	unsigned char m_flag;
};

// ?setInputEnabled@BfmeInGameUI_setInputEnabled@@QAEX_N@Z
void BfmeInGameUI_setInputEnabled::setInputEnabled(bool enabled)
{
	setInputEnabledImpl(enabled, &m_flag);
}

// @?setEngineInputEnabled@BfmeInGameUI_setInputEnabled@@QAEX_N@Z 0x0043B260
void BfmeInGameUI_setInputEnabled::setEngineInputEnabled(bool enabled)
{
	setInputEnabledImpl(enabled, &m_engineFlag);
}
