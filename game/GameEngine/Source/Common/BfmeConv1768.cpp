class BfmeBaseCH
{
public:
	~BfmeBaseCH();

	unsigned char m_bfmeHeadCH[0xc];
};

class BfmeMemCH
{
public:
	~BfmeMemCH();

	unsigned char m_bfmeHeadCH[0x10];
};

class BfmeTmpACH : public BfmeBaseCH
{
public:
	BfmeTmpACH(void *value) throw();
	~BfmeTmpACH() {}

	void bfmeUseCH(void *owner) throw();

	BfmeMemCH m_bfmeMemCH;
};

class BfmeOwnCH
{
public:
	BfmeOwnCH *bfmeMakeCH(void *value);
};

BfmeOwnCH *BfmeOwnCH::bfmeMakeCH(void *value)
{
	BfmeTmpACH(value).bfmeUseCH(this);

	return this;
}
