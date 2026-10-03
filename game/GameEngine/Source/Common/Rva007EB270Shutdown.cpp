// cl: /O2
// 0x007EB270: tear down the FESL singleton at 0x0130A588 then the two
// neighboring global-release helpers gated by 0x0130A58D / 0x0130A58C.

class T_007ea120
{
public:
	virtual void release(int);
	void m();
};

// Named by retail's hubsingle.cpp assertion; defined in createServiceHubImpl.cpp.
class ServiceHubImpl
{
public:
	static ServiceHubImpl *gInstance;
};
extern unsigned char g_Va0130A58D;
extern unsigned char g_Va0130A58C;

void Rva007EB830Release(void);
void Rva007F0060();

void Rva007EB270Shutdown()
{
	T_007ea120 *p = reinterpret_cast<T_007ea120 *>(ServiceHubImpl::gInstance);
	if (p)
	{
		p->m();
		p = reinterpret_cast<T_007ea120 *>(ServiceHubImpl::gInstance);
		if (p)
			p->release(1);
		ServiceHubImpl::gInstance = 0;
	}
	if (g_Va0130A58D)
		Rva007EB830Release();
	if (g_Va0130A58C)
		Rva007F0060();
}
