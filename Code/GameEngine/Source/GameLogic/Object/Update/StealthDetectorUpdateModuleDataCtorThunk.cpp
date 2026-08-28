// cl: /DNDEBUG /MD /EHsc
// stlport

#include <bitset>

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

template <unsigned int BitCount>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	BitFlags() {}

	void clear()
	{
		m_bits.reset();
	}

private:
	std::bitset<BitCount> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleData
{
public:
	virtual ~UpdateModuleData() {}

private:
	unsigned int m_moduleTagNameKey;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthDetectorUpdate.h
class StealthDetectorUpdateModuleData : public UpdateModuleData
{
public:
	StealthDetectorUpdateModuleData();

private:
	unsigned int m_updateRate;
	float m_detectionRange;
	bool m_initiallyDisabled;
	AudioEventRTS m_pingSound;
	AudioEventRTS m_loudPingSound;
	const void *m_IRBeaconParticleSysTmpl;
	const void *m_IRParticleSysTmpl;
	const void *m_IRBrightParticleSysTmpl;
	const void *m_IRGridParticleSysTmpl;
	AsciiString m_IRParticleSysBone;
	KindOfMaskType m_extraDetectKindof;
	KindOfMaskType m_extraDetectKindofNot;
	bool m_canDetectWhileGarrisoned;
	bool m_canDetectWhileTransported;
	bool m_canDetectWhileContained;
};

// ??0StealthDetectorUpdateModuleData@@QAE@XZ
StealthDetectorUpdateModuleData::StealthDetectorUpdateModuleData()
{
	m_updateRate = 1;
	m_detectionRange = 0.0f;
	m_initiallyDisabled = false;
	m_IRBeaconParticleSysTmpl = 0;
	m_IRParticleSysTmpl = 0;
	m_IRBrightParticleSysTmpl = 0;
	m_IRGridParticleSysTmpl = 0;
	m_extraDetectKindof.clear();
	m_extraDetectKindofNot.clear();
	m_canDetectWhileGarrisoned = false;
	m_canDetectWhileTransported = false;
	m_canDetectWhileContained = false;
}
