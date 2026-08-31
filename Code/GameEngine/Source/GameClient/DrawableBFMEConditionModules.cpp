// Byte-matched BFME Drawable condition-module notification helper.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class Object
{
public:
	UnsignedByte m_unreconstructed_000[0x118];
	UnsignedInt m_modelConditionWord0;
};

class BfmeDrawModule
{
public:
	virtual void bfmeSlot00() = 0; virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0; virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0; virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot18() = 0; virtual void bfmeSlot1C() = 0;
	virtual void bfmeSlot20() = 0; virtual void bfmeSlot24() = 0;
	virtual void bfmeSlot28() = 0; virtual void bfmeSlot2C() = 0;
	virtual void bfmeSlot30() = 0; virtual void bfmeSlot34() = 0;
	virtual void bfmeSlot38() = 0; virtual void bfmeSlot3C() = 0;
	virtual void bfmeSlot40() = 0; virtual void bfmeSlot44() = 0;
	virtual void bfmeSlot48() = 0; virtual void bfmeSlot4C() = 0;
	virtual void bfmeSlot50() = 0; virtual void bfmeSlot54() = 0;
	virtual void bfmeSlot58() = 0; virtual void bfmeSlot5C() = 0;
	virtual void bfmeSlot60() = 0; virtual void bfmeSlot64() = 0;
	virtual void bfmeSlot68() = 0; virtual void bfmeSlot6C() = 0;
	virtual void bfmeSlot70() = 0; virtual void bfmeSlot74() = 0;
	virtual void bfmeSlot78() = 0; virtual void bfmeSlot7C() = 0;
	virtual void bfmeSlot80() = 0; virtual void bfmeSlot84() = 0;
	virtual void bfmeSlot88() = 0; virtual void bfmeSlot8C() = 0;
	virtual void bfmeSlot90() = 0; virtual void bfmeSlot94() = 0;
	virtual void bfmeSlot98() = 0; virtual void bfmeSlot9C() = 0;
	virtual void bfmeSlotA0() = 0; virtual void bfmeSlotA4() = 0;
	virtual void bfmeSlotA8() = 0; virtual void bfmeSlotAC() = 0;
	virtual void bfmeSlotB0() = 0; virtual void bfmeSlotB4() = 0;
	virtual void bfmeSlotB8() = 0; virtual void bfmeSlotBC() = 0;
	virtual void bfmeSlotC0() = 0; virtual void bfmeSlotC4() = 0;
	virtual void bfmeSlotC8() = 0; virtual void bfmeSlotCC() = 0;
	virtual void bfmeSlotD0() = 0; virtual void bfmeSlotD4() = 0;
	virtual void bfmeSlotD8() = 0; virtual void bfmeSlotDC() = 0;
	virtual void bfmeSlotE0() = 0; virtual void bfmeSlotE4() = 0;
	virtual void bfmeCondition4Callback() = 0;
};

class Drawable
{
public:
	void bfmeNotifyCondition4Modules(Object *object);

private:
	UnsignedByte m_unreconstructed_000[0x150];
	BfmeDrawModule **m_drawModules;
};

void Drawable::bfmeNotifyCondition4Modules(Object *object)
{
	if (object == 0 || !(object->m_modelConditionWord0 & 0x10))
		return;

	for (BfmeDrawModule **module = m_drawModules; *module; ++module)
		(*module)->bfmeCondition4Callback();
}
