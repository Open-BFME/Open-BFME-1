// ?xfer@PlayerList@@UAEXPAVXfer@@@Z
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /O2 /EHs-c-

typedef unsigned char UnsignedByte;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(int *);
};

class Player;

class PlayerList
{
public:
	virtual void xfer(Xfer *xfer);

private:
	Player *m_local;
	int m_playerCount;
	Player *m_players[32];
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);

void PlayerList::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	int playerCount = m_playerCount;
	xfer->xferInt(&playerCount);
	if (playerCount != m_playerCount)
	{
		BfmeFormattedText error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	for (int i = 0; i < playerCount; ++i)
		xfer->xferSnapshot(reinterpret_cast<Snapshot *>(m_players[i]));
}
