// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Gen0078D1C0Base
{
public:
	virtual ~Gen0078D1C0Base() {}
};

class Gen0078D1C0Registry
{
public:
	virtual ~Gen0078D1C0Registry();

private:
	char m_unreconstructed[ 0xC8 ];
};

class Gen0078D1C0 : public Gen0078D1C0Base
{
public:
	virtual ~Gen0078D1C0() {}

private:
	Gen0078D1C0Registry m_registry;
	char m_unreconstructed[ 0x0E ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual ~GameWindow();

protected:
	Gen0078D1C0 *m_embeddedPointer;
	char m_unreconstructed[ 0x210 ];
};

class Rva0078D270GameWindowHost : public GameWindow
{
public:
	virtual ~Rva0078D270GameWindowHost();

private:
	Gen0078D1C0 m_embedded;
};

Rva0078D270GameWindowHost::~Rva0078D270GameWindowHost()
{
	m_embeddedPointer = 0;
}
