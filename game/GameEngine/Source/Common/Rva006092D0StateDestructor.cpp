// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00609E30 is Rva006092D0State::~Rva006092D0State.
// The scalar deleting destructor at 0x0060A130 calls this body through ILT
// 0x00011356, and the constructor at 0x0060A000 installs vtable 0x01115AD0.
// The curve member starts at +0x18 and owns 16-byte records through +0x20.

#define _STLP_NO_EXCEPTIONS 1

struct GarrisonContain
{
	struct StationPointData
	{
		float m_key;
		int m_value[3];
	};
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
__declspec(nothrow) OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *);

template <>
GarrisonContain::StationPointData *__copy<
	GarrisonContain::StationPointData *,
	GarrisonContain::StationPointData *, int>(
	GarrisonContain::StationPointData *, GarrisonContain::StationPointData *,
	GarrisonContain::StationPointData *, const random_access_iterator_tag &, int *);

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *, unsigned int);
};
}

void __cdecl operator delete(void *);

class BfmeLivingWorldManager
{
public:
	void rva00615850();
};

extern "C" BfmeLivingWorldManager *g_bfmeGameCW;

class Gen_00609320
{
};

extern Gen_00609320 *g_bfmeStateDF;

class ClientSubsystem
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c(int) = 0;
	virtual int slot40() = 0;
};

extern ClientSubsystem *TheAudioClientUpdate;

class Rva0006AB10Curve
{
public:
	__forceinline void clear()
	{
		GarrisonContain::StationPointData *result = m_start;
		GarrisonContain::StationPointData *first = m_finish;
		_STL::random_access_iterator_tag tag;
		int *none = 0;
		m_finish = _STL::__copy(first, first, result, tag, none);
	}

	__forceinline ~Rva0006AB10Curve()
	{
		if (m_start != 0)
		{
			unsigned int bytes = (unsigned int)(m_end - m_start) *
				sizeof(GarrisonContain::StationPointData);
			if (bytes > 128)
				::operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

	int m_field0;
	int m_field4;
	GarrisonContain::StationPointData *m_start;
	GarrisonContain::StationPointData *m_finish;
	GarrisonContain::StationPointData *m_end;
	int m_field14;
	GarrisonContain::StationPointData *m_current;
};

class __declspec(novtable) Rva006092D0State
{
public:
	virtual ~Rva006092D0State();
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0c() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1c() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2c() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3c() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4c() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5c() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68(int) = 0; virtual void slot6c(int) = 0;

private:
	int m_mode;
	char m_padding[0x10];
	Rva0006AB10Curve m_curve;
	char m_tail[0x3c];
};

Rva006092D0State::~Rva006092D0State()
{
	*(unsigned int *)this = 0x01115AD0;
	if (g_bfmeGameCW != 0)
		g_bfmeGameCW->rva00615850();
	if (TheAudioClientUpdate != 0 && TheAudioClientUpdate->slot40() == 1)
		TheAudioClientUpdate->slot3c(2);
	g_bfmeStateDF = 0;
	m_curve.clear();
}
