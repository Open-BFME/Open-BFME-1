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

// Named by retail's hubsingle.cpp assertion; defined in createServiceHubImpl.cpp.
class ServiceHubImpl
{
public:
	static ServiceHubImpl *gInstance;
};

extern unsigned char g_Va0130A58C;
extern unsigned char g_Va0130A58D;

extern void Rva007EB830Release(void);
extern void Rva007F0060(void);

class Rva007EB2C0Object
{
public:
	virtual ~Rva007EB2C0Object();
};

Rva007EB2C0Object::~Rva007EB2C0Object()
{
	if (ServiceHubImpl::gInstance)
	{
		reinterpret_cast<T_007ea120 *>(ServiceHubImpl::gInstance)->m();
		if (ServiceHubImpl::gInstance)
			reinterpret_cast<T_007ea120 *>(ServiceHubImpl::gInstance)->vslot0(1);
		ServiceHubImpl::gInstance = 0;
	}
	_ReadWriteBarrier();

	if (g_Va0130A58D)
		Rva007EB830Release();

	if (g_Va0130A58C)
		Rva007F0060();
}
