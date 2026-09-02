// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Gen0078D1C0
{
public:
	Gen0078D1C0();
};

class GameWindow
{
public:
	GameWindow();
	virtual ~GameWindow();

protected:
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
