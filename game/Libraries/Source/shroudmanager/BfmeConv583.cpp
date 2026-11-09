class BfmeOwnerCDE
{
public:
	void bfmeOneCDE(void *what);
};

// Retail calls 0x008F8D00, ledgered as the stdcall ?bfmeReleaseABI@@YGXPAX@Z
// (ECX is loaded with the owner but unused); reach it by that ledger name.
void __stdcall bfmeReleaseABI(void *what);
typedef void (BfmeOwnerCDE::*BfmeOwnerCDEReleaseCall)(void *);
inline BfmeOwnerCDEReleaseCall bfmeOwnerCDERelease()
{
	union { void (__stdcall *plain)(void *); BfmeOwnerCDEReleaseCall member; } call;
	call.plain = bfmeReleaseABI;
	return call.member;
}

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();
	void bfmeGoCDE();
	BfmeOwnerCDE *m_bfmeOwner;
	void *m_bfmePtr;
};


void BfmeThingCDE::bfmeGoCDE()
{
	if (m_bfmePtr != 0)
	{
		(m_bfmeOwner->*bfmeOwnerCDERelease())(m_bfmePtr);
		return;
	}
	bfmeDtorCDE();
	::operator delete(this);
}
