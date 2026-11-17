typedef float Real;

extern const Real g_rva01075350;
extern float g_bfmeDefaultBU;

struct BfmeObjectERD;

// Retail calls ILT 0x000246A4 (-> 0x00739900); spell the callee as the
// ledgered ?j_000246a4 thunk, cdecl (object, amount).
extern void j_000246a4();

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
	if (amount > g_rva01075350 && amount <= g_bfmeDefaultBU)
	{
		((void (__cdecl *)(BfmeObjectERD *, Real))j_000246a4)(m_bfmeObjectERD, amount);
		m_bfmeLastERD = amount;
	}
}
