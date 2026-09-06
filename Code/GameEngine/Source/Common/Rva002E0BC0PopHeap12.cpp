// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: near-twin of bfmePopHeap00531A40 (S4PopHeapElem12.cpp).  Same
// STLport __pop_heap shape over a twelve-byte element, but the element field
// order here matches Code/GameEngine/Source/Common/S4MakeHeap12.cpp's
// S4SortElem12 (int m_a; AsciiString m_name; char m_flag;) instead of the
// (char; AsciiString; int) layout the 0x00531A40 twin uses.  __adjust_heap
// callee is the already-pinned ?Gen002E07A0@@YAXPAUS4SortElem12@@HHU1@
// US4Cmp002E0CD0@@@Z (ILT thunk 0x0002C0CA).

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct S4SortElem12
{
	int m_a;
	AsciiString m_name;
	char m_flag;
};

struct S4Cmp002E0CD0
{
	void *m_state;
	bool operator()(S4SortElem12, S4SortElem12) const;
};

void Gen002E07A0(S4SortElem12 *first, int hole, int len, S4SortElem12 value,
	S4Cmp002E0CD0 comp);

void Rva002E0BC0PopHeap(S4SortElem12 *first, S4SortElem12 *last,
	S4SortElem12 *result, S4SortElem12 value, S4Cmp002E0CD0 comp, int *)
{
	*result = *first;
	Gen002E07A0(first, 0, last - first, value, comp);
}
