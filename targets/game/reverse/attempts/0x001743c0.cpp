// ?bfmeRunJL@BfmeSelfJL@@QAEHXZ
// partial score=0.8 date=2026-09-08
class BfmeArgJL
{
public:
	int m_bfmeFJL[10];
};

class BfmeTgtJL;

class BfmeSubJL
{
public:
	BfmeTgtJL *bfmeResolveJL();
};

class BfmeTgtJL
{
public:
	virtual void bfmeVt00JL();
	virtual void bfmeVt01JL();
	virtual void bfmeVt02JL();
	virtual void bfmeVt03JL();
	virtual void bfmeVt04JL();
	virtual void bfmeVt05JL();
	virtual void bfmeVt06JL();
	virtual void bfmeVt07JL();
	virtual void bfmeVt08JL();
	virtual void bfmeVt09JL();
	virtual void bfmeVt10JL();
	virtual void bfmeVt11JL();
	virtual void bfmeVt12JL();
	virtual void bfmeVt13JL();
	virtual void bfmeVt14JL();
	virtual void bfmeVt15JL();
	virtual void bfmeVt16JL();
	virtual void bfmeVt17JL();
	virtual void bfmeVt18JL();
	virtual void bfmeVt19JL();
	virtual void bfmeVt20JL();
	virtual void bfmeVt21JL();
	virtual void bfmeVt22JL();
	virtual void bfmeVt23JL();
	virtual void bfmeVt24JL();
	virtual void bfmeVt25JL();
	virtual void bfmeVt26JL();
	virtual void bfmeVt27JL();
	virtual void bfmeVt28JL();
	virtual void bfmeVt29JL();
	virtual void bfmeVt30JL();
	virtual void bfmeVt31JL();
	virtual void bfmeVt32JL();
	virtual void bfmeVt33JL();
	virtual void bfmeVt34JL();
	virtual void bfmeVt35JL();
	virtual void bfmeVt36JL();
	virtual void bfmeVt37JL();
	virtual void bfmeVt38JL();
	virtual void bfmeVt39JL();
	virtual void bfmeVt40JL();
	virtual void bfmeVt41JL();
	virtual void bfmeVt42JL();
	virtual void bfmeVt43JL();
	virtual void bfmeVt44JL();
	virtual void bfmeVt45JL();
	virtual void bfmeVt46JL();
	virtual void bfmeVt47JL();
	virtual void bfmeVt48JL();
	virtual void bfmeVt49JL();
	virtual void bfmeVt50JL();
	virtual void bfmeVt51JL();
	virtual void bfmeVt52JL();
	virtual void bfmeVt53JL();
	virtual void bfmeVt54JL();
	virtual void bfmeVt55JL();
	virtual void bfmeVt56JL();
	virtual void bfmeVt57JL();
	virtual void bfmeVt58JL();
	virtual void bfmeVt59JL();
	virtual void bfmeVt60JL();
	virtual void bfmeVt61JL();
	virtual void bfmeVt62JL();
	virtual void bfmeVt63JL();
	virtual void bfmeVt64JL();
	virtual void bfmeVt65JL();
	virtual void bfmeVt66JL();
	virtual void bfmeVt67JL();
	virtual void bfmeVt68JL();
	virtual void bfmeVt69JL();
	virtual void bfmeVt70JL();
	virtual void bfmeVt71JL();
	virtual void bfmeVt72JL();
	virtual void bfmeVt73JL();
	virtual void bfmeVt74JL();
	virtual void bfmeVt75JL();
	virtual void bfmeVt76JL();
	virtual void bfmeVt77JL();
	virtual void bfmeVt78JL();
	virtual void bfmeVt79JL();
	virtual void bfmeVt80JL();
	virtual void bfmeVt81JL();
	virtual void bfmeVt82JL();
	virtual void bfmeVt83JL();
	virtual void bfmeVt84JL();
	virtual void bfmeVt85JL();
	virtual void bfmeVt86JL();
	virtual void bfmeVt87JL();
	virtual void bfmeVt88JL();
	virtual void bfmeVt89JL();
	virtual void bfmeVt90JL();
	virtual void bfmeVt91JL();
	virtual void bfmeVt92JL();
	virtual void bfmeVt93JL();
	virtual void bfmeCallJL(int a, int b, BfmeArgJL x, BfmeArgJL y);
};

class BfmeOwnJL
{
public:
	unsigned char m_bfmeHeadJL[0x10];
	BfmeSubJL *m_bfme10JL;
};

class BfmeSelfJL
{
public:
	int bfmeRunJL();

	unsigned char m_bfmeHeadJL[0x1c];
	BfmeOwnJL *m_bfme1cJL;
};

int BfmeSelfJL::bfmeRunJL()
{
	BfmeArgJL s1;
	BfmeArgJL s2;
	BfmeOwnJL *a = m_bfme1cJL;
	BfmeTgtJL *t;

	if (a->m_bfme10JL != 0)
	{
		t = a->m_bfme10JL->bfmeResolveJL();

		if (t == 0)
			return -2;
	}
	else
	{
		t = (BfmeTgtJL *)a;
	}

	s1.m_bfmeFJL[0] = 0;
	s1.m_bfmeFJL[1] = 0;
	s1.m_bfmeFJL[2] = 0;
	s1.m_bfmeFJL[3] = 0;
	s1.m_bfmeFJL[4] = 0;
	s1.m_bfmeFJL[5] = 0;
	s1.m_bfmeFJL[6] = 0;
	s1.m_bfmeFJL[7] = 0;
	s1.m_bfmeFJL[9] = 0;
	s2.m_bfmeFJL[0] = 0;
	s2.m_bfmeFJL[1] = 0;
	s2.m_bfmeFJL[2] = 0;
	s2.m_bfmeFJL[3] = 0;
	s2.m_bfmeFJL[4] = 0;
	s2.m_bfmeFJL[5] = 0;
	s2.m_bfmeFJL[6] = 0;
	s2.m_bfmeFJL[7] = 0;
	s1.m_bfmeFJL[8] = 0x1000000;
	s2.m_bfmeFJL[8] = 0x800000;

	t->bfmeCallJL(0x32, 0x3c, s2, s1);

	return 0;
}
