// ??$grow_array@J@_STL@@YAPAU?$GrowPair@J@0@PAU10@PAJII@Z
// partial score=0.99 date=2026-09-02
// cl: /O2 /MD

// Open-BFME5: STLport ios_base auxiliary-array grow, three bodies. 0x0083EE00
// and 0x0083EE90 are the four-byte (iword / pword) copies; 0x0083EF20 is the
// eight-byte callback-pair copy. Each returns a {pointer, count} pair in
// memory: if the old count already covers index+1 the old block is handed
// back, otherwise realloc grows to old+needed (or needed on overflow) and
// the new tail is zeroed.

extern "C" __declspec(dllimport) void *__cdecl u2_import_01359474(void *p, unsigned int bytes);

namespace _STL
{

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
		T *p = (T *)u2_import_01359474(old_ptr, bytes);
		if (p != 0)
		{
			T *end = (T *)(bytes + (unsigned int)p);
			T *dst = p + old_count;
			if (dst != end)
			{
				do
				{
					*dst = T();
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

struct Callback
{
	int a;
	int b;
};

template GrowPair<long> *grow_array(GrowPair<long> *, long *, unsigned int, unsigned int);
template GrowPair<void *> *grow_array(GrowPair<void *> *, void **, unsigned int, unsigned int);
template GrowPair<Callback> *grow_array(GrowPair<Callback> *, Callback *, unsigned int, unsigned int);

}
