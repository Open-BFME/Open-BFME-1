class BfmeStrFM
{
public:
	BfmeStrFM(const BfmeStrFM &other);
	~BfmeStrFM();

	unsigned char m_bfmeHeadFM[4];
};

class Rva00361E00Element
{
public:
	BfmeStrFM stringAt0C() const;

	unsigned char m_bfmeBodyFM[0x58];
};

class BfmeHostFMVector
{
public:
	int size() const { return m_end - m_begin; }
	Rva00361E00Element *begin() const { return m_begin; }

	Rva00361E00Element *m_begin;
	Rva00361E00Element *m_end;
};

class BfmeHostFM
{
public:
	BfmeStrFM bfmeAtFM(int i) const;

	unsigned char m_bfmeHeadFM[0x18];
	BfmeHostFMVector m_bfmeVectorFM;
};

class Rva002E5FF0Str
{
public:
	void *m_data;
};

extern Rva002E5FF0Str Rva01336E50Str;

class BfmeSharedString
{
public:
	BfmeSharedString(const BfmeSharedString &other);
	~BfmeSharedString();

	void *m_data;
};

class Rva00361960
{
public:
	BfmeSharedString copyString();

	unsigned char m_bfmeBody[0x58];
};

class BfmeStrAVTV
{
public:
	BfmeStrAVTV(const BfmeStrAVTV &other);
	~BfmeStrAVTV();

	char *m_bfme00;
};

class BfmeElementDVB
{
public:
	BfmeStrAVTV getName() const;

	unsigned char m_bfmeBody[0x58];
};

class Rva00361E80Vector
{
public:
	int size() const { return m_end - m_begin; }
	Rva00361960 *begin() const { return m_begin; }

	Rva00361960 *m_begin;
	Rva00361960 *m_end;
};

class BfmeSubDVBVector
{
public:
	int size() const { return m_end - m_begin; }
	BfmeElementDVB *begin() const { return m_begin; }

	BfmeElementDVB *m_begin;
	BfmeElementDVB *m_end;
};

class BfmeSubDVB
{
public:
	void bfmeOneDVB(void *a, void *b);
	void bfmeTwoDVB(void *a, void *b);
	void bfmeThreeDVB(void *a, void *b);
	BfmeSharedString bfmeTwoDVB(int index);
	BfmeStrAVTV bfmeThreeDVB(int index);

	unsigned char m_bfmeHead[0x18];
	union
	{
		Rva00361E80Vector m_bfmeVectorTwo;
		BfmeSubDVBVector m_bfmeVectorThree;
	};
};

BfmeStrFM BfmeHostFM::bfmeAtFM(int i) const
{
	if (i >= 0 && (unsigned int)i < (unsigned int)m_bfmeVectorFM.size())
		return m_bfmeVectorFM.begin()[i].stringAt0C();

	return *(const BfmeStrFM *)&Rva01336E50Str;
}

BfmeSharedString BfmeSubDVB::bfmeTwoDVB(int index)
{
	if (index >= 0 && (unsigned int)index <
		(unsigned int)m_bfmeVectorTwo.size())
	{
		return m_bfmeVectorTwo.begin()[index].copyString();
	}

	return *(const BfmeSharedString *)&Rva01336E50Str;
}

BfmeStrAVTV BfmeSubDVB::bfmeThreeDVB(int index)
{
	if (index >= 0 && (unsigned int)index <
		(unsigned int)m_bfmeVectorThree.size())
	{
		return m_bfmeVectorThree.begin()[index].getName();
	}

	return *(const BfmeStrAVTV *)&Rva01336E50Str;
}

struct BfmeThingDVB
{
	void *bfmeGoDVBa(void *a, void *b);
	void *bfmeGoDVBb(void *a, void *b);
	void *bfmeGoDVBc(void *a, void *b);
	unsigned char m_bfmeHead[0x170];
	BfmeSubDVB m_bfmeSub;
};

void *BfmeThingDVB::bfmeGoDVBa(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeOneDVB(a, b);
	return a;
}

void *BfmeThingDVB::bfmeGoDVBb(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeTwoDVB(a, b);
	return a;
}

void *BfmeThingDVB::bfmeGoDVBc(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeThreeDVB(a, b);
	return a;
}
