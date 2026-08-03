// cl: /DNDEBUG /MD /EHsc

// Standalone TU for exact retail FastFixedAllocator bodies (Open-BFME5).
// Layout matches lotrbfme.exe: chunks@0, esize@4, stats@8/c/10, head@14.

class FastFixedAllocator
{
public:
	FastFixedAllocator(unsigned int);
	~FastFixedAllocator();
	void Init(unsigned int);
<<<<<<< HEAD
	// MSVC default-ctor closure (??_F...); object-symbol maps retail name here.
	void DefaultConstructorClosure();
=======
>>>>>>> d27c2f84c (Open-BFME5 convert FastFixedAllocator Init/ctor to clean C++)

protected:
	struct Link
	{
		Link *next;
	};

	struct Chunk
	{
		enum { size = 8 * 1024 - 16 };
		Chunk *next;
		char mem[size];
	};

	Chunk *chunks;
	unsigned int esize;
	unsigned TotalHeapSize;
	unsigned TotalAllocatedSize;
	unsigned TotalAllocationCount;
	Link *head;
};

// ??0FastFixedAllocator@@QAE@I@Z
// Retail zeros stats/head/chunks, stages esize=1, then Init(n) => esize = max(n, 4).
FastFixedAllocator::FastFixedAllocator(unsigned int n)
{
	TotalHeapSize = 0;
	TotalAllocatedSize = 0;
	TotalAllocationCount = 0;
	head = 0;
	chunks = 0;
	esize = 1;
	Init(n);
}

// ??1FastFixedAllocator@@QAE@XZ
<<<<<<< HEAD
// Walk chunks list; operator-delete each POD node (no Chunk dtor).
=======
>>>>>>> d27c2f84c (Open-BFME5 convert FastFixedAllocator Init/ctor to clean C++)
FastFixedAllocator::~FastFixedAllocator()
{
	Chunk *n = chunks;
	while (n) {
		Chunk *p = n;
		n = n->next;
		delete p;
	}
}

// ??_FFastFixedAllocator@@QAEXXZ
<<<<<<< HEAD
// Default-ctor closure for FastFixedAllocator() / FastFixedAllocator(0):
// zero stats/head/chunks and set esize=4 (sizeof(Link*)).
// object-symbol=?DefaultConstructorClosure@FastFixedAllocator@@QAEXXZ
void FastFixedAllocator::DefaultConstructorClosure()
{
	TotalHeapSize = 0;
	TotalAllocatedSize = 0;
	TotalAllocationCount = 0;
	head = 0;
	chunks = 0;
	esize = 4;
}

// ?Init@FastFixedAllocator@@QAEXI@Z
void FastFixedAllocator::Init(unsigned int size)
{
	if (size < 4) {
		size = 4;
	}
	*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 4) = size;
}
