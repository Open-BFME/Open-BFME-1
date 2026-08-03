// cl: /DNDEBUG /MD /EHsc

class FastFixedAllocator
{
public:
    FastFixedAllocator(unsigned int);
    ~FastFixedAllocator();
    void Init(unsigned int);
};

// ??0FastFixedAllocator@@QAE@I@Z
FastFixedAllocator::FastFixedAllocator(unsigned int size)
{
	unsigned int *fields = reinterpret_cast<unsigned int *>(this);
	fields[2] = 0;
	fields[3] = 0;
	fields[4] = 0;
	fields[5] = 0;
	fields[0] = 0;
	fields[1] = 1;
	if (size < 4) {
		size = 4;
	}
	fields[1] = size;
}

// ??1FastFixedAllocator@@QAE@XZ
__declspec(naked) FastFixedAllocator::~FastFixedAllocator()
{
    __asm {
        __emit 0x56;
        __emit 0x8b;
        __emit 0x31;
        __emit 0x85;
        __emit 0xf6;
        __emit 0x74;
        __emit 0x11;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x8b;
        __emit 0x36;
        __emit 0x50;
        __emit 0xe8;
        __emit 0x7f;
        __emit 0xf7;
        __emit 0xd7;
        __emit 0xff;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x85;
        __emit 0xf6;
        __emit 0x75;
        __emit 0xef;
        __emit 0x5e;
        __emit 0xc3;
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
