// Eight two-member constructors.
//
// Each copy-constructs a member at +0x00 through a shared routine and a second
// member at +0x04 through a routine of its own, and carries a full SEH frame
// while doing it.
//
// That frame is the point. Both members need DESTRUCTORS declared, even though
// neither destructor is called here: without them the compiler has nothing to
// unwind if the second copy throws, emits no frame at all, and the body
// collapses from eighty bytes to thirty-two. The mov [esp+0x14],0 between the
// two calls is the unwind state moving from -1 to 0, not a local being
// cleared, and the mov [esp+8],esi before them parks this where the funclet
// can find it.

class BfmeMemberA
{
public:
	BfmeMemberA(const BfmeMemberA &other);			// retail 0x00887B60
	~BfmeMemberA(void);

private:
	void *m_bfmeItem;
};


class BfmeMemberB_000809D0
{
public:
	BfmeMemberB_000809D0(const BfmeMemberB_000809D0 &other);		// retail 0x00011ADB
	~BfmeMemberB_000809D0(void);

private:
	void *m_bfmeItem;
};

class Gen_000809D0
{
public:
	Gen_000809D0(const BfmeMemberA &first, const BfmeMemberB_000809D0 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_000809D0 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_000C1490
{
public:
	BfmeMemberB_000C1490(const BfmeMemberB_000C1490 &other);		// retail 0x0000EA75
	~BfmeMemberB_000C1490(void);

private:
	void *m_bfmeItem;
};

class Gen_000C1490
{
public:
	Gen_000C1490(const BfmeMemberA &first, const BfmeMemberB_000C1490 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_000C1490 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_0013ED00
{
public:
	BfmeMemberB_0013ED00(const BfmeMemberB_0013ED00 &other);		// retail 0x00047B27
	~BfmeMemberB_0013ED00(void);

private:
	void *m_bfmeItem;
};

class Gen_0013ED00
{
public:
	Gen_0013ED00(const BfmeMemberA &first, const BfmeMemberB_0013ED00 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_0013ED00 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_0045F410
{
public:
	BfmeMemberB_0045F410(const BfmeMemberB_0045F410 &other);		// retail 0x00009278
	~BfmeMemberB_0045F410(void);

private:
	void *m_bfmeItem;
};

class Gen_0045F410
{
public:
	Gen_0045F410(const BfmeMemberA &first, const BfmeMemberB_0045F410 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_0045F410 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_005825E0
{
public:
	BfmeMemberB_005825E0(const BfmeMemberB_005825E0 &other);		// retail 0x0001202B
	~BfmeMemberB_005825E0(void);

private:
	void *m_bfmeItem;
};

class Gen_005825E0
{
public:
	Gen_005825E0(const BfmeMemberA &first, const BfmeMemberB_005825E0 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_005825E0 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_00632360
{
public:
	BfmeMemberB_00632360(const BfmeMemberB_00632360 &other);		// retail 0x00028218
	~BfmeMemberB_00632360(void);

private:
	void *m_bfmeItem;
};

class Gen_00632360
{
public:
	Gen_00632360(const BfmeMemberA &first, const BfmeMemberB_00632360 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_00632360 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_009CAA70
{
public:
	BfmeMemberB_009CAA70(const BfmeMemberB_009CAA70 &other);		// retail 0x009CA8F0
	~BfmeMemberB_009CAA70(void);

private:
	void *m_bfmeItem;
};

class Gen_009CAA70
{
public:
	Gen_009CAA70(const BfmeMemberA &first, const BfmeMemberB_009CAA70 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_009CAA70 m_bfmeSecond;				// +0x04
};

class BfmeMemberB_009CF070
{
public:
	BfmeMemberB_009CF070(const BfmeMemberB_009CF070 &other);		// retail 0x009CEBF0
	~BfmeMemberB_009CF070(void);

private:
	void *m_bfmeItem;
};

class Gen_009CF070
{
public:
	Gen_009CF070(const BfmeMemberA &first, const BfmeMemberB_009CF070 &second);

private:
	BfmeMemberA m_bfmeFirst;				// +0x00
	BfmeMemberB_009CF070 m_bfmeSecond;				// +0x04
};

// ??0Gen_000809D0@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_000809D0@@@Z
Gen_000809D0::Gen_000809D0(const BfmeMemberA &first, const BfmeMemberB_000809D0 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_000C1490@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_000C1490@@@Z
Gen_000C1490::Gen_000C1490(const BfmeMemberA &first, const BfmeMemberB_000C1490 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_0013ED00@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_0013ED00@@@Z
Gen_0013ED00::Gen_0013ED00(const BfmeMemberA &first, const BfmeMemberB_0013ED00 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_0045F410@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_0045F410@@@Z
Gen_0045F410::Gen_0045F410(const BfmeMemberA &first, const BfmeMemberB_0045F410 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_005825E0@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_005825E0@@@Z
Gen_005825E0::Gen_005825E0(const BfmeMemberA &first, const BfmeMemberB_005825E0 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_00632360@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_00632360@@@Z
Gen_00632360::Gen_00632360(const BfmeMemberA &first, const BfmeMemberB_00632360 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_009CAA70@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_009CAA70@@@Z
Gen_009CAA70::Gen_009CAA70(const BfmeMemberA &first, const BfmeMemberB_009CAA70 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}

// ??0Gen_009CF070@@QAE@ABVBfmeMemberA@@ABVBfmeMemberB_009CF070@@@Z
Gen_009CF070::Gen_009CF070(const BfmeMemberA &first, const BfmeMemberB_009CF070 &second)
	: m_bfmeFirst(first)
	, m_bfmeSecond(second)
{
}
