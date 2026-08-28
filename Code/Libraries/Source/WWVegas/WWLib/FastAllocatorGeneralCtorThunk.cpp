// cl: /DNDEBUG /MD /EHsc

// One 24-byte fixed-size pool per allocation bucket. The element has both a
// constructor and a destructor, so the array member below is built through
// `eh vector constructor iterator' (??_L) rather than the plain ??_H form.
class FastAllocatorPool
{
public:
    FastAllocatorPool();
    ~FastAllocatorPool();

    unsigned int m_head;
    unsigned int m_allocSize;
    unsigned int m_reserved[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/FastAllocator.h
class FastAllocatorGeneral
{
public:
    FastAllocatorGeneral();

    FastAllocatorPool m_pools[128];
    void *m_freeLists[128];
    char m_initialized;
    int m_totalAllocs;
    int m_totalFrees;
    int m_totalBytes;
};

// ??0FastAllocatorGeneral@@QAE@XZ
FastAllocatorGeneral::FastAllocatorGeneral()
{
    // Retail keeps an explicit store loop here (lea/xor/mov-add-dec-jne) and
    // holds the zero in ecx so the four scalar stores below can reuse it. Any
    // plain zero-fill loop is folded to `rep stosd` by MSVC 7.1's memset idiom,
    // so the volatile qualifier is a codegen pin, not a semantic claim.
    void *volatile *freeList = m_freeLists;
    int remaining = 128;
    do {
        *freeList = 0;
        ++freeList;
    } while (--remaining);

    m_initialized = 0;
    m_totalAllocs = 0;
    m_totalFrees = 0;
    m_totalBytes = 0;

    unsigned int size = 16;
    for (int i = 0; i < 128; ++i) {
        m_pools[i].m_allocSize = size < 4 ? 4 : size;
        size += 16;
    }
}
