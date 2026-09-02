// cl: /O2 /Ob0 /EHsc /MD

// Open-BFME5: _STL::ios_base::ios_base, retail 0x0083F6B0, 125 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real. Callers at 0x0083FA80 / 0x0083FAE0 (basic_ios char and
// wchar constructors) both go through it.
//
// After the vptr it zeros seven dwords of flags, constructs locale at +0x20,
// zeros the callback / iword / pword / cached-facet pointers, then constructs
// the cached grouping string at +0x48. Those two callees are already matched:
// locale's default constructor at 0x00832120 and basic_string<char>'s at
// 0x004D4F40 (ILT 0x0004048A).

namespace _STL
{

class locale
{
public:
	locale();
	~locale();

private:
	void *_M_impl;
};

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string();
	~basic_string();

private:
	CharT *_M_start;
	CharT *_M_finish;
	CharT *_M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class ios_base
{
protected:
	ios_base();
	virtual ~ios_base();

private:
	int _M_fmtflags;
	int _M_iostate;
	int _M_openmode;
	int _M_seekdir;
	int _M_exception_mask;
	int _M_precision;
	int _M_width;
	locale _M_locale;
	void *_M_callbacks;
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

// ??0ios_base@_STL@@IAE@XZ
ios_base::ios_base()
	: _M_fmtflags(0),
	  _M_iostate(0),
	  _M_openmode(0),
	  _M_seekdir(0),
	  _M_exception_mask(0),
	  _M_precision(0),
	  _M_width(0),
	  _M_locale(),
	  _M_callbacks(0),
	  _M_num_callbacks(0),
	  _M_callback_index(0),
	  _M_iwords(0),
	  _M_num_iwords(0),
	  _M_pwords(0),
	  _M_num_pwords(0),
	  _M_cached_ctype(0),
	  _M_cached_numpunct(0),
	  _M_cached_grouping()
{
}

}
