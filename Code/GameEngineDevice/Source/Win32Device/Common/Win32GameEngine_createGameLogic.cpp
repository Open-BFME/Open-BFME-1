// cl: /DNDEBUG /MD /EHsc

// BFME's Win32GameEngine factory. The canonical implementation returns a
// W3DGameLogic; the retail allocation size and two derived vtable stores also
// distinguish that concrete type from the GameLogic base.
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
	virtual GameLogic *createGameLogic();
};

// ?createGameLogic@Win32GameEngine@@MAEPAVGameLogic@@XZ
GameLogic *Win32GameEngine::createGameLogic()
{
	return new W3DGameLogic;
}
