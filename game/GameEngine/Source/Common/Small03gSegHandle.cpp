// cl: /O2 /Ob0
//
// Retail 0x0094FB40 is the +0xE0 handle-forwarding twin of the 0x00918C70
// offset-handle idiom: it shifts the receiver to the subobject at this+0xE0
// and tail-delegates to the pinned getHandle at 0x00960080, returning the
// result through the hidden buffer while the tag word is ignored. The
// argless const spelling is what emits retail's `ret 4` tail and the
// `push ecx / push esi / mov esi,[esp+0xC] / push esi / add ecx,0xE0 /
// mov [esp+8],0 / call / mov eax,esi / pop esi / pop ecx` form; any
// tag-taking spelling emits `ret 8` and drifts. IDENTITY IS NOT RECOVERED:
// the owner keeps its address token.
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

class Rva0094FB40Box
{
	unsigned char m_prefix[0xE0];
	Rva00960080Owner m_owner;
public:
	RefCountedHandle getHandle() const;
};

RefCountedHandle Rva0094FB40Box::getHandle() const
{
	volatile int guard = 0;
	return m_owner.getHandle();
}

class Rva00975050Owner
{
public:
	RefCountedTarget *m_target;
	RefCountedHandle getHandle() const;
};

class Rva00955AB0Box
{
	unsigned char m_prefix[0xE8];
	Rva00975050Owner m_owner;
public:
	RefCountedHandle getHandle() const;
};

RefCountedHandle Rva00955AB0Box::getHandle() const
{
	volatile int guard = 0;
	return m_owner.getHandle();
}
