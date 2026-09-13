// stlport
// Open-BFME: retail-layout reconstruction of
// ??0GenericObjectCreationNugget@@QAE@XZ at 0x001D7D70.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <vector>

template <class T>
class StringBase
{
friend class AsciiString;

public:
	void releaseBuffer();

private:
	StringBase(const StringBase<T> &);
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

	static const AsciiString TheEmptyString;

private:
	char *m_text;
};

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &, int);
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

struct RetailCoord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct RetailTailWords
{
	unsigned int word0;
	unsigned int word1;
	unsigned int word2;
	unsigned int word3;

	RetailTailWords()
		: word0(0), word1(0), word2(0), word3(0)
	{
	}
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();

protected:
	virtual ~GenericObjectCreationNugget();

private:
	std::vector<AsciiString> m_names;
	AsciiString m_putInContainer;
	struct AnimSet
	{
		AsciiString m_animInitial;
		AsciiString m_animFlying;
		AsciiString m_animFinal;
	};
	std::vector<AnimSet> m_animSets;
	void *m_fxFinal;
	AsciiString m_particleSysName;
	int m_debrisToGenerate;
	float m_mass;
	float m_extraBounciness;
	RetailCoord3D m_offset;
	int m_disposition;
	float m_dispositionIntensity;
	float m_spinRate;
	float m_yawRate;
	float m_rollRate;
	float m_pitchRate;
	float m_minPitch;
	float m_maxPitch;
	unsigned int m_minFrames;
	unsigned int m_maxFrames;
	int m_shadowType;
	int m_minLODRequired;
	unsigned int m_invulnerableTime;
	float m_minHealth;
	float m_maxHealth;
	unsigned int m_fadeFrames;
	AsciiString m_fadeSoundName;
	RetailTailWords m_tailWords;
	AudioEventRTS m_bounceSound;
	unsigned char m_flag104;
	unsigned char m_flag105;
	unsigned char m_flag106;
	unsigned char m_flag107;
	unsigned char m_flag108;
	unsigned char m_flag109;
	unsigned char m_flag10a;
	unsigned char m_flag10b;
	unsigned char m_flag10c;
	unsigned char m_flag10d;
	unsigned short m_pad10e;
	unsigned int m_word110;
	unsigned char m_flag114;
	unsigned char m_flag115;
	unsigned char m_flag116;
	unsigned char m_flag117;
	unsigned char m_flag118;
	unsigned char m_flag119;
	unsigned char m_flag11a;
	unsigned char m_pad11b;
	unsigned int m_word11c;
	std::bitset<320> m_retailTail;
};

GenericObjectCreationNugget::GenericObjectCreationNugget()
	: m_putInContainer(AsciiString::TheEmptyString),
	  m_animSets(),
	  m_fxFinal(0),
	  m_particleSysName(AsciiString::TheEmptyString),
	  m_debrisToGenerate(1),
	  m_mass(0.0f),
	  m_extraBounciness(0.0f),
	  m_disposition(2),
	  m_dispositionIntensity(0.0f),
	  m_spinRate(0.0f),
	  m_yawRate(1.0f),
	  m_rollRate(0.0f),
	  m_pitchRate(0.0f),
	  m_minPitch(0.0f),
	  m_maxPitch(0.0f),
	  m_minFrames(0),
	  m_maxFrames(0),
	  m_shadowType(0),
	  m_minLODRequired(1),
	  m_invulnerableTime(0),
	  m_minHealth(1.0f),
	  m_maxHealth(1.0f),
	  m_fadeFrames(0),
	  m_fadeSoundName(AsciiString::TheEmptyString),
	  m_tailWords(),
	  m_bounceSound(AsciiString::TheEmptyString, 0),
	  m_flag104(0),
	  m_flag105(0),
	  m_flag106(0),
	  m_flag107(0),
	  m_flag108(0),
	  m_flag109(0),
	  m_flag10a(1),
	  m_flag10b(0),
	  m_flag10c(0),
	  m_flag10d(0),
	  m_word110(0),
	  m_flag114(1),
	  m_flag115(0),
	  m_flag116(0),
	  m_flag117(0),
	  m_flag118(0),
	  m_flag119(0),
	  m_flag11a(0),
	  m_pad11b(0),
	  m_word11c(0),
	  m_retailTail()
{
	m_offset.zero();
}
