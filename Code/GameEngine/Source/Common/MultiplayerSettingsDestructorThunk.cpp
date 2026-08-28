// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the retail settings destructor.

class MultiplayerColorList
{
public:
	~MultiplayerColorList();

private:
	unsigned char m_data[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	~MultiplayerColorDefinition();

private:
	unsigned char m_data[0x24];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	unsigned char m_data[0x2c];
};

class __declspec(novtable) MultiplayerSettings : public SubsystemInterface
{
public:
	virtual ~MultiplayerSettings();

private:
	MultiplayerColorList m_colorList;
	MultiplayerColorDefinition m_observerColor;
	MultiplayerColorDefinition m_randomColor;
};

// ??1MultiplayerSettings@@UAE@XZ
MultiplayerSettings::~MultiplayerSettings()
{
}
