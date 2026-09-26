// cl: /O2 /Ob0

class Rva008918A0
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34(int value);

	void apply();
};

void Rva008918A0::apply()
{
	if (this)
		slot34(1);
}
