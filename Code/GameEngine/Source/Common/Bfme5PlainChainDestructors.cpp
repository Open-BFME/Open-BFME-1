// Four non-polymorphic destructors: two members, then the base.
//
// Nothing here stores a vftable, so none of these classes is polymorphic and
// the base destructor is reached by an ordinary call rather than through a
// slot. The bodies are empty in source; the three calls are the two members in
// reverse declaration order followed by the base.
//
// The state word counts what is still to be unwound: 1, then 0 -- written as a
// byte, since only the low one changes -- then -1 once the members are gone
// and only the base is left. The base's width is what sets the member offsets,
// and those are the only differences between the four.

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

class BfmeDtorMemberM
{
public:
	~BfmeDtorMemberM(void);					// retail 0x0000E5D9

private:
	int m_bfmeValue;
};

void bfmeDeallocate(void *memory, unsigned int bytes);

class BfmeDtorMemberJBase
{
protected:
	~BfmeDtorMemberJBase(void)
	{
		if (m_header != 0)
			bfmeDeallocate(m_header, 0x30);
	}

	void *m_header;
	int m_bfmeTreeState[2];
};

class BfmeDtorMemberJ : public BfmeDtorMemberJBase
{
public:
	~BfmeDtorMemberJ(void);					// retail 0x009CF1E0

private:
	void clear(void);
};

class BfmeDtorMemberK
{
public:
	~BfmeDtorMemberK(void);					// retail 0x009CFB40

private:
	int m_bfmeValue;
};

class BfmeDtorBaseL
{
public:
	~BfmeDtorBaseL(void);					// retail 0x0001E30D

private:
	int m_bfmeFields[3];					// +0x00
};

class BfmeDtorBaseN
{
public:
	~BfmeDtorBaseN(void);					// retail 0x0004A430

private:
	char m_bfmePad[0x58];					// +0x00
};

class Gen_00093CC0 : public BfmeDtorBaseL
{
public:
	~Gen_00093CC0(void);

private:
	BfmeDtorMemberM m_bfmeFirst;				// +0x0C
	BfmeDtorMemberM m_bfmeSecond;				// +0x10
};

class Gen_002DEB80 : public BfmeDtorBaseN
{
public:
	~Gen_002DEB80(void);

private:
	BfmeDtorMemberD m_bfmeFirst;				// +0x58
	BfmeDtorMemberC m_bfmeSecond;				// +0x5C
};

class Gen_00581F30 : public BfmeDtorMemberC
{
public:
	~Gen_00581F30(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberD m_bfmeSecond;				// +0x08
};

class Gen_009D0730 : public BfmeDtorMemberC
{
public:
	~Gen_009D0730(void);

private:
	BfmeDtorMemberJ m_bfmeFirst;				// +0x04
	BfmeDtorMemberK m_bfmeSecond;				// +0x10
};

// ??1Gen_00093CC0@@QAE@XZ
Gen_00093CC0::~Gen_00093CC0(void)
{
}

// ??1Gen_002DEB80@@QAE@XZ
Gen_002DEB80::~Gen_002DEB80(void)
{
}

// ??1Gen_00581F30@@QAE@XZ
Gen_00581F30::~Gen_00581F30(void)
{
}

// ??1BfmeDtorMemberJ@@QAE@XZ
BfmeDtorMemberJ::~BfmeDtorMemberJ(void)
{
	clear();
}

// ??1Gen_009D0730@@QAE@XZ
Gen_009D0730::~Gen_009D0730(void)
{
}
