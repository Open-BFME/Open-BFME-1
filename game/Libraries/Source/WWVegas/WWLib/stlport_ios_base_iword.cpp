// cl: /MD /G6 /Ob1
// stlport
// STLport ios_base auxiliary slots and callback registration.
// BFME 2 donor: 1e726cf7cf299ff126c390e7dbed212200903c24.
// BFME 1 identity/ABI evidence: targets/game/reverse/identity_evidence/0x0083f1c0-ios-callback.md
#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS
#include <ios>
#include <stdio.h>
#include <stdlib.h>
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

// Preserve the existing BFME 1 fallback data owners.
long g_0130BD24 = 0;
void *g_0130BD28 = 0;

long &ios_base::iword(int index)
{
	GrowPair<long> grown;
	grow_array(&grown, _M_iwords, _M_num_iwords, index);
	if (grown.first)
	{
		_M_iwords = grown.first;
		_M_num_iwords = grown.second;
		return _M_iwords[index];
	}

	_M_iostate |= 1;
	if (_M_iostate & _M_exception_mask)
		::fputs("ios failure", stderr);
	return g_0130BD24;
}

void *&ios_base::pword(int index)
{
	GrowPair<void *> grown;
	grow_array(&grown, _M_pwords, _M_num_pwords, index);
	if (grown.first)
	{
		_M_pwords = grown.first;
		_M_num_pwords = grown.second;
		return _M_pwords[index];
	}

	_M_iostate |= 1;
	if (_M_iostate & _M_exception_mask)
		::fputs("ios failure", stderr);
	return g_0130BD28;
}

// The helper's original spelling is unproven. Return the actual non-POD
// STLport pair so MSVC supplies the retail hidden result argument.
template <class T>
inline const T &stlp_max(const T &a, const T &b)
{
	return a < b ? b : a;
}

template <class T>
__declspec(noinline) pair<T *, unsigned> rva0083EF20(T *old_ptr, unsigned old_count, unsigned index)
{
	if ((int)old_count < (int)(index + 1))
	{
		unsigned needed = index + 1;
		unsigned grown = old_count + old_count;
		unsigned count = stlp_max(grown, needed);
		unsigned bytes = count * sizeof(T);
		T *p = (T *)::realloc(old_ptr, bytes);
		if (p)
		{
			T zero = T();
			T *end = (T *)(count * sizeof(T) + (unsigned)p);
			T *dst = p + old_count;
			if (dst != end)
			{
				do
				{
					*dst = zero;
					++dst;
				}
				while (dst != end);
			}
			return pair<T *, unsigned>(p, count);
		}
		return pair<T *, unsigned>(0, 0);
	}
	return pair<T *, unsigned>(old_ptr, old_count);
}

void ios_base::register_callback(event_callback fn, int index)
{
	typedef pair<event_callback, int> Callback;
	pair<Callback *, unsigned> grown = rva0083EF20(_M_callbacks, _M_num_callbacks, _M_callback_index);
	if (grown.first)
	{
		pair<Callback *, unsigned> tmp = grown;
		_M_num_callbacks = tmp.second;
		_M_callbacks = tmp.first;
		Callback cb;
		cb.first = fn;
		cb.second = index;
		_M_callbacks[_M_callback_index++] = cb;
		return;
	}
	_M_iostate |= 1;
	if (_M_iostate & _M_exception_mask)
		::fputs("ios failure", stderr);
}

}
