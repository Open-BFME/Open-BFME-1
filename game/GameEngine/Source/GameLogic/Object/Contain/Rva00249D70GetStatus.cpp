// Byte-twin of RiderChangeContain::getStatus at 0x0022B480
// (ContainModuleInterfaceGetStatus.cpp): identical 98 bytes once relocations
// are masked; all callees (the pinned lookup/accepts pair and the tail
// getTriple thunk) are fixed real symbols independent of the enclosing
// class, so only the container class needs a fresh name. No name is
// provable for this second site, so it is claimed address-derived.

typedef bool Bool;
typedef int Int;

class Object;
class Player;

struct Rva221A50Triple
{
	unsigned int first;
	unsigned int second;
	unsigned int third;
};

class Rva221A50Inner
{
public:
	Rva221A50Triple getTriple(Int index) const;
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva00249D70ModuleData
{
private:
	char m_unmodelled_000[0x224];

public:
	Rva2225E0Filter m_containFilter;
};

class Rva00249D70Interface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual Rva221A50Triple getStatus(Object *object) const;
};

class Rva00249D70ContainModuleData : public Rva00249D70ModuleData
{
};

class Rva00249D70Contain : public Rva00249D70Interface
{
public:
	virtual Rva221A50Triple getStatus(Object *object) const;

	Rva00249D70ContainModuleData *getModuleData() const
	{
		return *(Rva00249D70ContainModuleData **)((char *)this - 0x1c);
	}

	Object *getObject() const
	{
		return *(Object **)((char *)this - 0x18);
	}
};

Rva221A50Triple Rva00249D70Contain::getStatus(Object *object) const
{
	Object *owner = getObject();
	if (object != 0)
	{
		if (getModuleData()->m_containFilter.accepts(
			object, owner->getControllingPlayer()))
		{
			return *(Rva221A50Triple *)((char *)getModuleData() + 0x23c);
		}
	}

	return ((Rva221A50Inner *)this)->getTriple((Int)object);
}
