// cl: /DNDEBUG /MD /EHsc

class Module { public: virtual ~Module(); private: unsigned int m_storage[2]; };
class BehaviorModuleInterface { public: virtual void anchor(); };
class BehaviorModule : public Module, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};
class RunOffMapBehaviorInterface { public: virtual void anchor(); };
class RunOffMapBehavior : public BehaviorModule, public RunOffMapBehaviorInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~RunOffMapBehavior();
};

RunOffMapBehavior::~RunOffMapBehavior() {}

// ?forceDestructorEmission@RunOffMapBehavior@@SAXXZ absent-from-retail
void RunOffMapBehavior::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	RunOffMapBehavior value;
}
