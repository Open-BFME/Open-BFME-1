// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: Radar::isRadarWindow

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
public:
	bool isRadarWindow(GameWindow *window);

private:
	unsigned char m_pad[0x1438];
	GameWindow *m_radarWindow;
};

// ?isRadarWindow@Radar@@QAE_NPAVGameWindow@@@Z
bool Radar::isRadarWindow(GameWindow *window)
{
	GameWindow *r = m_radarWindow;
	return r == window && r != 0;
}
