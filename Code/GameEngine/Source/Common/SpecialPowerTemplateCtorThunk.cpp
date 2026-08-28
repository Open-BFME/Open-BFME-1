// cl: /DNDEBUG /MD /EHsc
// readable body of ??0SpecialPowerTemplate@@: Code/GameEngine/Source/Common/RTS/SpecialPower.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	__forceinline AsciiString() : m_text(0) {}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
private:
	unsigned char m_data[0x6c];

public:
	AudioEventRTS(void *allocator = (void *)0x01336e50, int zero = 0);
	virtual ~AudioEventRTS();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
protected:
	__forceinline Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();

	Overridable *m_nextOverride;
	bool m_isOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerTemplate();

private:
	AsciiString m_name;
	int m_id;
	int m_type;
	int m_reloadTime;
	int m_requiredScience;
	int m_academyClassificationType;
	AudioEventRTS m_initiateSound;
	AudioEventRTS m_initiateAtLocationSound;
	int m_detectionTime;
	int m_viewObjectDuration;
	float m_viewObjectRange;
	float m_radiusCursorRadius;
	bool m_publicTimer;
	bool m_sharedNSync;
	bool m_shortcutPower;
	AsciiString m_tail;
};

// ??0SpecialPowerTemplate@@QAE@XZ
SpecialPowerTemplate::SpecialPowerTemplate()
{
	m_id = 0;
	m_type = 0;
	m_reloadTime = 0;
	m_requiredScience = -1;
	m_academyClassificationType = 0;
	m_publicTimer = false;
	m_detectionTime = 50;
	m_sharedNSync = false;
	m_viewObjectDuration = 0;
	m_viewObjectRange = 0.0f;
	m_radiusCursorRadius = 0.0f;
}
