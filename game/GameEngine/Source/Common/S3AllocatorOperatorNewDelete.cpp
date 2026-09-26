// Four 20-byte cdecl bodies at 0x007F0130, 0x007F0150, 0x007F0170 and
// 0x007F0190, all the same shape:
//
//     call Gen007EFFC0            fetch the allocator
//     mov ecx, [esp + 4]          the one argument
//     push 0
//     push ecx
//     call [vftable + 8 or + 0xC] allocate or release, with a flags of 0
//
// The allocator is the one S3PolymorphicArrayClear.cpp and the V2/Y2 FESL
// sources already use: slot 2 is allocate(size, flags) and slot 3 is
// release(block, flags). A cdecl function that takes a size and returns what
// allocate returned is a class operator new; one that takes a pointer and
// hands it to release is a class operator delete. Both mangle as static
// members, which is what SAPAXI@Z and SAXPAX@Z are.
//
// The first two bodies are byte-identical to each other and so are the last
// two, so nothing in the image pairs a new with its matching delete -- these
// are four separate functions the linker did not fold. Each is therefore named
// after its own address rather than guessed into two classes.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate(unsigned int size, int flags);
	virtual void release(void *block, int flags);
};

extern GenAlloc *Gen007EFFC0();

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class Gen007F0150
{
public:
	static void *operator new(unsigned int size);
};

class Gen007F0170
{
public:
	static void operator delete(void *block);
};

class Gen007F0190
{
public:
	static void operator delete(void *block);
};

// ??2Gen007F0130@@SAPAXI@Z
void *Gen007F0130::operator new(unsigned int size)
{
	return Gen007EFFC0()->allocate(size, 0);
}

// ??2Gen007F0150@@SAPAXI@Z
void *Gen007F0150::operator new(unsigned int size)
{
	return Gen007EFFC0()->allocate(size, 0);
}

// ??3Gen007F0170@@SAXPAX@Z
void Gen007F0170::operator delete(void *block)
{
	Gen007EFFC0()->release(block, 0);
}

// ??3Gen007F0190@@SAXPAX@Z
void Gen007F0190::operator delete(void *block)
{
	Gen007EFFC0()->release(block, 0);
}
