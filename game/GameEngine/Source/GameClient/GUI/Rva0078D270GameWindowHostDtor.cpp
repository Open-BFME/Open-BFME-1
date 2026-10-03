// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Gen0078D1C0Base
{
public:
	virtual ~Gen0078D1C0Base() {}
};

// Retail's member teardown at 0x0078D040 destroys the embedded object through
// 0x009409F0, whose own body installs vtable 0x0113CEAC and is matched in the
// ledger as ??1Render2DSentenceClass@@UAE@XZ (see
// targets/game/reverse/identity_evidence/009409f0-render2dsentence-dtor.md).
// Spelling the embedded type with its defining name is what makes this
// reference resolve; the destructor's virtualness already matches UAE@XZ.
class Render2DSentenceClass
{
public:
	virtual ~Render2DSentenceClass();

private:
	char m_unreconstructed[ 0xC8 ];
};

class Gen0078D1C0 : public Gen0078D1C0Base
{
public:
	Gen0078D1C0();
	virtual ~Gen0078D1C0() {}

private:
	Render2DSentenceClass m_registry;
	char m_unreconstructed[ 0x0E ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	GameWindow();

protected:
	virtual ~GameWindow();
	Gen0078D1C0 *m_embeddedPointer;
	char m_unreconstructed[ 0x210 ];
};

class Rva0078D270GameWindowHost : public GameWindow
{
public:
	Rva0078D270GameWindowHost();
	virtual ~Rva0078D270GameWindowHost();

private:
	Gen0078D1C0 m_embedded;
};

Rva0078D270GameWindowHost::Rva0078D270GameWindowHost()
{
	m_embeddedPointer = &m_embedded;
}

Rva0078D270GameWindowHost::~Rva0078D270GameWindowHost()
{
	m_embeddedPointer = 0;
}
