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

}

// TransitionDamageFX.h's three element structs, named outside an anonymous
// namespace (whose decorated name changes with the source path).  Retail's
// incremental-link thunk table confirms each decorated name exactly
// (tools/ilt_oracle.py): ctors 0x00252360 / 0x00252380 / 0x002523A0 and dtors
// 0x00252370 / 0x00252390 / 0x002523B0, reached through ILTs 0x00007BAD /
// 0x000302D8 / 0x00016158 and 0x0001074E / 0x00015703 / 0x0002E451.  As in
// the header, the ctor and dtor are the implicit ones.
struct FXDamageFXListInfo
{
	void *m_value;
	unsigned char m_locationType;
	unsigned char m_padding_05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_padding_0d[3];
	TransitionDamageFXCoord m_location;
};

struct FXDamageOCLInfo
{
	void *m_value;
	unsigned char m_locationType;
	unsigned char m_padding_05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_padding_0d[3];
	TransitionDamageFXCoord m_location;
};

struct FXDamageParticleSystemInfo
{
	void *m_value;
	unsigned char m_locationType;
	unsigned char m_padding_05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_padding_0d[3];
	TransitionDamageFXCoord m_location;
};

// The four-element damage-flag arrays are _STL::vector<AsciiString>: retail
// builds them through ILT 0x0003469E and destroys them through ILT 0x00026AB2,
// which the ledger records as that vector's default-constructor closure and
// destructor.  The closure exists because the constructor takes a defaulted
// allocator.  Including <vector> would pull STLport's inline __copy_backward
// into the m_tail.erase() call below, so only the layout and the two
// out-of-line members this TU names are spelled here (STLport 4.5 layout:
// start, finish, end of storage).
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class Alloc> class vector;

template <>
class vector<AsciiString, allocator<AsciiString> >
{
public:
	explicit vector(const allocator<AsciiString> &a = allocator<AsciiString>());
	~vector();

private:
	AsciiString *_M_start;
	AsciiString *_M_finish;
	AsciiString *_M_end_of_storage;
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
	FXDamageFXListInfo m_fxList[0x30];
	int volatile m_fxListFlags;
	FXDamageOCLInfo m_ocl[0x30];
	int volatile m_oclFlags;
	FXDamageParticleSystemInfo m_particleSystem[0x30];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_damageFlags[4];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_damageParticleFlags[4];
	TensileFormationUpdateMember m_tail;
};

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
