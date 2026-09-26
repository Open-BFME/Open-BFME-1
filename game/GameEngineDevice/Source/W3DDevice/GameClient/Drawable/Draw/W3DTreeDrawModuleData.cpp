// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail constructor 0x0077F360 (192B) and destructor 0x0077F460 (112B).
// INI table RVA 0x00D25E40 witnesses the member offsets and names, including
// BFME's MorphTree/MorphTime/MorphFX/TaintedTree/Fade* fields. Its four string
// entries at +08/+0C/+28/+48 use INI::parseAsciiString (0x00851EE0).

#include "ascii_string.h"

// Canonical bodies from ascii_string.cpp and string_base.cpp, visible here
// to preserve retail's direct calls to StringBase<char>::releaseBuffer.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

template <typename T> inline void StringBase<T>::clear()
{
	releaseBuffer();
}

class FXList;

class W3DTreeDrawModuleDataBase
{
public:
	virtual ~W3DTreeDrawModuleDataBase() {}

private:
	unsigned char m_pad[4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTreeDraw.h
class W3DTreeDrawModuleData : public W3DTreeDrawModuleDataBase
{
public:
	W3DTreeDrawModuleData();
	virtual ~W3DTreeDrawModuleData();

private:
	AsciiString m_modelName;
	AsciiString m_textureName;
	unsigned int m_framesToMoveOutward;
	unsigned int m_framesToMoveInward;
	float m_maxOutwardMovement;
	float m_darkening;
	void *m_toppleFX;
	void *m_bounceFX;
	AsciiString m_stumpName;
	float m_initialVelocityPercent;
	float m_initialAccelPercent;
	float m_bounceVelocityPercent;
	float m_minimumToppleSpeed;
	bool m_killWhenToppled;
	bool m_doTopple;
	unsigned char m_pad3e[2];
	unsigned int m_sinkFrames;
	float m_sinkDistance;
	AsciiString m_morphTree;
	unsigned int m_morphTime;
	const FXList *m_morphFX;
	bool m_taintedTree;
	unsigned char m_pad55[3];
	unsigned int m_fadeRate;
	unsigned int m_fadeTarget;
	float m_fadeDistance;
};

// ??0W3DTreeDrawModuleData@@QAE@XZ
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
	m_morphFX = 0;
	m_taintedTree = false;
	m_initialVelocityPercent = 0.2f;
	m_initialAccelPercent = 0.01f;
	m_bounceVelocityPercent = 0.3f;
	m_minimumToppleSpeed = 0.5f;
	m_sinkFrames = 50;
	m_sinkDistance = 20.0f;
	m_morphTime = 50;
	m_fadeRate = 5;
	m_fadeTarget = 105;
	m_fadeDistance = 40.0f;
}

// ??1W3DTreeDrawModuleData@@UAE@XZ
W3DTreeDrawModuleData::~W3DTreeDrawModuleData()
{
}
