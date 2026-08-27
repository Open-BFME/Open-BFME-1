// Five destructors over a base whose own destructor folds in.
//
// Each body is empty in source. What it emits is a full unwind frame -- the
// -1 trylevel, the scope table, the linked fs:[0] record -- because the member
// at +0x0C has a destructor that must run if anything above throws; the state
// word going -1 to 0 is that member becoming live.
//
// The two vftable stores are the two destructors: the derived one on entry and
// the base one on exit, the latter inlined because the base destructor is
// defined in its own class body. Twelve bytes of base -- vptr plus two fields
// -- is what puts the member at +0x0C.


class BfmeDtorMemberA
{
public:
	~BfmeDtorMemberA(void);				// retail 0x00836300

private:
	int m_bfmeValue;
};

class BfmeDtorMemberB
{
public:
	~BfmeDtorMemberB(void);				// retail 0x0000B109

private:
	int m_bfmeValue;
};

template <int RetailCopy>
class BfmeDtorBase
{
public:
	virtual ~BfmeDtorBase(void) {}

private:
	int m_bfmeFields[2];					// +0x04
};

class Gen_00837480 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_00837480(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_008374F0 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_008374F0(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_00837560 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_00837560(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_008375D0 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_008375D0(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_009D9C00 : public BfmeDtorBase<1>
{
public:
	virtual ~Gen_009D9C00(void);

private:
	BfmeDtorMemberB m_bfmeMember;				// +0x0C
};

// ??1Gen_00837480@@UAE@XZ
Gen_00837480::~Gen_00837480(void)
{
}

// ??1Gen_008374F0@@UAE@XZ
Gen_008374F0::~Gen_008374F0(void)
{
}

// ??1Gen_00837560@@UAE@XZ
Gen_00837560::~Gen_00837560(void)
{
}

// ??1Gen_008375D0@@UAE@XZ
Gen_008375D0::~Gen_008375D0(void)
{
}

// ??1Gen_009D9C00@@UAE@XZ
Gen_009D9C00::~Gen_009D9C00(void)
{
}
