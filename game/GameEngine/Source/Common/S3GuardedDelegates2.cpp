// Seven more one-line wrappers: 0x001BF490, 0x001BF4B0, 0x001BF4D0 and
// 0x001BF4F0, then 0x0037DF60, 0x0052F050 and 0x00574F40.
//
// The first four are the void-returning form of the guarded delegate. There is
// no xor al,al because nothing is returned -- the guard simply falls through
// to ret 4 -- and the pointer they test lives at +0x1E8.
//
// The last three are the other direction: a __stdcall free function that turns
// its first stack argument into a this and hands the second one on. It cannot
// tail-jump because it owns eight bytes of arguments while the member it calls
// owns four, so it calls and then rets 8.

class Gen_001BF490Target
{
public:
	void bfmeForward(void *a);				// ILT 0x000138EF
};

class Gen_001BF4B0Target
{
public:
	void bfmeForward(void *a);				// ILT 0x0003DE5B
};

class Gen_001BF4D0Target
{
public:
	void bfmeForward(void *a);				// ILT 0x0000FD35
};

class Gen_001BF4F0Target
{
public:
	void bfmeForward(void *a);				// ILT 0x00040E17
};

class Gen_001BF490
{
public:
	void bfmeForward(void *a);

private:
	char m_bfmeHead[0x1E8];
	Gen_001BF490Target *m_bfmeImpl;				// +0x1E8
};

class Gen_001BF4B0
{
public:
	void bfmeForward(void *a);

private:
	char m_bfmeHead[0x1E8];
	Gen_001BF4B0Target *m_bfmeImpl;				// +0x1E8
};

class Gen_001BF4D0
{
public:
	void bfmeForward(void *a);

private:
	char m_bfmeHead[0x1E8];
	Gen_001BF4D0Target *m_bfmeImpl;				// +0x1E8
};

class Gen_001BF4F0
{
public:
	void bfmeForward(void *a);

private:
	char m_bfmeHead[0x1E8];
	Gen_001BF4F0Target *m_bfmeImpl;				// +0x1E8
};

class Gen_0037DF60Owner
{
public:
	void bfmeApply(void *a);				// ILT 0x000204F0
};

class Gen_0052F050Owner
{
public:
	void bfmeApply(void *a);				// ILT 0x0002B210
};

class Gen_00574F40Owner
{
public:
	void bfmeApply(void *a);				// ILT 0x00013471
};

// ?bfmeForward@Gen_001BF490@@QAEXPAX@Z
void Gen_001BF490::bfmeForward(void *a)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a);
}

// ?bfmeForward@Gen_001BF4B0@@QAEXPAX@Z
void Gen_001BF4B0::bfmeForward(void *a)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a);
}

// ?bfmeForward@Gen_001BF4D0@@QAEXPAX@Z
void Gen_001BF4D0::bfmeForward(void *a)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a);
}

// ?bfmeForward@Gen_001BF4F0@@QAEXPAX@Z
void Gen_001BF4F0::bfmeForward(void *a)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a);
}

// ?bfmeInvoke_0037DF60@@YGXPAVGen_0037DF60Owner@@PAX@Z
void __stdcall bfmeInvoke_0037DF60(Gen_0037DF60Owner *owner, void *a)
{
	owner->bfmeApply(a);
}

// ?bfmeInvoke_0052F050@@YGXPAVGen_0052F050Owner@@PAX@Z
void __stdcall bfmeInvoke_0052F050(Gen_0052F050Owner *owner, void *a)
{
	owner->bfmeApply(a);
}

// ?bfmeInvoke_00574F40@@YGXPAVGen_00574F40Owner@@PAX@Z
void __stdcall bfmeInvoke_00574F40(Gen_00574F40Owner *owner, void *a)
{
	owner->bfmeApply(a);
}
