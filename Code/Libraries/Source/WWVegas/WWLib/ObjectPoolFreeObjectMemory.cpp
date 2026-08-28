// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ObjectPoolClass<HAnimComboDataClass,256>::Free_Object_Memory,
// retail 0x00973E90, 38 bytes.
//
// mempool.h's template, and the frame confirms its member order: FreeListHead
// at +0x00, BlockListHead at +0x04, FreeObjectCount at +0x08, TotalObjectCount
// at +0x0C and the critical section at +0x10.
//
// BFME's mutex.h is not the reference's. There the LockClass constructor is a
// block of inline asm around a `bts` spin; here it is a call to a private
// static taking the flag by pointer -- `lea edi, [esi+0x10]` then a __fastcall
// through the ILT at 0x00026FA8, which the ledger already names
// ?spin@LockClass@FastCriticalSectionClass@@CIXPAI@Z. The destructor is
// unchanged: the lone `mov dword ptr [edi], 0` at the end.
//
// The same template lands twice, byte for byte, at two addresses the linker
// never folded: 0x00973E90 for HAnimComboDataClass and 0x009DBEB0 for
// MultiListNodeClass, whose pool is the one multilist.h's
// `AutoPoolClass<MultiListNodeClass, 256>` base carries and whose two callers
// are both inside GenericMultiListClass::Internal_Remove.
//
// Six more instantiations land the same 38 bytes elsewhere. Four of them --
// AABTreeLinkClass, AABTreeNodeClass, CameraShakeSystemClass::CameraShakerClass
// and GenericSLNode -- were folded onto one body at 0x006D1480, which is why
// four names share it; PolyRenderTaskClass at 0x009452A0 and MatPassTaskClass
// at 0x009453B0 kept their own copies. All eight differ only in the
// relocation on the spin call. GridLinkClass keeps its own copy too, right
// behind its allocator at 0x008DDA50.

typedef unsigned int uint32;

class HAnimComboDataClass;
class MultiListNodeClass;
class AABTreeLinkClass;
class AABTreeNodeClass;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/camerashakesystem.h
class CameraShakeSystemClass
{
public:
	class CameraShakerClass;
};
class GenericSLNode;
class GridLinkClass;
class PolyRenderTaskClass;
class MatPassTaskClass;

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
	void		Free_Object_Memory(T * obj);

protected:

	T	*		FreeListHead;			
	uint32 *	BlockListHead;			
	int		FreeObjectCount;
	int		TotalObjectCount;
	FastCriticalSectionClass ObjectPoolCS;

};

template<class T,int BLOCK_SIZE> 
void ObjectPoolClass<T,BLOCK_SIZE>::Free_Object_Memory(T * obj)
{
	FastCriticalSectionClass::LockClass lock(ObjectPoolCS);

	*(T**)(obj) = FreeListHead;		// Link to the Head
	FreeListHead = obj;					// Set the Head
	FreeObjectCount++;
}

template void ObjectPoolClass<HAnimComboDataClass,256>::Free_Object_Memory(HAnimComboDataClass *);
template void ObjectPoolClass<MultiListNodeClass,256>::Free_Object_Memory(MultiListNodeClass *);
template void ObjectPoolClass<AABTreeLinkClass,256>::Free_Object_Memory(AABTreeLinkClass *);
template void ObjectPoolClass<AABTreeNodeClass,256>::Free_Object_Memory(AABTreeNodeClass *);
template void ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::Free_Object_Memory(CameraShakeSystemClass::CameraShakerClass *);
template void ObjectPoolClass<GenericSLNode,256>::Free_Object_Memory(GenericSLNode *);
template void ObjectPoolClass<GridLinkClass,256>::Free_Object_Memory(GridLinkClass *);
template void ObjectPoolClass<PolyRenderTaskClass,256>::Free_Object_Memory(PolyRenderTaskClass *);
template void ObjectPoolClass<MatPassTaskClass,256>::Free_Object_Memory(MatPassTaskClass *);
