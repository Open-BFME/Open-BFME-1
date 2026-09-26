// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??1SpecialPowerTemplate@@: game/GameEngine/Source/Common/RTS/SpecialPower.cpp
// Open-BFME5: retail-layout C++ conversion of the SpecialPowerTemplate destructor.

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
private:
	unsigned char m_data[0x70];

public:
	// Non-virtual local view: retail encodes the ILT at 0x00026F35,
	// which the ledger names ??1AudioEventRTS@@QAE@XZ for the body at
	// 0x000B31F0. The vptr the virtual spelling added is folded back
	// into the padding so the layout is unchanged.
	~AudioEventRTS();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
protected:
	__forceinline virtual ~Overridable()
	{
		if (m_nextOverride)
			m_nextOverride->deleteInstance();
		m_nextOverride = 0;
	}

	void deleteInstance()
	{
		delete this;
	}

	Overridable *m_nextOverride;
	bool m_isOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
protected:
	virtual ~SpecialPowerTemplate();

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

// ??1SpecialPowerTemplate@@MAE@XZ
SpecialPowerTemplate::~SpecialPowerTemplate()
{
}
