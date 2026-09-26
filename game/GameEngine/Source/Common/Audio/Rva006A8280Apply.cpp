// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006A8280: mutex-guarded 8-byte vector upsert.
// Identity is NOT recovered: class and method names are address-derived.
//
// Layout is the same owner as landed 0x006A5600 (dirty +0x636, mutex +0x95C,
// 8-byte vector +0xADC).  Arg1 is a pointer key, arg2 a float clamped to
// [0, 1] except the exact-1.0 path which calls vtable slot 0x160.
//
// 0x01075334 is 1.0f (bits 0x3f800000); 0x01075350 is 0.0f (bits 0).
// push_back is the already-matched 8-byte POD vector at 0x006A7170.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern float g_bfmeDefaultBU; // retail 0x01075334, 1.0f
extern float g_bfmeDefaultBR; // retail 0x01075350, 0.0f

struct Gen_t_006a7170_p8pod
{
	void *key;
	float value;
};

namespace _STL
{
template<class T>
class allocator
{
};

template<class T, class A>
class vector
{
public:
	void push_back(const T &value);

	T *_M_start;
	T *volatile _M_finish;
	T *_M_end_of_storage;
};
}

typedef _STL::vector<Gen_t_006a7170_p8pod, _STL::allocator<Gen_t_006a7170_p8pod> >
	Rva006A8280Vec;

class Rva006A8280ScopedMutex
{
	void *m_mutex;
	unsigned char m_held;

public:
	__forceinline Rva006A8280ScopedMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	__forceinline ~Rva006A8280ScopedMutex()
	{
		if (m_held)
			ReleaseMutex(m_mutex);
	}
};

class Rva006A8280Owner
{
public:
#define RVA006A8280_SLOT(n) virtual void pad##n();
	RVA006A8280_SLOT(00) RVA006A8280_SLOT(01) RVA006A8280_SLOT(02) RVA006A8280_SLOT(03)
	RVA006A8280_SLOT(04) RVA006A8280_SLOT(05) RVA006A8280_SLOT(06) RVA006A8280_SLOT(07)
	RVA006A8280_SLOT(08) RVA006A8280_SLOT(09) RVA006A8280_SLOT(10) RVA006A8280_SLOT(11)
	RVA006A8280_SLOT(12) RVA006A8280_SLOT(13) RVA006A8280_SLOT(14) RVA006A8280_SLOT(15)
	RVA006A8280_SLOT(16) RVA006A8280_SLOT(17) RVA006A8280_SLOT(18) RVA006A8280_SLOT(19)
	RVA006A8280_SLOT(20) RVA006A8280_SLOT(21) RVA006A8280_SLOT(22) RVA006A8280_SLOT(23)
	RVA006A8280_SLOT(24) RVA006A8280_SLOT(25) RVA006A8280_SLOT(26) RVA006A8280_SLOT(27)
	RVA006A8280_SLOT(28) RVA006A8280_SLOT(29) RVA006A8280_SLOT(30) RVA006A8280_SLOT(31)
	RVA006A8280_SLOT(32) RVA006A8280_SLOT(33) RVA006A8280_SLOT(34) RVA006A8280_SLOT(35)
	RVA006A8280_SLOT(36) RVA006A8280_SLOT(37) RVA006A8280_SLOT(38) RVA006A8280_SLOT(39)
	RVA006A8280_SLOT(40) RVA006A8280_SLOT(41) RVA006A8280_SLOT(42) RVA006A8280_SLOT(43)
	RVA006A8280_SLOT(44) RVA006A8280_SLOT(45) RVA006A8280_SLOT(46) RVA006A8280_SLOT(47)
	RVA006A8280_SLOT(48) RVA006A8280_SLOT(49) RVA006A8280_SLOT(50) RVA006A8280_SLOT(51)
	RVA006A8280_SLOT(52) RVA006A8280_SLOT(53) RVA006A8280_SLOT(54) RVA006A8280_SLOT(55)
	RVA006A8280_SLOT(56) RVA006A8280_SLOT(57) RVA006A8280_SLOT(58) RVA006A8280_SLOT(59)
	RVA006A8280_SLOT(60) RVA006A8280_SLOT(61) RVA006A8280_SLOT(62) RVA006A8280_SLOT(63)
	RVA006A8280_SLOT(64) RVA006A8280_SLOT(65) RVA006A8280_SLOT(66) RVA006A8280_SLOT(67)
	RVA006A8280_SLOT(68) RVA006A8280_SLOT(69) RVA006A8280_SLOT(70) RVA006A8280_SLOT(71)
	RVA006A8280_SLOT(72) RVA006A8280_SLOT(73) RVA006A8280_SLOT(74) RVA006A8280_SLOT(75)
	RVA006A8280_SLOT(76) RVA006A8280_SLOT(77) RVA006A8280_SLOT(78) RVA006A8280_SLOT(79)
	RVA006A8280_SLOT(80) RVA006A8280_SLOT(81) RVA006A8280_SLOT(82) RVA006A8280_SLOT(83)
	RVA006A8280_SLOT(84) RVA006A8280_SLOT(85) RVA006A8280_SLOT(86) RVA006A8280_SLOT(87)
#undef RVA006A8280_SLOT
	virtual void onUnit(void *key);

	void apply(void *key, float value);

	// vptr at +0; dirty is still +0x636 from the object start.
	char m_pad636[0x632];
	unsigned char m_dirty;
	char m_pad638[0x95c - 0x638];
	void *m_mutex;
	char m_pad960[0xadc - 0x960];
	Rva006A8280Vec m_vector;
};

// ?apply@Rva006A8280Owner@@QAEXPAXM@Z
void Rva006A8280Owner::apply(void *key, float value)
{
	Rva006A8280ScopedMutex guard(m_mutex);
	Gen_t_006a7170_p8pod *item;

	if (key)
	{
		if (value == g_bfmeDefaultBU)
		{
			onUnit(key);
		}
		else
		{
			if (value > g_bfmeDefaultBU)
				value = g_bfmeDefaultBU;
			else if (value < g_bfmeDefaultBR)
				value = g_bfmeDefaultBR;

			item = m_vector._M_start;
			if (item != m_vector._M_finish)
			{
				do
				{
					if (item->key == key)
						goto found;
					++item;
				}
				while (item != m_vector._M_finish);
			}

			{
				Gen_t_006a7170_p8pod tmp;
				tmp.value = value;
				tmp.key = key;
				m_vector.push_back(tmp);
			}
			m_dirty = 1;
		}
	}
	return;
found:
	if (item->value != value)
	{
		item->value = value;
		m_dirty = 1;
	}
}
