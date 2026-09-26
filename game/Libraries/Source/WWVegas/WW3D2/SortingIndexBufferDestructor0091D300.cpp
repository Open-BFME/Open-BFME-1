// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME7: SortingIndexBufferClass::~SortingIndexBufferClass at 0x0091D300
// (74 B). Retail inlines the base IndexBufferClass destructor (the three
// file-static counters _IndexBufferCount / _IndexBufferTotalIndices /
// _IndexBufferTotalSize at VA 0x01346720 / 0x0134671C / 0x01346728 and the
// base vtable store) into the derived destructor, which the ported
// dx8indexbuffer.cpp does not because its base destructor is out of line.
// Layout: RefCountClass vptr/NumRefs, engine_refs +8, index_count +0xc,
// type +0x10, index_buffer +0x14; index_count is a full int here.
extern void __cdecl operator delete[](void *) throw();

static int _IndexBufferCount;
static int _IndexBufferTotalIndices;
static int _IndexBufferTotalSize;

class RefCountClass
{
public:
	virtual ~RefCountClass() {}
	int NumRefs;
};

class IndexBufferClass : public RefCountClass
{
public:
	virtual ~IndexBufferClass()
	{
		_IndexBufferCount--;
		_IndexBufferTotalIndices -= index_count;
		_IndexBufferTotalSize -= index_count * sizeof(unsigned short);
	}
	int engine_refs;
	int index_count;
	unsigned int type;
};

class SortingIndexBufferClass : public IndexBufferClass
{
public:
	virtual ~SortingIndexBufferClass();
	unsigned short *index_buffer;
};

SortingIndexBufferClass::~SortingIndexBufferClass()
{
	delete[] index_buffer;
}
