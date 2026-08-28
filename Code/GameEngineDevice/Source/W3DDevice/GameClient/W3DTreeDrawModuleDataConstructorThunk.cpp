// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DTreeDrawModuleData@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTreeDraw.cpp

class Buffer
{
public:
	Buffer() : m_data(0) {}
	~Buffer();
	void clear();

private:
	void *m_data;
};

class W3DTreeDrawModuleDataBase
{
public:
	virtual ~W3DTreeDrawModuleDataBase() {}

private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTreeDraw.h
class W3DTreeDrawModuleData : public W3DTreeDrawModuleDataBase
{
public:
	W3DTreeDrawModuleData();
	virtual ~W3DTreeDrawModuleData();

private:
	Buffer m_modelName;
	Buffer m_textureName;
	unsigned int m_framesToMoveOutward;
	unsigned int m_framesToMoveInward;
	float m_maxOutwardMovement;
	float m_darkening;
	void *m_toppleFX;
	void *m_bounceFX;
	Buffer m_stumpName;
	float m_initialVelocityPercent;
	float m_initialAccelPercent;
	float m_bounceVelocityPercent;
	float m_minimumToppleSpeed;
	bool m_killWhenToppled;
	bool m_doTopple;
	unsigned char m_pad3e[2];
	unsigned int m_sinkFrames;
	float m_sinkDistance;
	Buffer m_bfmeName;
	unsigned int m_bfmeFrames;
	unsigned int m_bfmeZero;
	bool m_doShadow;
	unsigned char m_pad55[3];
	unsigned int m_bfmeFive;
	unsigned int m_bfmeHundredFive;
	float m_bfmeForty;
};

W3DTreeDrawModuleData::W3DTreeDrawModuleData() :
	m_framesToMoveOutward(1),
	m_framesToMoveInward(1),
	m_maxOutwardMovement(1.0f),
	m_darkening(0.0f)
{
	m_toppleFX = 0;
	m_bounceFX = 0;
	m_stumpName.clear();
	m_killWhenToppled = true;
	m_doTopple = false;
	m_bfmeZero = 0;
	m_doShadow = false;
	m_initialVelocityPercent = 0.2f;
	m_initialAccelPercent = 0.01f;
	m_bounceVelocityPercent = 0.3f;
	m_minimumToppleSpeed = 0.5f;
	m_sinkFrames = 50;
	m_sinkDistance = 20.0f;
	m_bfmeFrames = 50;
	m_bfmeFive = 5;
	m_bfmeHundredFive = 105;
	m_bfmeForty = 40.0f;
}
