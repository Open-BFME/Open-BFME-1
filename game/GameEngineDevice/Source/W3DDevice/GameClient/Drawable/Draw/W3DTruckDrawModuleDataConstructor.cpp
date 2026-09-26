// cl: /DNDEBUG /MD /EHsc
// W3DTruckDrawModuleData constructor at retail 0x0077F830.

struct BfmeAsciiString0077F830
{
	unsigned int m_data;
	BfmeAsciiString0077F830() : m_data(0) {}
};

class W3DSupplyDrawModuleDataBase
{
	char m_bfmeBase[0x158];

public:
	W3DSupplyDrawModuleDataBase();
	virtual ~W3DSupplyDrawModuleDataBase();
};

class W3DTruckDrawModuleData : public W3DSupplyDrawModuleDataBase
{
	BfmeAsciiString0077F830 m_dustEffectName;
	BfmeAsciiString0077F830 m_dirtEffectName;
	BfmeAsciiString0077F830 m_powerslideEffectName;
	BfmeAsciiString0077F830 m_frontLeftTireBoneName;
	BfmeAsciiString0077F830 m_frontRightTireBoneName;
	BfmeAsciiString0077F830 m_rearLeftTireBoneName;
	BfmeAsciiString0077F830 m_rearRightTireBoneName;
	BfmeAsciiString0077F830 m_midFrontLeftTireBoneName;
	BfmeAsciiString0077F830 m_midFrontRightTireBoneName;
	BfmeAsciiString0077F830 m_midRearLeftTireBoneName;
	BfmeAsciiString0077F830 m_midRearRightTireBoneName;
	BfmeAsciiString0077F830 m_midMidLeftTireBoneName;
	BfmeAsciiString0077F830 m_midMidRightTireBoneName;
	BfmeAsciiString0077F830 m_unkString00;
	BfmeAsciiString0077F830 m_unkString01;
	BfmeAsciiString0077F830 m_unkString02;
	BfmeAsciiString0077F830 m_unkString03;
	BfmeAsciiString0077F830 m_unkString04;
	BfmeAsciiString0077F830 m_unkString05;
	BfmeAsciiString0077F830 m_cabBoneName;
	BfmeAsciiString0077F830 m_trailerBoneName;
	float m_cabRotationFactor;
	float m_trailerRotationFactor;
	float m_rotationDampingFactor;
	float m_rotationSpeedMultiplier;
	float m_powerslideRotationAddition;

public:
	W3DTruckDrawModuleData();
	virtual ~W3DTruckDrawModuleData();
};

// ??0W3DTruckDrawModuleData@@QAE@XZ
W3DTruckDrawModuleData::W3DTruckDrawModuleData()
{
	m_cabRotationFactor = 1.0f;
	m_trailerRotationFactor = 1.0f;
	m_rotationDampingFactor = 1.0f;
	m_rotationSpeedMultiplier = 1.0f;
	m_powerslideRotationAddition = 0.0f;
}
