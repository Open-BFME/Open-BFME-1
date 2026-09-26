class BfmeHostXP
{
public:
	unsigned char m_bfmeHeadXP[0x68];
	unsigned char m_bfmeFlagXP;
};

class BfmeOuterXP
{
public:
	virtual void bfmeO00XP();
	virtual void bfmeO01XP();
	virtual void bfmeO02XP();
	virtual void bfmeO03XP();
	virtual void bfmeO04XP();
	virtual void bfmeO05XP();
	virtual void bfmeO06XP();
	virtual void bfmeO07XP();
	virtual void bfmeO08XP();
	virtual void bfmeO09XP();
	virtual void bfmeO10XP();
	virtual void bfmeO11XP();
	virtual void bfmeO12XP();
	virtual void bfmeO13XP();
	virtual void bfmeO14XP();
	virtual void bfmeO15XP();
	virtual void bfmeO16XP();
	virtual void bfmeO17XP();
	virtual void bfmeO18XP();
	virtual void bfmeO19XP();
	virtual void bfmeO20XP();
	virtual void bfmeO21XP();
	virtual void bfmeO22XP();
	virtual void bfmeO23XP();
	virtual void bfmeO24XP();
	virtual void bfmeO25XP();
	virtual void bfmeO26XP();
	virtual void bfmeO27XP();
	virtual void bfmeO28XP();
	virtual void bfmeO29XP();
	virtual void bfmeO30XP();
	virtual void bfmeO31XP();
	virtual void bfmeO32XP();
	virtual void bfmeO33XP();
	virtual void bfmeO34XP();
	virtual void bfmeO35XP();
	virtual void bfmeO36XP();
	virtual void bfmeO37XP();
	virtual void bfmeO38XP();
	virtual void bfmeO39XP();
	virtual void bfmeO40XP();
	virtual void bfmeO41XP();
	virtual void bfmeO42XP();
	virtual void bfmeO43XP();
	virtual void bfmeO44XP();
	virtual void bfmeO45XP();
	virtual int bfmeReadyXP();
	virtual void bfmeO47XP();
	virtual void bfmeO48XP();
	virtual void bfmeO49XP();
	virtual void bfmeO50XP();
	virtual void bfmeO51XP();
	virtual void bfmeO52XP();
	virtual void bfmeO53XP();
	virtual void bfmeO54XP();
	virtual void bfmeO55XP();
	virtual void bfmeO56XP();
	virtual void bfmeO57XP();
	virtual void bfmeO58XP();
	virtual void bfmeO59XP();
	virtual void bfmeO60XP();
	virtual void bfmeApplyXP(int a, int zero, int b);

	BfmeHostXP *m_bfmeHostXP;
};

class BfmeOwnerXP
{
public:
	void bfmeSetXP(unsigned int value);

	unsigned char m_bfmeHeadXP[4];
	int m_bfmeAXP;
	int m_bfmeBXP;
	unsigned char m_bfmePadXP[0xc];
	unsigned int m_bfmeValueXP;
};

void BfmeOwnerXP::bfmeSetXP(unsigned int value)
{
	if (((BfmeOuterXP *)((char *)this - 0xc))->m_bfmeHostXP->m_bfmeFlagXP != 0)
	{
		if (value != 0)
			value |= 0xff000000;

		if (value != m_bfmeValueXP)
		{
			m_bfmeValueXP = value;

			if (((BfmeOuterXP *)((char *)this - 0xc))->bfmeReadyXP() != 0)
			{
				int a = m_bfmeAXP;

				m_bfmeAXP = 0;
				((BfmeOuterXP *)((char *)this - 0xc))->bfmeApplyXP(a, 0, m_bfmeBXP);
			}
		}
	}
}
