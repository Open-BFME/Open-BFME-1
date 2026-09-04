// cl: /DNDEBUG /MD /EHsc

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual ~W3DSmudgeManager();
	virtual void init();
	virtual void reset();
	virtual void ReleaseResources();
	virtual void ReAcquireResources();
};

W3DSmudgeManager::~W3DSmudgeManager()
{
	ReleaseResources();
}
