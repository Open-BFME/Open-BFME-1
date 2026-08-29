// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
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

template <bool Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *, unsigned int);
};

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
			__node_alloc<true, 0>::_M_deallocate(start, bytes);
		}
	}
}
}
