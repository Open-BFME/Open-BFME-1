// Three destructors that only have to unwind two members.
//
// Every body is empty in source. The frame exists because both members have
// destructors, and the two calls are those members going away in reverse
// declaration order -- the higher offset first. The state word carries that:
// zero while the second member is still to be destroyed, then -1 once nothing
// is left.
//
// The single vftable store is the class's own; none of these has a base with a
// destructor to inline. The member offsets differ per class and one of them
// sits 0x1B8 into the object, which is the only reason that body is three
// bytes longer.

class BfmeDtorMemberC
{
public:
	~BfmeDtorMemberC(void);					// retail 0x00887940

private:
	int m_bfmeValue;
};

class BfmeDtorMemberD
{
public:
	~BfmeDtorMemberD(void);					// retail 0x0001A401

private:
	int m_bfmeValue;
};

class BfmeDtorMemberE
{
public:
	~BfmeDtorMemberE(void);					// retail 0x008881D0

private:
	int m_bfmeValue;
};

class Gen_001031B0
{
public:
	virtual ~Gen_001031B0(void);

private:
	int m_bfmeFields[3];					// +0x04
	BfmeDtorMemberC m_bfmeFirst;				// +0x10
	BfmeDtorMemberC m_bfmeSecond;				// +0x14
};

class Gen_0014B790
{
public:
	virtual ~Gen_0014B790(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	char m_bfmePad[0x1B0];					// +0x08
	BfmeDtorMemberC m_bfmeSecond;				// +0x1B8
};

class Gen_0043DB30
{
public:
	virtual ~Gen_0043DB30(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberE m_bfmeSecond;				// +0x08
};

// ??1Gen_001031B0@@UAE@XZ
Gen_001031B0::~Gen_001031B0(void)
{
}

// ??1Gen_0014B790@@UAE@XZ
Gen_0014B790::~Gen_0014B790(void)
{
}

// ??1Gen_0043DB30@@UAE@XZ
Gen_0043DB30::~Gen_0043DB30(void)
{
}
