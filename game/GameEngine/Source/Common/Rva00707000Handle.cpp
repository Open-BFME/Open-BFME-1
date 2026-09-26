// The three byte-identical 28-byte refcounting getters at 0x00707000,
// 0x00960080 and 0x00975050. Same shape as RefCountedHandleGetters.cpp
// (29B with the pointer at +0x24) except the pointer lives at offset 0:
//
//     push ecx / mov ecx,[ecx] / test ecx,ecx / mov eax,[esp+8]
//     mov dword ptr [esp],0 / mov [eax],ecx / je done
//     inc word ptr [ecx+4]
//     done: pop ecx / ret 4

class RefCountedTarget
{
public:
	int m_first;
	unsigned short m_refCount;
	unsigned short m_pad;
};

class RefCountedHandle
{
public:
	RefCountedHandle( RefCountedTarget *target );
	RefCountedTarget *m_target;
};

// ??0RefCountedHandle@@QAE@PAVRefCountedTarget@@@Z absent-from-retail
inline RefCountedHandle::RefCountedHandle( RefCountedTarget *target ) : m_target( target )
{
	if ( m_target )
	{
		++m_target->m_refCount;
	}
}

class Rva00707000Owner
{
public:
	RefCountedTarget *m_target;
	RefCountedHandle getHandle() const;
};

RefCountedHandle Rva00707000Owner::getHandle() const
{
	volatile int guard = 0;
	return RefCountedHandle( m_target );
}

class Rva00960080Owner
{
public:
	RefCountedTarget *m_target;
	RefCountedHandle getHandle() const;
};

RefCountedHandle Rva00960080Owner::getHandle() const
{
	volatile int guard = 0;
	return RefCountedHandle( m_target );
}

class Rva00975050Owner
{
public:
	RefCountedTarget *m_target;
	RefCountedHandle getHandle() const;
};

RefCountedHandle Rva00975050Owner::getHandle() const
{
	volatile int guard = 0;
	return RefCountedHandle( m_target );
}
