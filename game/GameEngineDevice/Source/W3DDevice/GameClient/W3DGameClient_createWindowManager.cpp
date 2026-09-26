// Retail 0x006FB600.  The reference W3DGameClient inline factory allocates a
// W3DGameWindowManager.  Its GameWindowManager base reaches +0x3B in retail:
// the tab-list view starts at +0x30 and is followed by the cursor and capture
// fields.  Keep that ABI correction local to this factory TU.

class GameWindowManager
{
public:

	virtual ~GameWindowManager();

private:

	unsigned char m_retailData[0x38];
};

class W3DGameWindowManager : public GameWindowManager
{
public:

	W3DGameWindowManager();
};

typedef char BfmeRetailW3DGameWindowManagerSizeCheck[
	sizeof( W3DGameWindowManager ) == 0x3c ? 1 : -1 ];

class W3DGameClient
{
protected:

	virtual GameWindowManager *createWindowManager();
};

GameWindowManager *W3DGameClient::createWindowManager()
{
	return new W3DGameWindowManager;
}
