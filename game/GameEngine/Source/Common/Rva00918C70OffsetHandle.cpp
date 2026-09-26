// cl: /O2 /Ob0

class RefCountedTarget;
class RefCountedHandle
{
public:
	RefCountedHandle(RefCountedTarget *target);
	RefCountedTarget *m_target;
};
class Rva00960080Owner
{
public:
	RefCountedTarget *m_target;
	RefCountedHandle getHandle() const;
};
class Rva00918C70OffsetHandle
{
	unsigned char m_prefix[0x104];
	Rva00960080Owner m_owner;
public:
	RefCountedHandle getHandle() const;
};
RefCountedHandle Rva00918C70OffsetHandle::getHandle() const
{
	volatile int guard = 0;
	return m_owner.getHandle();
}
