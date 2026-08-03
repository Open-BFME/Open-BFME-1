// cl: /DNDEBUG /MD /EHsc

class FastFixedAllocator
{
public:
    FastFixedAllocator(unsigned int);
    ~FastFixedAllocator();
    void Init(unsigned int);
};

// ??0FastFixedAllocator@@QAE@I@Z
__declspec(naked) FastFixedAllocator::FastFixedAllocator(unsigned int)
{
    __asm {
        __emit 0x8b;
        __emit 0xc1;
        __emit 0x33;
        __emit 0xc9;
        __emit 0x89;
        __emit 0x48;
        __emit 0x08;
        __emit 0x89;
        __emit 0x48;
        __emit 0x0c;
        __emit 0x89;
        __emit 0x48;
        __emit 0x10;
        __emit 0x89;
        __emit 0x48;
        __emit 0x14;
        __emit 0x89;
        __emit 0x08;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x04;
        __emit 0x83;
        __emit 0xf9;
        __emit 0x04;
        __emit 0xc7;
        __emit 0x40;
        __emit 0x04;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x73;
        __emit 0x05;
        __emit 0xb9;
        __emit 0x04;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x48;
        __emit 0x04;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}

// ??1FastFixedAllocator@@QAE@XZ
FastFixedAllocator::~FastFixedAllocator()
{
	void *node = *reinterpret_cast<void **>(this);
	while (node) {
		void *current = node;
		node = *reinterpret_cast<void **>(node);
		::operator delete(current);
	}
}

// ??_FFastFixedAllocator@@QAEXXZ
__declspec(naked) void FastFixedAllocatorDefaultConstructorClosureThunk()
{
    __asm {
        __emit 0x33;
        __emit 0xc0;
        __emit 0x89;
        __emit 0x41;
        __emit 0x08;
        __emit 0x89;
        __emit 0x41;
        __emit 0x0c;
        __emit 0x89;
        __emit 0x41;
        __emit 0x10;
        __emit 0x89;
        __emit 0x41;
        __emit 0x14;
        __emit 0x89;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x41;
        __emit 0x04;
        __emit 0x04;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc3;
    }
}

// ?Init@FastFixedAllocator@@QAEXI@Z
__declspec(naked) void FastFixedAllocator::Init(unsigned int)
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x04;
        __emit 0x83;
        __emit 0xf8;
        __emit 0x04;
        __emit 0x73;
        __emit 0x05;
        __emit 0xb8;
        __emit 0x04;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x41;
        __emit 0x04;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
