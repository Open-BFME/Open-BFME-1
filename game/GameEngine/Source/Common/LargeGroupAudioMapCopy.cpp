// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// LargeGroupAudioMap copy helper, retail 0x003D21C0 (465 bytes).  The parser
// creates an override map with the named constructor, then calls this helper
// to copy the scalar fields and clone every SoundKeyPair.

#define _M_insert_overflow j_000030bc
#include <vector>
#undef _M_insert_overflow

class LargeGroupAudioMap;

extern void j_0000d0b7(void);
extern void j_00023a74(void);

class AsciiString;

template <class Char>
class StringBase
{
public:
	void set(const StringBase<Char> &source);
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&source);
		return *this;
	}

private:
	char *m_data;
};

class SoundKeyPair
{
public:
	SoundKeyPair(LargeGroupAudioMap *owner);

	~SoundKeyPair()
	{
		typedef void (SoundKeyPair::*Destroy)();
		union
		{
			void (*raw)(void);
			Destroy member;
		} target;
		target.raw = j_0000d0b7;
		(this->*target.member)();
	}

private:
	unsigned char m_data[0x3c];
};

class BfmeMapXF
{
public:
	void bfmeAssignXF(const BfmeMapXF &source);
};

class SoundKeyVector : public _STL::vector<SoundKeyPair *,
	_STL::allocator<SoundKeyPair *> >
{
public:
	using _STL::vector<SoundKeyPair *,
		_STL::allocator<SoundKeyPair *> >::_M_start;
	using _STL::vector<SoundKeyPair *,
		_STL::allocator<SoundKeyPair *> >::_M_finish;
	using _STL::vector<SoundKeyPair *,
		_STL::allocator<SoundKeyPair *> >::_M_end_of_storage;
};

struct ConditionFlags
{
	unsigned int m_value[10];
};

struct StatusBits
{
	unsigned int m_value[3];
};

class LargeGroupAudioMap
{
public:
	void copy(const LargeGroupAudioMap &source);

private:
	void *m_vtable;
	void *m_owner;
	unsigned char m_isOverride;
	unsigned char m_pad09[3];
	float m_size;
	float m_maximumAudioSpeed;
	AsciiString m_soundName;
	SoundKeyVector m_sound;
	ConditionFlags m_requiredModelConditions;
	ConditionFlags m_excludedModelConditions;
	StatusBits m_requiredObjectStatus;
	StatusBits m_excludedObjectStatus;
	int m_startThreshold;
	int m_stopThreshold;
	unsigned short m_handOffModeDuration;
	unsigned char m_ignoreStealthedUnits;
	unsigned char m_pad97;
	float m_cachedSpeed[4];
};

static __forceinline void reserveSoundKeys(void *receiver, unsigned int count)
{
	typedef void (SoundKeyVector::*Reserve)(unsigned int);
	union
	{
		void (*raw)(void);
		Reserve member;
	} target;
	target.raw = j_00023a74;
	(reinterpret_cast<SoundKeyVector *>(receiver)->*target.member)(count);
}

// ?copy@LargeGroupAudioMap@@QAEXABV1@@Z
void LargeGroupAudioMap::copy(const LargeGroupAudioMap &source)
{
	if (&source == this)
		return;

	SoundKeyPair **it = m_sound._M_start;
	while (it != m_sound._M_finish)
	{
		SoundKeyPair *pair = *it;
		if (pair)
			delete pair;
		++it;
	}

	m_sound.clear();
	m_cachedSpeed[1] = -1.0f;
	m_cachedSpeed[0] = -1.0f;
	m_cachedSpeed[3] = -1.0f;
	m_cachedSpeed[2] = -1.0f;
	m_size = source.m_size;
	m_maximumAudioSpeed = source.m_maximumAudioSpeed;
	m_soundName = source.m_soundName;
	m_requiredModelConditions = source.m_requiredModelConditions;
	m_excludedModelConditions = source.m_excludedModelConditions;
	m_requiredObjectStatus = source.m_requiredObjectStatus;
	m_excludedObjectStatus = source.m_excludedObjectStatus;
	m_startThreshold = source.m_startThreshold;
	m_stopThreshold = source.m_stopThreshold;
	m_handOffModeDuration = source.m_handOffModeDuration;
	m_ignoreStealthedUnits = source.m_ignoreStealthedUnits;

	unsigned int count = (unsigned int)(source.m_sound._M_finish -
		source.m_sound._M_start);
	reserveSoundKeys(&m_sound, count);
	SoundKeyPair **sourceIt = source.m_sound._M_start;
	while (sourceIt != source.m_sound._M_finish)
	{
		SoundKeyPair *pair = new SoundKeyPair(this);
		m_sound.push_back(pair);
		((BfmeMapXF *)pair)->bfmeAssignXF(
			*(const BfmeMapXF *)*sourceIt);
		++sourceIt;
	}
}
