// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// partial score=0.8 date=2026-09-06
// cl: /O2 /Ob0 /MD
// Open-BFME5: STLport ios_base::iword, retail 0x0083F0C0, 117 bytes.

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

class ios_base
{
public:
	enum event { erase_event = 0, imbue_event = 1, copyfmt_event = 2 };
	typedef void (*event_callback)(event, ios_base &, int);

	long &iword(int index);
	void *&pword(int index);
	void register_callback(event_callback fn, int index);

private:
	struct Callback
	{
		event_callback fn;
		int index;
	};

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

long &ios_base::iword(int index)
{
	GrowPair<long> grown;
	grow_array(&grown, m_iwords, m_num_iwords, index);
	if (grown.first)
	{
		m_iwords = grown.first;
		m_num_iwords = grown.second;
		return m_iwords[index];
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		g_call((void *)0x0112EBAC, (char *)g_global + 0x40);
	return *(long *)0x0130BD24;
}

void *&ios_base::pword(int index)
{
	GrowPair<void *> grown;
	grow_array(&grown, m_pwords, m_num_pwords, index);
	if (grown.first)
	{
		m_pwords = grown.first;
		m_num_pwords = grown.second;
		return m_pwords[index];
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		g_call((void *)0x0112EBAC, (char *)g_global + 0x40);
	return *(void **)0x0130BD28;
}

void ios_base::register_callback(event_callback fn, int index)
{
	GrowPair<Callback> grown;
	grow_array(&grown, m_callbacks, m_num_callbacks, m_callback_index);
	if (grown.first)
	{
		Callback *new_callbacks = grown.first;
		m_num_callbacks = grown.second;
		m_callbacks = new_callbacks;
		new_callbacks[m_callback_index].fn = fn;
		new_callbacks[m_callback_index].index = index;
		++m_callback_index;
		return;
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		g_call((void *)0x0112EBAC, (char *)g_global + 0x40);
}

}
