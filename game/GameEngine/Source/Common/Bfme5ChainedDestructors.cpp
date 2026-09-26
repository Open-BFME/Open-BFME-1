// Four destructors that unwind one member and then chain to a real base.
//
// Each is empty in source. The member at the class's own offset is destroyed
// first with the state word at zero, then the base destructor runs on this
// with the state back at -1; unlike the folded cases nearby, these bases are
// out of line, so the second call is a call and not another vftable store.
//
// The member offset is the base's width, and it is the only thing separating
// the four: 0x0C for the small base, then 0x9C, 0xB4 and 0x15C, which is why
// one body is three bytes shorter than the other three.


class BfmeDtorMemberC
{
public:
	~BfmeDtorMemberC(void);				// retail 0x00887940

private:
	int m_bfmeValue;
};

class BfmeDtorMemberF
{
public:
	~BfmeDtorMemberF(void);				// retail 0x00013AFC

private:
	int m_bfmeValue;
};

class BfmeDtorBaseF
{
public:
	virtual ~BfmeDtorBaseF(void);				// retail 0x009A1A40

private:
	char m_bfmePad[0x8];					// +0x04
};

class BfmeDtorBaseG
{
public:
	virtual ~BfmeDtorBaseG(void);				// retail 0x0004243D

private:
	char m_bfmePad[0x98];					// +0x04
};

class BfmeDtorBaseH
{
public:
	virtual ~BfmeDtorBaseH(void);				// retail 0x000033F0

private:
	char m_bfmePad[0xB0];					// +0x04
};

class BfmeDtorBaseI
{
public:
	virtual ~BfmeDtorBaseI(void);				// retail 0x0002C71E

private:
	char m_bfmePad[0x158];					// +0x04
};

class Gen_00076C80 : public BfmeDtorBaseF
{
public:
	virtual ~Gen_00076C80(void);

private:
	BfmeDtorMemberF m_bfmeMember;				// +0x0C
};

class Gen_000B5240 : public BfmeDtorBaseG
{
public:
	virtual ~Gen_000B5240(void);

private:
	BfmeDtorMemberC m_bfmeMember;				// +0x9C
};

class Gen_00428730 : public BfmeDtorBaseH
{
public:
	virtual ~Gen_00428730(void);

private:
	BfmeDtorMemberC m_bfmeMember;				// +0xB4
};

class Gen_0077DD80 : public BfmeDtorBaseI
{
public:
	virtual ~Gen_0077DD80(void);

private:
	BfmeDtorMemberC m_bfmeMember;				// +0x15C
};

// ??1Gen_00076C80@@UAE@XZ
Gen_00076C80::~Gen_00076C80(void)
{
}

// ??1Gen_000B5240@@UAE@XZ
Gen_000B5240::~Gen_000B5240(void)
{
}

// ??1Gen_00428730@@UAE@XZ
Gen_00428730::~Gen_00428730(void)
{
}

// ??1Gen_0077DD80@@UAE@XZ
Gen_0077DD80::~Gen_0077DD80(void)
{
}
