class Object;

class ContainModuleInterface
{
public:
	virtual void reserved00();
	virtual void reserved01();
	virtual void reserved02();
	virtual void reserved03();
	virtual void reserved04();
	virtual void reserved05();
	virtual void reserved06();
	virtual void reserved07();
	virtual void reserved08();
	virtual void reserved09();
	virtual void reserved10();
	virtual void reserved11();
	virtual void reserved12();
	virtual void reserved13();
	virtual void reserved14();
	virtual void reserved15();
	virtual void reserved16();
	virtual void reserved17();
	virtual void reserved18();
	virtual void reserved19();
	virtual void reserved20();
	virtual void reserved21();
	virtual void reserved22();
	virtual void reserved23();
	virtual void reserved24();
	virtual void reserved25();
	virtual void reserved26();
	virtual void reserved27();
	virtual void reserved28();
	virtual void reserved29();
	virtual void reserved30();
	virtual void reserved31();
	virtual void reserved32();
	virtual bool isValidContainerFor(const Object *object, bool checkCapacity);
};

class Object
{
private:
	char m_unmodelled[0x1FC];
	ContainModuleInterface *m_contain;

public:
	ContainModuleInterface *getContain() const { return m_contain; }
};

class DockUpdate
{
public:
	virtual bool isClearToEnter(const Object *docker) const;
};

class RailedTransportDockUpdate : public DockUpdate
{
public:
	virtual bool isClearToEnter(const Object *docker) const;
};

bool RailedTransportDockUpdate::isClearToEnter(const Object *docker) const
{
	const Object *us = *(Object *const *)((const char *)this - 0x18);

	if (!DockUpdate::isClearToEnter(docker))
		return false;

	ContainModuleInterface *contain = us->getContain();
	if (contain && !contain->isValidContainerFor(docker, true))
		return false;

	return true;
}
