// Open-BFME5 conversions.

struct BfmeSub1007
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};

struct BfmeX1007
{
	char m_bfmePad[0xfc];
	BfmeSub1007 *m_bfmeSub;
};

class BfmeSrc1007
{
public:
	virtual void bfmeVS01007();
	virtual void bfmeVS11007();
	virtual void bfmeVS21007();
	virtual void bfmeVS31007();
	virtual void bfmeVS41007();
	virtual void bfmeVS51007();
	virtual void bfmeVS61007();
	virtual void bfmeVS71007();
	virtual void bfmeVS81007();
	virtual void bfmeVS91007();
	virtual void bfmeVS101007();
	virtual BfmeX1007 *bfmeFind1007(void *a);
};

extern BfmeSrc1007 *g_bfmeSrc1007;

class BfmeB1007
{
public:
	char bfmeGo1007B(void *a);
	char bfmeSend1007(int v, void *a);
};

char BfmeB1007::bfmeGo1007B(void *a)
{
	if (!a)
		return 0;

	BfmeX1007 *x = g_bfmeSrc1007->bfmeFind1007(a);
	int v = 0;

	if (x && x->m_bfmeSub)
		v = x->m_bfmeSub->m_bfmeId;

	return bfmeSend1007(v, a);
}
