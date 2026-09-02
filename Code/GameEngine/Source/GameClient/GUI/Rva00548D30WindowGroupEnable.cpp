// cl: /DNDEBUG /MD /O2 /Ob2

class GameWindow
{
public:
	int winEnable(bool enable);
};

class Rva00548D30WindowGroup
{
private:
	unsigned char m_pad[0x74];
	GameWindow *m_windows[4];

public:
	void winEnable(bool enable);
};

void Rva00548D30WindowGroup::winEnable(bool enable)
{
	if (m_windows[0] != 0) {
		m_windows[0]->winEnable(enable);
	}
	if (m_windows[1] != 0) {
		m_windows[1]->winEnable(enable);
	}
	if (m_windows[2] != 0) {
		m_windows[2]->winEnable(enable);
	}
	if (m_windows[3] != 0) {
		m_windows[3]->winEnable(enable);
	}
}
