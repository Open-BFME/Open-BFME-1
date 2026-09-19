// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0020FA70AllocProxy
{
public:
	void *base() const;
};

void *Rva0020FA70AllocProxy::base() const
{
	return (char *)this + 0x30;
}
