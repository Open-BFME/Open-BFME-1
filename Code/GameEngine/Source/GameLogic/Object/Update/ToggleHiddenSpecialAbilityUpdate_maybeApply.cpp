// cl: /DNDEBUG /MD /EHsc
// ToggleHiddenSpecialAbilityUpdate helper at 0x0026C080: if the second
// argument is present and its float at +0x1c is the zero constant, ask
// vtable+0x64 about the kind at +0x10 and on success dispatch vtable+0x54.

extern float g_bfmeZeroCY;

class BfmeZeroFloatArg
{
public:
	char m_pad00[0x10];
	int m_kind;
	char m_pad14[8];
	float m_value;
};

class ToggleHiddenSpecialAbilityUpdate
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void apply(void *arg);
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual bool acceptKind(int kind);

	void maybeApply(void *arg, BfmeZeroFloatArg *other);
};

// ?maybeApply@ToggleHiddenSpecialAbilityUpdate@@QAEXPAXPAVBfmeZeroFloatArg@@@Z
void ToggleHiddenSpecialAbilityUpdate::maybeApply(void *arg, BfmeZeroFloatArg *other)
{
	if (other != 0)
	{
		if (other->m_value != g_bfmeZeroCY)
		{
			if (acceptKind(other->m_kind))
				apply(arg);
		}
	}
}
