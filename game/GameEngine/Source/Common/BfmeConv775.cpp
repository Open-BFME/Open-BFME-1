// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GlobalWeatherSystem.h
// Declaration only: the spelling of the reference this call site makes. The
// definition is GlobalWeatherSystemSetWeather.cpp's body at 0x0039B090, which
// this TU does not include; retail encodes the call through its ILT thunk
// 0x0003DB77.
class GlobalWeatherSystem
{
public:
	void setWeather(int weather);
};

struct BfmeThingDSP
{
	void bfmeGoDSP();
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

void BfmeThingDSP::bfmeGoDSP()
{
	void *p = m_bfmeP;
	m_bfmeP = 0;
	reinterpret_cast<GlobalWeatherSystem *>(reinterpret_cast<char *>(this) - 8)
		->setWeather((int)p);
}