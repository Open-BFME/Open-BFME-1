// ?apply@Gen0075BC60@@QAEXPAVGen0075BC60Arg@@E@Z
// partial score=0.85 date=2026-09-02
// 0x0075BC60 -- if the argument object exists, fetch a helper through vtable
// slot 0x84 (passing 0 and this+8), then vtable slot 0x190 with the flag, then
// release when the refcount hits zero.
//
//     mov bl,flag / test bl,bl / jne $+0 / test arg / je end /
//     helper = arg->v84(0, this->m_08) / helper->v190(flag) / Release

class Gen0075BC60Helper
{
public:
	virtual void dispose(void);
	int m_refs;

	virtual void v04(void);
	virtual void v08(void);
	virtual void v0C(void);
	virtual void v10(void);
	virtual void v14(void);
	virtual void v18(void);
	virtual void v1C(void);
	virtual void v20(void);
	virtual void v24(void);
	virtual void v28(void);
	virtual void v2C(void);
	virtual void v30(void);
	virtual void v34(void);
	virtual void v38(void);
	virtual void v3C(void);
	virtual void v40(void);
	virtual void v44(void);
	virtual void v48(void);
	virtual void v4C(void);
	virtual void v50(void);
	virtual void v54(void);
	virtual void v58(void);
	virtual void v5C(void);
	virtual void v60(void);
	virtual void v64(void);
	virtual void v68(void);
	virtual void v6C(void);
	virtual void v70(void);
	virtual void v74(void);
	virtual void v78(void);
	virtual void v7C(void);
	virtual void v80(void);
	virtual void v84(void);
	virtual void v88(void);
	virtual void v8C(void);
	virtual void v90(void);
	virtual void v94(void);
	virtual void v98(void);
	virtual void v9C(void);
	virtual void vA0(void);
	virtual void vA4(void);
	virtual void vA8(void);
	virtual void vAC(void);
	virtual void vB0(void);
	virtual void vB4(void);
	virtual void vB8(void);
	virtual void vBC(void);
	virtual void vC0(void);
	virtual void vC4(void);
	virtual void vC8(void);
	virtual void vCC(void);
	virtual void vD0(void);
	virtual void vD4(void);
	virtual void vD8(void);
	virtual void vDC(void);
	virtual void vE0(void);
	virtual void vE4(void);
	virtual void vE8(void);
	virtual void vEC(void);
	virtual void vF0(void);
	virtual void vF4(void);
	virtual void vF8(void);
	virtual void vFC(void);
	virtual void v100(void);
	virtual void v104(void);
	virtual void v108(void);
	virtual void v10C(void);
	virtual void v110(void);
	virtual void v114(void);
	virtual void v118(void);
	virtual void v11C(void);
	virtual void v120(void);
	virtual void v124(void);
	virtual void v128(void);
	virtual void v12C(void);
	virtual void v130(void);
	virtual void v134(void);
	virtual void v138(void);
	virtual void v13C(void);
	virtual void v140(void);
	virtual void v144(void);
	virtual void v148(void);
	virtual void v14C(void);
	virtual void v150(void);
	virtual void v154(void);
	virtual void v158(void);
	virtual void v15C(void);
	virtual void v160(void);
	virtual void v164(void);
	virtual void v168(void);
	virtual void v16C(void);
	virtual void v170(void);
	virtual void v174(void);
	virtual void v178(void);
	virtual void v17C(void);
	virtual void v180(void);
	virtual void v184(void);
	virtual void v188(void);
	virtual void v18C(void);
	virtual void v190(unsigned char flag);
};

class Gen0075BC60Arg
{
public:
	virtual void dispose(void);
	virtual void v04(void);
	virtual void v08(void);
	virtual void v0C(void);
	virtual void v10(void);
	virtual void v14(void);
	virtual void v18(void);
	virtual void v1C(void);
	virtual void v20(void);
	virtual void v24(void);
	virtual void v28(void);
	virtual void v2C(void);
	virtual void v30(void);
	virtual void v34(void);
	virtual void v38(void);
	virtual void v3C(void);
	virtual void v40(void);
	virtual void v44(void);
	virtual void v48(void);
	virtual void v4C(void);
	virtual void v50(void);
	virtual void v54(void);
	virtual void v58(void);
	virtual void v5C(void);
	virtual void v60(void);
	virtual void v64(void);
	virtual void v68(void);
	virtual void v6C(void);
	virtual void v70(void);
	virtual void v74(void);
	virtual void v78(void);
	virtual void v7C(void);
	virtual void v80(void);
	virtual Gen0075BC60Helper *v84(int zero, void *held);
};

class Gen0075BC60
{
public:
	void apply(Gen0075BC60Arg *arg, unsigned char flag);

private:
	char m_pad[8];
	void *m_08;
};

// ?apply@Gen0075BC60@@QAEXPAVGen0075BC60Arg@@E@Z
void Gen0075BC60::apply(Gen0075BC60Arg *arg, unsigned char flag)
{
	unsigned char shown = flag;
	Gen0075BC60Helper *helper;

	if (arg)
	{
		helper = arg->v84(0, m_08);

		if (helper)
		{
			helper->v190(shown);

			if (--helper->m_refs == 0)
				helper->dispose();
		}
	}
}
