// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0026B230 is a guarded back-pointer dispatch.  The bytes prove the
// owner read at this-8, the owner's +0x1A4 gate, the Object accessor at
// 0x001BFE20, and a declaration-only virtual view whose used slot is +0x1CC.
// The returned object's method fills a three-pointer STLport vector temporary;
// this TU reconstructs that temporary and its retail cleanup without emitting
// a guessed vtable or claiming an unresolved class identity.

extern void __cdecl operator delete(void *);

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int bytes);
};
}

struct Rva0026B230Vector
{
	Rva0026B230Vector() : m_start(0), m_finish(0), m_end(0) {}

	~Rva0026B230Vector()
	{
		int *start = m_start;
		if (start != 0)
		{
			unsigned int bytes = static_cast<unsigned int>((m_end - start) * 4);
			if (bytes > 0x80)
				::operator delete(start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(start, bytes);
		}
	}

	int *m_start;
	int *m_finish;
	int *m_end;
};

class Player
{
public:
#define Rva0026B230Slot(N) virtual void slot##N() = 0;
	Rva0026B230Slot(000) Rva0026B230Slot(001) Rva0026B230Slot(002) Rva0026B230Slot(003)
	Rva0026B230Slot(004) Rva0026B230Slot(005) Rva0026B230Slot(006) Rva0026B230Slot(007)
	Rva0026B230Slot(008) Rva0026B230Slot(009) Rva0026B230Slot(010) Rva0026B230Slot(011)
	Rva0026B230Slot(012) Rva0026B230Slot(013) Rva0026B230Slot(014) Rva0026B230Slot(015)
	Rva0026B230Slot(016) Rva0026B230Slot(017) Rva0026B230Slot(018) Rva0026B230Slot(019)
	Rva0026B230Slot(020) Rva0026B230Slot(021) Rva0026B230Slot(022) Rva0026B230Slot(023)
	Rva0026B230Slot(024) Rva0026B230Slot(025) Rva0026B230Slot(026) Rva0026B230Slot(027)
	Rva0026B230Slot(028) Rva0026B230Slot(029) Rva0026B230Slot(030) Rva0026B230Slot(031)
	Rva0026B230Slot(032) Rva0026B230Slot(033) Rva0026B230Slot(034) Rva0026B230Slot(035)
	Rva0026B230Slot(036) Rva0026B230Slot(037) Rva0026B230Slot(038) Rva0026B230Slot(039)
	Rva0026B230Slot(040) Rva0026B230Slot(041) Rva0026B230Slot(042) Rva0026B230Slot(043)
	Rva0026B230Slot(044) Rva0026B230Slot(045) Rva0026B230Slot(046) Rva0026B230Slot(047)
	Rva0026B230Slot(048) Rva0026B230Slot(049) Rva0026B230Slot(050) Rva0026B230Slot(051)
	Rva0026B230Slot(052) Rva0026B230Slot(053) Rva0026B230Slot(054) Rva0026B230Slot(055)
	Rva0026B230Slot(056) Rva0026B230Slot(057) Rva0026B230Slot(058) Rva0026B230Slot(059)
	Rva0026B230Slot(060) Rva0026B230Slot(061) Rva0026B230Slot(062) Rva0026B230Slot(063)
	Rva0026B230Slot(064) Rva0026B230Slot(065) Rva0026B230Slot(066) Rva0026B230Slot(067)
	Rva0026B230Slot(068) Rva0026B230Slot(069) Rva0026B230Slot(070) Rva0026B230Slot(071)
	Rva0026B230Slot(072) Rva0026B230Slot(073) Rva0026B230Slot(074) Rva0026B230Slot(075)
	Rva0026B230Slot(076) Rva0026B230Slot(077) Rva0026B230Slot(078) Rva0026B230Slot(079)
	Rva0026B230Slot(080) Rva0026B230Slot(081) Rva0026B230Slot(082) Rva0026B230Slot(083)
	Rva0026B230Slot(084) Rva0026B230Slot(085) Rva0026B230Slot(086) Rva0026B230Slot(087)
	Rva0026B230Slot(088) Rva0026B230Slot(089) Rva0026B230Slot(090) Rva0026B230Slot(091)
	Rva0026B230Slot(092) Rva0026B230Slot(093) Rva0026B230Slot(094) Rva0026B230Slot(095)
	Rva0026B230Slot(096) Rva0026B230Slot(097) Rva0026B230Slot(098) Rva0026B230Slot(099)
	Rva0026B230Slot(100) Rva0026B230Slot(101) Rva0026B230Slot(102) Rva0026B230Slot(103)
	Rva0026B230Slot(104) Rva0026B230Slot(105) Rva0026B230Slot(106) Rva0026B230Slot(107)
	Rva0026B230Slot(108) Rva0026B230Slot(109) Rva0026B230Slot(110) Rva0026B230Slot(111)
	Rva0026B230Slot(112) Rva0026B230Slot(113) Rva0026B230Slot(114)
#undef Rva0026B230Slot
	virtual void collect(Rva0026B230Vector *values) = 0;
};

class Object
{
public:
	Player *unidentified_001BFE20() const;

	char m_prefix[0x1A4];
	int m_gate;
};

class Rva0026B230Dispatcher
{
public:
	void run(int unused);
};

void Rva0026B230Dispatcher::run(int)
{
	Object *object = *(Object **)((char *)this - 8);
	if (object->m_gate != 0)
		return;

	Player *player = object->unidentified_001BFE20();
	if (player == 0)
		return;

	Rva0026B230Vector values;
	player->collect(&values);
}
