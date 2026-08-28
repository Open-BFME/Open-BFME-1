class BehaviorModuleInterfaceSlice
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void notifyValue(int value) = 0;
};

class BehaviorModule;

class Object
{
public:
	void notifyBehaviorModulesOfValue();

private:
	unsigned char m_unmodelled000[0x1f0];
	BehaviorModule **m_behaviors;
	unsigned char m_unmodelled1f4[0x370 - 0x1f4];
	int m_value;
};

// Relay the current object value to the secondary behavior-module interface.
// ?notifyBehaviorModulesOfValue@Object@@QAEXXZ
void Object::notifyBehaviorModulesOfValue()
{
	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterfaceSlice *interfaceSlice =
			reinterpret_cast<BehaviorModuleInterfaceSlice *>(
				reinterpret_cast<unsigned char *>(*module) + 0x0c);
		interfaceSlice->notifyValue(m_value);
	}
}
