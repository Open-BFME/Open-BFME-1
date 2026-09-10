// cl: /DNDEBUG /MD /EHsc
// ?Rva003B3950Room@Glo012F1024Type@@QAE?AVBfmeRoomYC@@XZ
// Address-derived Glo012F1024Type indexed-entry room accessor at retail 0x003B3950.

class BfmeRoomYC
{
public:
	BfmeRoomYC(const BfmeRoomYC &other);
	~BfmeRoomYC();

	unsigned char m_bfmeBytesYC[0x20];
};

class BfmeSubYC
{
public:
	BfmeRoomYC bfmeRoomYC();
};

class BfmeElemYC
{
public:
	BfmeSubYC *bfmeSubYC();

	unsigned char m_bfmePadYC[0x20];
};

extern BfmeRoomYC g_bfmeDefaultYC;

class BfmeVecYC
{
public:
	int bfmeSizeYC(void) const { return (int)(m_bfmeEndYC - m_bfmeBeginYC); }

	BfmeElemYC *m_bfmeBeginYC;
	BfmeElemYC *m_bfmeEndYC;
};

class Glo012F1024Type
{
public:
	BfmeRoomYC Rva003B3950Room(void);

private:
	unsigned char m_pad00[0x0C];
	int m_bfmeIndexYC;
	BfmeVecYC m_bfmeVecYC;
};

// The returned room is copy-constructed into the caller's hidden buffer in both
// paths; the declared destructor is what gives retail its construction flag slot.
BfmeRoomYC Glo012F1024Type::Rva003B3950Room(void)
{
	if (m_bfmeIndexYC >= 0
		&& (unsigned int)m_bfmeIndexYC < (unsigned int)m_bfmeVecYC.bfmeSizeYC())
	{
		BfmeElemYC *begin = m_bfmeVecYC.m_bfmeBeginYC;
		BfmeSubYC *sub = begin[m_bfmeIndexYC].bfmeSubYC();
		return sub->bfmeRoomYC();
	}

	return g_bfmeDefaultYC;
}
