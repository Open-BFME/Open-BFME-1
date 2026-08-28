// cl: /DNDEBUG /MD /EHsc

typedef int Bool;

class MemoryPool {
public:
	void *allocateBlockImplementation();
	int getAllocationSize();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolFactory {
public:
	MemoryPool *createMemoryPool(const char *name, int size, int initial, int overflow);
	MemoryPool *findMemoryPool(const char *name);
};

extern MemoryPoolFactory *TheMemoryPoolFactory;
extern void *TheObjectDefectionHelperPoolPtr;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectDefectionHelper.h
class ObjectDefectionHelper {
public:
	virtual ~ObjectDefectionHelper();
	static MemoryPool *getClassMemoryPool();
};

// ??1ObjectDefectionHelper@@UAE@XZ present-unmatched
ObjectDefectionHelper::~ObjectDefectionHelper()
{
	getClassMemoryPool();
}

// ?getClassMemoryPool@ObjectDefectionHelper@@CAPAVMemoryPool@@XZ present-unmatched
MemoryPool *ObjectDefectionHelper::getClassMemoryPool()
{
	static MemoryPool *pool = TheMemoryPoolFactory->createMemoryPool("ObjectDefectionHelper", sizeof(ObjectDefectionHelper), -1, -1);
	return pool;
}
