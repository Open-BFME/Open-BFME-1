// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::Allocate_Object_Memory,
// retail 0x006D1370, 212 bytes.
//
// mempool.h's other half, over the member order ObjectPoolFreeObjectMemory.cpp
// already measured, and with the same BFME lock: the LockClass constructor is
// a __fastcall to a private static taking the flag by pointer, through the ILT
// at 0x00026FA8, and its destructor is the `mov dword ptr [ebx], 0` at the end.
// Here the pairing needs a real frame, because ::operator new can throw.
//
// The block size is in the allocation: `push 0x3C04` is sizeof(T) * 256 plus
// the four bytes of block link, so T is sixty bytes wide and BLOCK_SIZE is
// 256. That also explains the loop -- unrolled four ways at a stride of 0xF0,
// running to 0x3C78 -- and the 0x100 added to both counts at the end.

typedef unsigned int uint32;

// Three more pools allocate through the same template with a twenty-byte
// element -- GridLinkClass at 0x008DD970, MultiListNodeClass at 0x009DBDD0 and
// HAnimComboDataClass at 0x00973DB0, all asking ::operator new for 0x1404 --
// so those bodies are 210 bytes where this one is 212.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/gridcull.h
class GridLinkClass
{
	char m_bfmeBody[20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListNodeClass
{
	char m_bfmeBody[20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/camerashakesystem.h
class CameraShakeSystemClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/camerashakesystem.h
	class CameraShakerClass
	{
		// Sixty bytes: what the pool's block allocation measures it as.
		char m_bfmeBody[60];
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class FastCriticalSectionClass
{
	unsigned Flag;

public:
	FastCriticalSectionClass() : Flag(0) {}

	class LockClass
	{
		FastCriticalSectionClass& cs;
	public:
		LockClass(FastCriticalSectionClass& critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}

		~LockClass()
		{
			cs.Flag=0;
		}

	private:
		static void __fastcall spin(unsigned *flag);		// ILT 0x00026FA8

		LockClass &operator=(const LockClass&);
		LockClass(const LockClass&);
	};

	friend class LockClass;
};

template<class T,int BLOCK_SIZE = 64>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mempool.h
class ObjectPoolClass
{
public:
	T *		Allocate_Object_Memory(void);

protected:

	T	*		FreeListHead;			
	uint32 *	BlockListHead;			
	int		FreeObjectCount;
	int		TotalObjectCount;
	FastCriticalSectionClass ObjectPoolCS;

};

template<class T,int BLOCK_SIZE> 
T * ObjectPoolClass<T,BLOCK_SIZE>::Allocate_Object_Memory(void)
{
	FastCriticalSectionClass::LockClass lock(ObjectPoolCS);

	if ( FreeListHead == 0 ) {  

		// No free objects, allocate another block
		uint32 * tmp_block_head = BlockListHead;
		BlockListHead = (uint32*)::operator new( sizeof(T) * BLOCK_SIZE + sizeof(uint32 *));
		// Link this block into the block list
		*(void **)BlockListHead = tmp_block_head;

		// Link the objects in the block into the free object list
		FreeListHead = (T*)(BlockListHead + 1);
		for ( int i = 0; i < BLOCK_SIZE; i++ ) {	
			*(T**)(&(FreeListHead[i])) = &(FreeListHead[i+1]);	// link up the elements
		}
		*(T**)(&(FreeListHead[BLOCK_SIZE-1])) = 0;				// Mark the end

		FreeObjectCount += BLOCK_SIZE;
		TotalObjectCount += BLOCK_SIZE;
	}

	T * obj = FreeListHead;						// Get the next free object
	FreeListHead = *(T**)(FreeListHead);	// Bump the Head
	FreeObjectCount--;

	return obj;										
}

template CameraShakeSystemClass::CameraShakerClass * ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::Allocate_Object_Memory(void);
template GridLinkClass * ObjectPoolClass<GridLinkClass,256>::Allocate_Object_Memory(void);
template MultiListNodeClass * ObjectPoolClass<MultiListNodeClass,256>::Allocate_Object_Memory(void);
