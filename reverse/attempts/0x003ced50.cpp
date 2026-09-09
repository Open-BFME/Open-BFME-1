// ??0LargeGroupAudioMap@@QAE@VAsciiStringVZ@@@Z
// partial score=0.55 date=2026-09-08
// LargeGroupAudioMap constructor, retail 0x003CED50.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

template <class T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

private:
	char *m_data;
};

class AsciiStringVZ : private StringBase<char>
{
public:
	AsciiStringVZ() : StringBase<char>() {}
	AsciiStringVZ(const AsciiStringVZ &other) : StringBase<char>(other) {}
	~AsciiStringVZ() {}
};

class LargeGroupAudioMap
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();

	LargeGroupAudioMap(AsciiStringVZ name);
	virtual ~LargeGroupAudioMap();

private:
	void *m_owner;
	unsigned char m_isOverride;
	unsigned char m_pad09[3];
	float m_size;
	float m_maximumAudioSpeed;
	AsciiStringVZ m_soundName;
	unsigned int m_sound[3];
	unsigned int m_requiredModelConditions[10];
	unsigned int m_excludedModelConditions[10];
	unsigned int m_requiredObjectStatus[3];
	unsigned int m_excludedObjectStatus[3];
	int m_startThreshold;
	int m_stopThreshold;
	unsigned short m_handOffModeDuration;
	unsigned char m_ignoreStealthedUnits;
	unsigned char m_pad97;
	float m_cachedSpeed[4];
};

LargeGroupAudioMap::LargeGroupAudioMap(AsciiStringVZ name) :
	m_soundName(name)
{
	m_owner = 0;
	m_isOverride = 0;
	m_size = 10000.0f;
	m_maximumAudioSpeed =
		*(const float *)0x012B48F0 * *(const float *)0x010977E0;

	m_sound[0] = 0;
	m_sound[1] = 0;
	m_sound[2] = 0;

	m_requiredModelConditions[0] = 0;
	m_requiredModelConditions[1] = 0;
	m_requiredModelConditions[2] = 0;
	m_requiredModelConditions[3] = 0;
	m_requiredModelConditions[4] = 0;
	m_requiredModelConditions[5] = 0;
	m_requiredModelConditions[6] = 0;
	m_requiredModelConditions[7] = 0;
	m_requiredModelConditions[8] = 0;
	m_requiredModelConditions[9] = 0;

	m_excludedModelConditions[0] = 0;
	m_excludedModelConditions[1] = 0;
	m_excludedModelConditions[2] = 0;
	m_excludedModelConditions[3] = 0;
	m_excludedModelConditions[4] = 0;
	m_excludedModelConditions[5] = 0;
	m_excludedModelConditions[6] = 0;
	m_excludedModelConditions[7] = 0;
	m_excludedModelConditions[8] = 0;
	m_excludedModelConditions[9] = 0;

	m_requiredObjectStatus[0] = 0;
	m_requiredObjectStatus[1] = 0;
	m_requiredObjectStatus[2] = 0;
	m_excludedObjectStatus[0] = 0;
	m_excludedObjectStatus[1] = 0;
	m_excludedObjectStatus[2] = 0;

	m_cachedSpeed[0] = -1.0f;
	m_cachedSpeed[1] = -1.0f;
	m_cachedSpeed[2] = -1.0f;
	m_cachedSpeed[3] = -1.0f;
	m_startThreshold = 40000;
	m_stopThreshold = 10;
	m_handOffModeDuration = 10;
	m_ignoreStealthedUnits = 1;
}
