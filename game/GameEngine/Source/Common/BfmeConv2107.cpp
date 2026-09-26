struct Rva0020AA00Registry
{
	void *bfmeLookupZF(void *key);
};

extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

class BfmeOwnerZF
{
public:
	unsigned char m_bfmeHeadZF[0x248];
	int m_bfme248ZF;
};

class BfmeHostZF
{
public:
	void *bfmeFindZF();
};

void *BfmeHostZF::bfmeFindZF()
{
	BfmeOwnerZF *o = *(BfmeOwnerZF **)((char *)this - 0xe0);

	return Rva0020AA00TheRegistry->bfmeLookupZF(&o->m_bfme248ZF);
}
