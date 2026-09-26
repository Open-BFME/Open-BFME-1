typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

extern int(__cdecl *g_bfmeNowVNH)();
void bfmeRefreshXE();

class BfmeSpyXE
{
public:
	virtual void bfmeS00XE();
	virtual void bfmeS01XE();
	virtual void bfmeS02XE();
	virtual void bfmeS03XE();
	virtual void bfmeS04XE();
	virtual void bfmeS05XE();
	virtual void bfmeS06XE();
	virtual void bfmeS07XE();
	virtual void bfmeS08XE();
	virtual void bfmeS09XE();
	virtual void bfmeS10XE();
	virtual void bfmeS11XE();
	virtual void bfmeS12XE();
	virtual void bfmeS13XE();
	virtual void bfmeS14XE();
	virtual void bfmeS15XE();
	virtual void bfmeS16XE();
	virtual void bfmeS17XE();
	virtual void bfmeS18XE();
	virtual void bfmeS19XE();
	virtual void bfmeS20XE();
	virtual void bfmeS21XE();
	virtual void bfmeS22XE();
	virtual void bfmeS23XE();
	virtual void bfmeS24XE();
	virtual void bfmeS25XE();
	virtual void bfmeS26XE();
	virtual void bfmeS27XE();
	virtual void bfmeS28XE();
	virtual void bfmeS29XE();
	virtual void bfmeS30XE();
	virtual void bfmeS31XE();
	virtual void bfmeS32XE();
	virtual void bfmeS33XE();
	virtual void bfmeS34XE();
	virtual void bfmeS35XE();
	virtual void bfmeS36XE();
	virtual void bfmeS37XE();
	virtual void bfmeS38XE();
	virtual void bfmeS39XE();
	virtual void bfmeS40XE();
	virtual void bfmeS41XE();
	virtual void bfmeS42XE();
	virtual Bool bfmeAllowedXE();
};

extern BfmeSpyXE *TheBfmeSpyXE;

class BfmeOwnerXE
{
public:
	void bfmePollXE(Bool force);

	char m_bfmePadXE[0xa0];
	UnsignedInt m_bfmeTimeXE;
};

void BfmeOwnerXE::bfmePollXE(Bool force)
{
	int(__cdecl *nowFunction)() = g_bfmeNowVNH;

	if (!force) {
		if (m_bfmeTimeXE != 0) {
			UnsignedInt now = nowFunction();
			if (m_bfmeTimeXE + 10000 > now)
				return;
		}
	}

	if (TheBfmeSpyXE->bfmeAllowedXE()) {
		bfmeRefreshXE();
		m_bfmeTimeXE = nowFunction();
	}
}
