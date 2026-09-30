// cl: /O2 /MD

// Open-BFME5: STLport ios_base callback-array grow, retail 0x0083EF20, 147
// bytes. The live zero-valued Callback temporary is intentional: it preserves
// the retail register allocation through the callback-pair tail fill.

// Retail calls MSVCR71.dll!realloc through IAT 0x01359474.
#include <stdlib.h>

namespace _STL
{

struct Callback
{
	typedef void (*event_callback)(int, void *, int);
	event_callback fn;
	int index;
	Callback() : fn(0), index(0) {}
};

template <class T>
struct GrowPair
{
	T *first;
	unsigned int second;
};

template <class T>
inline const T &stlp_max(const T &a, const T &b)
{
	return a < b ? b : a;
}

template <class T>
GrowPair<T> *grow_array(GrowPair<T> *out, T *old_ptr, unsigned int old_count, unsigned int index)
{
	if ((int)old_count < (int)(index + 1))
	{
		unsigned int needed = index + 1;
		unsigned int grown = old_count + old_count;
		unsigned int count = stlp_max(grown, needed);
		unsigned int bytes = count * sizeof(T);
		T *p = (T *)realloc(old_ptr, bytes);
		if (p != 0)
		{
			Callback zero;
			T *end = (T *)(count * sizeof(T) + (unsigned int)p);
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

			out->second = count;
			out->first = p;
			return out;
		}

		out->first = 0;
		out->second = 0;
		return out;
	}

	out->second = old_count;
	out->first = old_ptr;
	return out;
}

template GrowPair<Callback> *grow_array(GrowPair<Callback> *, Callback *, unsigned int, unsigned int);

}
