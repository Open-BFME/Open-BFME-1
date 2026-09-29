// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct HideShowSubObjInfo
	{
		unsigned int vtable;
		unsigned int flags;
	};
};

struct HideShowSubObjInfoDestroyVTable
{
	virtual void destroy(unsigned int) = 0;
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
	void _M_clear();
};

class ModelConditionInfoHideShowSubObjInfoInsertOverflowShim
{
public:
	void insert_overflow(ModelConditionInfo::HideShowSubObjInfo *pos, const ModelConditionInfo::HideShowSubObjInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end);
	void clear();
};

void vector<ModelConditionInfo::HideShowSubObjInfo, allocator<ModelConditionInfo::HideShowSubObjInfo> >::_M_insert_overflow(
	ModelConditionInfo::HideShowSubObjInfo *pos, const ModelConditionInfo::HideShowSubObjInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((ModelConditionInfoHideShowSubObjInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}

void vector<ModelConditionInfo::HideShowSubObjInfo, allocator<ModelConditionInfo::HideShowSubObjInfo> >::_M_clear()
{
	((ModelConditionInfoHideShowSubObjInfoInsertOverflowShim *)this)->clear();
}

void ModelConditionInfoHideShowSubObjInfoInsertOverflowShim::clear()
{
	typedef ModelConditionInfo::HideShowSubObjInfo Element;
	struct VectorLayout
	{
		Element *start;
		Element *finish;
		Element *end;
	};

	VectorLayout *vector = reinterpret_cast<VectorLayout *>(this);
	Element *first = vector->start;
	Element *last = vector->finish;
	while (first != last)
	{
		reinterpret_cast<HideShowSubObjInfoDestroyVTable *>(first)->destroy(0);
		++first;
	}

	Element *start = vector->start;
	if (start != 0)
	{
		unsigned int bytes = static_cast<unsigned int>((vector->end - start) * sizeof(Element));
		if (bytes > 0x80)
		{
			::operator delete(start);
		}
		else
		{
			_STL::nodePoolDeallocate(start, bytes);
		}
	}
}
}
