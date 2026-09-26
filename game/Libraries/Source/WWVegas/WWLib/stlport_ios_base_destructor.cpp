// ??1ios_base@_STL@@UAE@XZ
// cl: /O2 /Ob2 /EHsc /MD
// STLport 4.5.3
// The compiler barrier in basic_string's destructor emits no instruction. It
// preserves the real second nontrivial member lifetime in the flattened
// reconstruction, so VC7.1 assigns the same EH cleanup state as retail.

extern "C" __declspec(dllimport) void __cdecl bfmeFree1035(void *p);
void __cdecl operator delete(void *p);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

template <int Instance>
class _STLP_mutex_spin
{
public:
	static void __cdecl _M_do_lock(volatile long *lock);
};

class NodeAllocMutex
{
};

template <bool Threads, int Instance>
class _Node_Alloc_Lock
{
public:
	static NodeAllocMutex _S_lock;
};

template <bool Threads, int Instance>
NodeAllocMutex _Node_Alloc_Lock<Threads, Instance>::_S_lock;

template <bool Threads, int Instance>
class __node_alloc
{
public:
	struct _Obj
	{
		_Obj *_M_free_list_link;
	};

	static _Obj *_S_free_list[0x10];
};

template <class CharT>
class char_traits
{
};

template <class CharT>
class allocator
{
};

template <class CharT>
inline void _Destroy(CharT *first, CharT *last)
{
	first;
	last;
}

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Alloc>
class _String_base
{
public:
	__forceinline ~_String_base() __declspec(nothrow)
	{
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	__forceinline ~basic_string()
	{
		_Destroy(this->_M_start, this->_M_finish + 1);
		_ReadWriteBarrier();
	}
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class locale
{
public:
	~locale() __declspec(nothrow);

private:
	void *_M_impl;
};

class ios_base
{
public:
	enum event { erase_event = 0, imbue_event = 1, copyfmt_event = 2 };
	typedef void (*event_callback)(event, ios_base &, int);

	virtual ~ios_base();

private:
	struct Callback
	{
		event_callback fn;
		int index;
	};

	int _M_fmtflags;
	int _M_iostate;
	int _M_openmode;
	int _M_seekdir;
	int _M_exception_mask;
	int _M_precision;
	int _M_width;
	locale _M_locale;
	Callback *_M_callbacks;
	unsigned int _M_num_callbacks;
	unsigned int _M_callback_index;
	long *_M_iwords;
	unsigned int _M_num_iwords;
	void **_M_pwords;
	unsigned int _M_num_pwords;
	void *_M_cached_ctype;
	void *_M_cached_numpunct;
	string _M_cached_grouping;
};

ios_base::~ios_base()
{
	unsigned int n = _M_callback_index;
	if (n > 0)
	{
		do
		{
			Callback *slot = _M_callbacks + n;
			event_callback fn = slot[-1].fn;
			int index = slot[-1].index;
			fn(erase_event, *this, index);
			--n;
		}
		while (n);
	}

	bfmeFree1035(_M_callbacks);
	bfmeFree1035(_M_iwords);
	bfmeFree1035(_M_pwords);

	char *start = _M_cached_grouping._M_start;
	unsigned int bytes = (unsigned int)(_M_cached_grouping._M_end_of_storage._M_data - start);
	if (start != 0)
	{
		if (bytes > 0x80)
		{
			operator delete(start);
		}
		else
		{
			typedef __node_alloc<true, 0>::_Obj Node;
			Node *volatile *my_free_list =
				__node_alloc<true, 0>::_S_free_list + ((bytes - 1) >> 3);
			_STLP_mutex_spin<0>::_M_do_lock(
				(volatile long *)&_Node_Alloc_Lock<true, 0>::_S_lock);
			((Node *)start)->_M_free_list_link = *my_free_list;
			*my_free_list = (Node *)start;
			*(volatile long *)&_Node_Alloc_Lock<true, 0>::_S_lock = 0;
		}
	}
}

}
