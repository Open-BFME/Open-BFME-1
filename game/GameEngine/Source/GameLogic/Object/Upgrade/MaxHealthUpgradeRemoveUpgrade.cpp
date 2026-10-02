// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// MaxHealthUpgrade::removeUpgrade at retail 0x002D6510: slot 7 of the UpgradeMux table
// 0x010CD158, reached only through ILT 0x0000AD44. MaxHealthUpgrade's registered
// constructor 0x002D63A0 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md
// Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot):
// targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md

class Rva002D6510Value
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual float read(float value);
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void write(float value);
};

class Rva002D6510Source
{
private:
	char m_pad00[0x70];

public:
	float m_subtract;
	float m_value;
};

class Rva002D6510Owner
{
public:
	char m_pad00[0x200];
	Rva002D6510Value *m_value;
};

class MaxHealthUpgrade
{
protected:
	virtual void removeUpgrade();
};

void MaxHealthUpgrade::removeUpgrade()
{
	Rva002D6510Owner *owner = *(Rva002D6510Owner **)((char *)this - 8);
	Rva002D6510Source *source = *(Rva002D6510Source **)((char *)this - 0x0C);
	Rva002D6510Value *value = owner->m_value;
	if (value != 0)
	{
		value->write(value->read(source->m_value) - source->m_subtract);
	}
}
