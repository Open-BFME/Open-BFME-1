// 0x007EB2C0: reset the global object and release its guarded resources.
// The barrier preserves retail's store-before-flag-read instruction order.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class T_007ea120
{
public:
	virtual void vslot0(int value);
	void m(void);
};

struct Rva0130A588State
{
	T_007ea120 *m_obj;
	char m_flagC;
	char m_flagD;
};

extern Rva0130A588State g_Va0130A588;

extern void Rva007EB830Release(void);
extern void Rva007F0060(void);

class Rva007EB2C0Object
{
public:
	virtual ~Rva007EB2C0Object();
};

Rva007EB2C0Object::~Rva007EB2C0Object()
{
	if (g_Va0130A588.m_obj)
	{
		g_Va0130A588.m_obj->m();
		if (g_Va0130A588.m_obj)
			g_Va0130A588.m_obj->vslot0(1);
		g_Va0130A588.m_obj = 0;
	}
	_ReadWriteBarrier();

	if (g_Va0130A588.m_flagD)
		Rva007EB830Release();

	if (g_Va0130A588.m_flagC)
		Rva007F0060();
}
