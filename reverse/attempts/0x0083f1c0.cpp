// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// partial score=0.977 date=2026-09-25
// cl: /O2 /MD
// Open-BFME5: STLport ios_base::register_callback, retail 0x0083F1C0, 132
// bytes. The grown pair is copied into a block-local before the member stores
// (STLport's by-value pair from _Stl_expand_array); without that copy MSVC
// reloads grown.first before the second callback field store.

namespace _STL
{

template <class T>
struct GrowPair
{
	T *first;
	unsigned int second;
};

template <class T>
GrowPair<T> *grow_array(GrowPair<T> *, T *, unsigned int, unsigned int);

typedef void (__cdecl *IosBaseErrorCall)(void *, void *);
extern IosBaseErrorCall g_call;
extern void *g_global;

struct Callback;

class ios_base
{
public:
	enum event { erase_event = 0, imbue_event = 1, copyfmt_event = 2 };
	typedef void (*event_callback)(event, ios_base &, int);

	void register_callback(event_callback fn, int index);

private:
	char m_vtable[4];
	int m_fmtflags;
	int m_iostate;
	int m_openmode;
	int m_seekdir;
	int m_exception_mask;
	int m_precision;
	int m_width;
	char m_locale[4];
	Callback *m_callbacks;
	unsigned int m_num_callbacks;
	unsigned int m_callback_index;
	long *m_iwords;
	unsigned int m_num_iwords;
	void **m_pwords;
	unsigned int m_num_pwords;
};

struct Callback
{
	ios_base::event_callback fn;
	int index;
};

void ios_base::register_callback(event_callback fn, int index)
{
	GrowPair<Callback> grown;
	grow_array(&grown, m_callbacks, m_num_callbacks, m_callback_index);
	if (grown.first)
	{
		GrowPair<Callback> tmp = grown;
		m_num_callbacks = tmp.second;
		m_callbacks = tmp.first;
		Callback cb = { fn, index };
		m_callbacks[m_callback_index++] = cb;
		return;
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		g_call((void *)0x0112EBAC, (char *)g_global + 0x40);
}

}
