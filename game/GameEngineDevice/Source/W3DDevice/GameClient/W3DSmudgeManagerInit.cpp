class SmudgeManager
{
public:
	virtual ~SmudgeManager();
	virtual void init();
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual void init();
	virtual void reset();
	virtual void ReleaseResources();
	virtual void ReAcquireResources();
};

void W3DSmudgeManager::init()
{
	SmudgeManager::init();
	ReAcquireResources();
}
