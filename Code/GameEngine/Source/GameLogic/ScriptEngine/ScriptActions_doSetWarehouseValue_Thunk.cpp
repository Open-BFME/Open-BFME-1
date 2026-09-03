// cl: /DNDEBUG /MD /EHsc

typedef int Int;

class AsciiString
{
private:
	char *m_text;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

private:
	char *m_text;
};

class SupplyWarehouseDockUpdate
{
public:
	void setCashValue(Int);
};

class Object
{
public:
	SupplyWarehouseDockUpdate *findUpdateModule(Int key);
};

class ScriptEngine
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
	virtual Object *getUnitNamed(BfmeAsciiStringArg) = 0;
};

class NameKeyGenerator
{
public:
	Int nameToKey(const char *name);
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptActions
{
protected:
	void doSetWarehouseValue(const AsciiString &, Int);
};

// ?doSetWarehouseValue@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doSetWarehouseValue(const AsciiString &warehouseName, Int cashValue)
{
	Object *object = TheScriptEngine->getUnitNamed(warehouseName);
	if (!object)
		return;

	static const Int warehouseModuleKey = TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
	SupplyWarehouseDockUpdate *warehouse = object->findUpdateModule(warehouseModuleKey);
	if (warehouse)
		warehouse->setCashValue(cashValue);
}
