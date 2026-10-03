typedef float Real;

extern const Real g_rva01075350;
extern const Real BfmeSubdualCapERD;

struct BfmeObjectERD;

void __cdecl bfmeApplyERD(BfmeObjectERD *object, Real amount);

class BfmeHelperERD
{
public:
	void bfmeNotifyERD(Real amount);

	unsigned char m_bfmeHeadERD[8];
	BfmeObjectERD *m_bfmeObjectERD;
	unsigned char m_bfmeMidERD[0x80];
	Real m_bfmeLastERD;
};

void BfmeHelperERD::bfmeNotifyERD(Real amount)
{
	if (amount > g_rva01075350 && amount <= BfmeSubdualCapERD)
	{
		bfmeApplyERD(m_bfmeObjectERD, amount);
		m_bfmeLastERD = amount;
	}
}
