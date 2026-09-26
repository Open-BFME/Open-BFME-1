class BfmeRoomYF
{
public:
	BfmeRoomYF(const BfmeRoomYF &other);
	~BfmeRoomYF();

	unsigned char m_bfmeBytesYF[12];
};

extern BfmeRoomYF g_bfmeDefaultYF;

class BfmeOwnerYF
{
public:
	virtual void bfmeO00YF();
	virtual void bfmeO01YF();
	virtual void bfmeO02YF();
	virtual void bfmeO03YF();
	virtual void bfmeO04YF();
	virtual void bfmeO05YF();
	virtual void bfmeO06YF();
	virtual void bfmeO07YF();
	virtual void bfmeO08YF();
	virtual void bfmeO09YF();
	virtual void bfmeO10YF();
	virtual void bfmeO11YF();
	virtual void bfmeO12YF();
	virtual void bfmeO13YF();
	virtual void bfmeO14YF();
	virtual void bfmeO15YF();
	virtual void bfmeO16YF();
	virtual void bfmeO17YF();
	virtual void bfmeO18YF();
	virtual void bfmeO19YF();
	virtual void bfmeO20YF();
	virtual void bfmeO21YF();
	virtual void bfmeO22YF();
	virtual void bfmeO23YF();
	virtual void bfmeO24YF();
	virtual void bfmeO25YF();
	virtual void bfmeO26YF();
	virtual void bfmeO27YF();
	virtual void bfmeO28YF();
	virtual void bfmeO29YF();
	virtual void bfmeO30YF();
	virtual void bfmeO31YF();
	virtual void bfmeO32YF();
	virtual void bfmeO33YF();
	virtual void bfmeO34YF();
	virtual void bfmeO35YF();
	virtual void bfmeO36YF();
	virtual void bfmeO37YF();
	virtual void bfmeO38YF();
	virtual void bfmeO39YF();
	virtual void bfmeO40YF();
	virtual void bfmeO41YF();
	virtual void bfmeO42YF();
	virtual void bfmeO43YF();
	virtual void bfmeO44YF();
	virtual void bfmeO45YF();
	virtual bool bfmeReadyYF(int what);

	BfmeRoomYF bfmeGetYF(unsigned int index);

	unsigned char m_bfmeHeadYF[0x650];
	BfmeRoomYF m_bfmeRoomsYF[64];
	unsigned int m_bfmeCountYF;
};

BfmeRoomYF BfmeOwnerYF::bfmeGetYF(unsigned int index)
{
	if (bfmeReadyYF(4) && index < m_bfmeCountYF)
		return m_bfmeRoomsYF[index];

	return g_bfmeDefaultYF;
}
