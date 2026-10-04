// cl: /DNDEBUG /MD /EHsc
// readable body of ??0GarrisonContainModuleData@@QAE@XZ: game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp

// GarrisonContainModuleData default constructor (0x0022F7E0, 153 B). It first
// runs the 0x2F4-byte base constructor at 0x002472D0 (through ILT 0x0000ED77),
// the body HorseHordeContain::friend_newModuleData allocates and calls, then
// installs vtable 0x010ADE98 and sets its own defaults in field order. BFME's
// layout differs from the Zero Hour header GarrisonContain.cpp compiles
// against, so this TU keeps an offset-named view.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class HorseHordeContainModuleData
{
public:
	HorseHordeContainModuleData();
	virtual ~HorseHordeContainModuleData();

private:
	unsigned char m_pad[0x2f0];
};

class GarrisonContainModuleData : public HorseHordeContainModuleData
{
public:
	GarrisonContainModuleData();
	virtual ~GarrisonContainModuleData();

private:
	unsigned int m_2F4[10];
	float m_31C;
	float m_320;
	unsigned int m_324;
	float m_328;
	int m_32C;
	float m_330;
	float m_334;
	float m_338;
};

GarrisonContainModuleData::GarrisonContainModuleData()
{
	m_2F4[0] = 0;
	m_2F4[1] = 0;
	m_2F4[2] = 0;
	m_2F4[3] = 0;
	m_2F4[4] = 0;
	m_2F4[5] = 0;
	m_2F4[6] = 0;
	m_2F4[7] = 0;
	m_2F4[8] = 0;
	m_2F4[9] = 0;
	m_31C = 1.0f;
	m_320 = 0.45f;
	m_324 = 0;
	m_328 = 999999.0f;
	m_32C = 2;
	m_330 = 1.0f;
	m_334 = 0.3f;
	m_338 = 0.4f;
}
