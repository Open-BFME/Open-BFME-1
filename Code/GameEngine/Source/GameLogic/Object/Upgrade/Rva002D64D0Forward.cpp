// Address-derived virtual forwarding helper at 0x002D64D0.
// cl: /O2 /DNDEBUG /DWIN32 /MD

class Rva002D64D0Target
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual float getValue(int value) = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void setValue(float value) = 0;
};

class Rva002D64D0Source
{
public:
	unsigned char m_pad000[0x200];
	Rva002D64D0Target *m_target;
};

class Rva002D64D0Data
{
public:
	unsigned char m_pad000[0x70];
	float m_bias;
	int m_value;
};

class Rva002D64D0Owner
{
public:
	void forwardValue();

private:
};

void Rva002D64D0Owner::forwardValue()
{
	Rva002D64D0Source *source = *reinterpret_cast<Rva002D64D0Source **>(reinterpret_cast<char *>(this) - 8);
	Rva002D64D0Data *data = *reinterpret_cast<Rva002D64D0Data **>(reinterpret_cast<char *>(this) - 12);
	Rva002D64D0Target *target = source->m_target;
	if (target) {
		target->setValue(target->getValue(data->m_value) + data->m_bias);
	}
}
