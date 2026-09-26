// Retail 0x0020FA60 returns the address sixteen bytes before its receiver.
// The surrounding STLport constructor label does not prove a semantic owner.
class Rva0020FA60AllocProxy
{
public:
	void *base(void);
};

void *Rva0020FA60AllocProxy::base(void)
{
	return (char *)this - 0x10;
}
