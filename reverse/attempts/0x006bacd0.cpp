// ?createGameLogic@Win32GameEngine@@MAEPAVGameLogic@@XZ
// partial score=0.99 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

// BFME's Win32GameEngine factory at 0x006BACD0.  The canonical Win32GameEngine
// header returns NEW W3DGameLogic here.  The retail allocation size (0x294),
// call to GameLogic::GameLogic, and the W3DGameLogic primary/Snapshot vftable
// stores independently confirm that identity.  Local class replicas keep the
// recovered BFME layout isolated from headers shared by other matched bodies.

class Xfer;
class TerrainLogic;
class GhostObjectManager;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;

	int m_name;
};

class Snapshot
{
public:
	Snapshot();
	~Snapshot();

protected:
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

class GameLogic : public SubsystemInterface, public Snapshot
{
public:
	GameLogic();
	virtual ~GameLogic();
	virtual void init();

protected:
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();
	virtual TerrainLogic *createTerrainLogic();
	virtual GhostObjectManager *createGhostObjectManager();

	char m_tail[0x294 - sizeof(SubsystemInterface) - sizeof(Snapshot)];
};

class W3DGameLogic : public GameLogic
{
protected:
	virtual TerrainLogic *createTerrainLogic();
	virtual GhostObjectManager *createGhostObjectManager();
};

class Win32GameEngine
{
protected:
	virtual GameLogic *createGameLogic(void);
};

GameLogic *Win32GameEngine::createGameLogic(void)
{
	return new W3DGameLogic;
}
