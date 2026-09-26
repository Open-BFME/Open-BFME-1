// cl: /DNDEBUG /MD

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
	virtual void init();
	virtual void reset();
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual void reset();
};

void W3DSmudgeManager::reset()
{
	SmudgeManager::reset();
}
