// cl: /O2 /Ob0

class Drawable
{
public:
	void updateDrawableSupplyStatus(int maxSupply, int currentSupply);
};

class ObjRva002C5E60
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1c();
	virtual void pad20();
	virtual void pad24();
	virtual Drawable *getDrawable();
};

class DataRva002C5E60
{
public:
	char m_lead[0x64];
	int m_maxBoxes;
};

class Rva002C5E60
{
public:
	bool loseOneBox();

	char m_pad[0x1C];
	int m_numberBoxes;
};

bool Rva002C5E60::loseOneBox()
{
	if (m_numberBoxes == 0)
		return false;
	--m_numberBoxes;
	Drawable *draw = (*(ObjRva002C5E60 **)((char *)this - 0x338))->getDrawable();
	if (draw)
		draw->updateDrawableSupplyStatus(
			(*(DataRva002C5E60 **)((char *)this - 0x33C))->m_maxBoxes,
			m_numberBoxes);
	return true;
}
