// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);

private:
	char m_pad[0x70];
};

class Rva006982B0 : public AudioEventRTS
{
	int m_70;
	char m_74;

public:
	Rva006982B0(const Rva006982B0 &other);
};

Rva006982B0::Rva006982B0(const Rva006982B0 &other)
	: AudioEventRTS(other)
	, m_70(other.m_70)
	, m_74(other.m_74)
{
}
