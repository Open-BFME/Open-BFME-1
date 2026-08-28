// Seven 17-byte bodies with one shape: call something on this with no
// arguments, then tail-jump into a member sub-object.
//
//     push esi / mov esi, ecx
//     call <first>
//     lea ecx, [esi + disp]
//     pop esi
//     jmp <second>
//
// The lea rather than a load is what says the second callee's object is a
// SUB-OBJECT EMBEDDED at that displacement, not a pointer stored there. Six of
// the seven reach UpdateModule::loadPostProcess for the first call, and a
// qualified base call is how a tail jump to a named base member gets there --
// so those six are loadPostProcess overrides that chain to the base and then
// hand off to their member. The seventh calls a different member entirely.
//
// The displacements differ and one of them is NEGATIVE: five at +0x20, one at
// +0x2C, and one at -0x08. A negative displacement cannot be a member, so that
// last one is a sibling sub-object of the same owner, reached by walking this
// back eight bytes -- which folds into the same single lea.

class Gen_002d9b20
{
public:
	void m(void);							// ILT 0x0002DF5B
};

class Gen_001ef410
{
public:
	void m(void);							// ILT 0x0004049E

	char m_bfmeBody[0x04];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	virtual void loadPostProcess(void);				// ILT 0x00015E0B
};

class Gen_001ee8a0 : public UpdateModule
{
protected:
	virtual void loadPostProcess(void);

private:
	char m_bfmeHead[0x20 - 0x04];
	Gen_002d9b20 m_bfmeSub;						// +0x20
};

class Gen_001fb490 : public UpdateModule
{
protected:
	virtual void loadPostProcess(void);

private:
	char m_bfmeHead[0x20 - 0x04];
	Gen_002d9b20 m_bfmeSub;						// +0x20
};

class Gen_001fbc40
{
public:
	void bfmeReload(void);

private:
	Gen_001ef410 m_bfmeOwn;						// +0x00
	char m_bfmeMid[0x20 - 0x04];
	Gen_002d9b20 m_bfmeSub;						// +0x20
};

class Gen_002043f0 : public UpdateModule
{
protected:
	virtual void loadPostProcess(void);

private:
	char m_bfmeHead[0x20 - 0x04];
	Gen_002d9b20 m_bfmeSub;						// +0x20
};

class Gen_0020a7e0 : public UpdateModule
{
protected:
	virtual void loadPostProcess(void);

private:
	char m_bfmeHead[0x2C - 0x04];
	Gen_002d9b20 m_bfmeSub;						// +0x2C
};

class Gen_002d31b0 : public UpdateModule
{
protected:
	virtual void loadPostProcess(void);

private:
	char m_bfmeHead[0x20 - 0x04];
	Gen_002d9b20 m_bfmeSub;						// +0x20
};

class Gen_002d6c30 : public UpdateModule
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@Gen_001ee8a0@@MAEXXZ
void Gen_001ee8a0::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();

	m_bfmeSub.m();
}

// ?loadPostProcess@Gen_001fb490@@MAEXXZ
void Gen_001fb490::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();

	m_bfmeSub.m();
}

// ?bfmeReload@Gen_001fbc40@@QAEXXZ
void Gen_001fbc40::bfmeReload(void)
{
	m_bfmeOwn.m();

	m_bfmeSub.m();
}

// ?loadPostProcess@Gen_002043f0@@MAEXXZ
void Gen_002043f0::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();

	m_bfmeSub.m();
}

// ?loadPostProcess@Gen_0020a7e0@@MAEXXZ
void Gen_0020a7e0::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();

	m_bfmeSub.m();
}

// ?loadPostProcess@Gen_002d31b0@@MAEXXZ
void Gen_002d31b0::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();

	m_bfmeSub.m();
}

// ?loadPostProcess@Gen_002d6c30@@MAEXXZ
void Gen_002d6c30::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();

	((Gen_002d9b20 *)((char *)this - 0x08))->m();
}
