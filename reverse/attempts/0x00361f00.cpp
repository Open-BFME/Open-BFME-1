// ?d_00361f00@@YAXXZ
// partial score=0.97 date=2026-09-10
// ?d_00361f00@@YAXXZ
// Partial clean reconstruction for the 0x00361F00 triplet member.
class BfmeStrFM
{
public:
	BfmeStrFM(const BfmeStrFM &other);
	~BfmeStrFM();

	unsigned char m_bfmeHeadFM[4];
};

extern BfmeStrFM Rva01336E50Str;

class BfmeElemFM
{
public:
	BfmeStrFM bfmeNameFM() const;

	unsigned char m_bfmeHeadFM[0x58];
};

class BfmeHostFM
{
public:
	BfmeStrFM bfmeAtFM(int i) const;

	unsigned char m_bfmeHeadFM[0x18];
	BfmeElemFM *m_bfmeBeginFM;
	BfmeElemFM *m_bfmeEndFM;
};

BfmeStrFM BfmeHostFM::bfmeAtFM(int i) const
{
	if (i >= 0 && (unsigned int)i < (unsigned int)(m_bfmeEndFM - m_bfmeBeginFM))
		return (*(BfmeElemFM *volatile *)&m_bfmeBeginFM)[i].bfmeNameFM();

	return Rva01336E50Str;
}
