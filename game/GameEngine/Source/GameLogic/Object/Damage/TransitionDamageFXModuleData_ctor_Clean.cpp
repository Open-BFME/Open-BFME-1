// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

namespace
{

struct TransitionDamageFXCoord
{
	float x;
	float y;
	float z;
};

class TransitionDamageFXRecordA
{
public:
	TransitionDamageFXRecordA();
	~TransitionDamageFXRecordA();

	void *m_value;
	unsigned char m_locationType;
	unsigned char m_padding_05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_padding_0d[3];
	TransitionDamageFXCoord m_location;
};

class TransitionDamageFXRecordB
{
public:
	TransitionDamageFXRecordB();
	~TransitionDamageFXRecordB();

	void *m_value;
	unsigned char m_locationType;
	unsigned char m_padding_05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_padding_0d[3];
	TransitionDamageFXCoord m_location;
};

class TransitionDamageFXRecordC
{
public:
	TransitionDamageFXRecordC();
	~TransitionDamageFXRecordC();

	void *m_value;
	unsigned char m_locationType;
	unsigned char m_padding_05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_padding_0d[3];
	TransitionDamageFXCoord m_location;
};

class TransitionDamageFXFlags
{
public:
	TransitionDamageFXFlags();
	~TransitionDamageFXFlags();

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

}

struct Gen_t_00252ce0_p128pod
{
	int m_key;
	AsciiString m_inner;
	unsigned char m_tail[0x24];
};

class Gen00252DA0
{
public:
	~Gen00252DA0();
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *);

extern template Gen_t_00252ce0_p128pod *__copy_backward<Gen_t_00252ce0_p128pod *, Gen_t_00252ce0_p128pod *, int>(
	Gen_t_00252ce0_p128pod *, Gen_t_00252ce0_p128pod *, Gen_t_00252ce0_p128pod *,
	const random_access_iterator_tag &, int *);
}

namespace
{

class TensileFormationUpdateMember
{
public:
	TensileFormationUpdateMember()
		: m_begin(0), m_end(0), m_capacity(0)
	{
	}

	~TensileFormationUpdateMember();

	Gen_t_00252ce0_p128pod *m_begin;
	Gen_t_00252ce0_p128pod *m_end;
	Gen_t_00252ce0_p128pod *m_capacity;

	void erase()
	{
		Gen_t_00252ce0_p128pod *start = m_begin;
		Gen_t_00252ce0_p128pod *finish = m_end;
		_STL::random_access_iterator_tag tag;
		Gen_t_00252ce0_p128pod *destination = _STL::__copy_backward(
			finish, finish, start, tag, (int *)0);
		Gen_t_00252ce0_p128pod *oldFinish = m_end;
		for (Gen_t_00252ce0_p128pod *current = destination;
			current != oldFinish; ++current)
		{
			reinterpret_cast<Gen00252DA0 *>(
				reinterpret_cast<char *>(current) + 4)->~Gen00252DA0();
		}
		m_end = destination;
	}
};

}

class TransitionDamageFXModuleDataBase
{
public:
	virtual ~TransitionDamageFXModuleDataBase() {}

protected:
	unsigned char m_padding_04[4];
	int volatile m_flags;
};

class TransitionDamageFXModuleData : public TransitionDamageFXModuleDataBase
{
public:
	TransitionDamageFXModuleData();
	virtual ~TransitionDamageFXModuleData();

private:
	TransitionDamageFXRecordA m_fxList[0x30];
	int volatile m_fxListFlags;
	TransitionDamageFXRecordB m_ocl[0x30];
	int volatile m_oclFlags;
	TransitionDamageFXRecordC m_particleSystem[0x30];
	TransitionDamageFXFlags m_damageFlags[4];
	TransitionDamageFXFlags m_damageParticleFlags[4];
	TensileFormationUpdateMember m_tail;
};

// ?TransitionDamageFXRecordA::TransitionDamageFXRecordA present-unmatched
TransitionDamageFXRecordA::TransitionDamageFXRecordA()
	: m_boneName()
{
}

// ?TransitionDamageFXRecordA::~TransitionDamageFXRecordA present-unmatched
TransitionDamageFXRecordA::~TransitionDamageFXRecordA()
{
}

// ?TransitionDamageFXRecordB::TransitionDamageFXRecordB present-unmatched
TransitionDamageFXRecordB::TransitionDamageFXRecordB()
	: m_boneName()
{
}

// ?TransitionDamageFXRecordB::~TransitionDamageFXRecordB present-unmatched
TransitionDamageFXRecordB::~TransitionDamageFXRecordB()
{
}

// ?TransitionDamageFXRecordC::TransitionDamageFXRecordC present-unmatched
TransitionDamageFXRecordC::TransitionDamageFXRecordC()
	: m_boneName()
{
}

// ?TransitionDamageFXRecordC::~TransitionDamageFXRecordC present-unmatched
TransitionDamageFXRecordC::~TransitionDamageFXRecordC()
{
}

// ?TransitionDamageFXFlags::TransitionDamageFXFlags present-unmatched
TransitionDamageFXFlags::TransitionDamageFXFlags()
	: m_begin(0), m_end(0), m_capacity(0)
{
}

// ?TransitionDamageFXFlags::~TransitionDamageFXFlags present-unmatched
TransitionDamageFXFlags::~TransitionDamageFXFlags()
{
}

TransitionDamageFXModuleData::TransitionDamageFXModuleData()
{
	int i;
	int j;

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 12; ++j)
		{
			m_fxList[i * 12 + j].m_value = 0;
			m_fxList[i * 12 + j].m_location.x = 0.0f;
			m_fxList[i * 12 + j].m_location.y = 0.0f;
			m_fxList[i * 12 + j].m_location.z = 0.0f;
			m_fxList[i * 12 + j].m_locationType = 1;
			m_fxList[i * 12 + j].m_randomBone = 0;

			m_ocl[i * 12 + j].m_value = 0;
			m_ocl[i * 12 + j].m_location.x = 0.0f;
			m_ocl[i * 12 + j].m_location.y = 0.0f;
			m_ocl[i * 12 + j].m_location.z = 0.0f;
			m_ocl[i * 12 + j].m_locationType = 1;
			m_ocl[i * 12 + j].m_randomBone = 0;

			m_particleSystem[i * 12 + j].m_value = 0;
			m_particleSystem[i * 12 + j].m_location.x = 0.0f;
			m_particleSystem[i * 12 + j].m_location.y = 0.0f;
			m_particleSystem[i * 12 + j].m_location.z = 0.0f;
			m_particleSystem[i * 12 + j].m_locationType = 1;
			m_particleSystem[i * 12 + j].m_randomBone = 0;
		}
	}

	m_tail.erase();
	m_flags = -1;
	m_fxListFlags = -1;
	m_oclFlags = -1;
}
