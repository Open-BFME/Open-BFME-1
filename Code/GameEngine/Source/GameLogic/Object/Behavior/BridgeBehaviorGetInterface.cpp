// cl: /DNDEBUG /MD /EHsc

class BridgeBehaviorInterface {};

class BehaviorModuleInterfaceSlice
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0C();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1C();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28();
	virtual BridgeBehaviorInterface *getBridgeBehaviorInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
private:
	unsigned char m_unmodelled_00[0x0c];

public:
	BehaviorModuleInterfaceSlice m_interface;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BehaviorModule **getBehaviorModules() { return m_behaviors; }

private:
	unsigned char m_unmodelled_00[0x1f0];
	BehaviorModule **m_behaviors;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *object);
};

BridgeBehaviorInterface *BridgeBehavior::getBridgeBehaviorInterfaceFromObject(Object *object)
{
	if (object == 0)
		return 0;

	BehaviorModule **module = object->getBehaviorModules();
	for (; *module != 0; ++module) {
		BridgeBehaviorInterface *bridge = (*module)->m_interface.getBridgeBehaviorInterface();
		if (bridge != 0)
			return bridge;
	}
	return 0;
}
