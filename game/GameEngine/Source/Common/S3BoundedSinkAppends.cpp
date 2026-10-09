// Twelve 37-byte bodies with one shape:
//
//     edx = m_last - 4;  eax = m_cur
//     if (eax == edx) tail-jump to the aux                one element short
//     if (eax) *eax = *arg;                               placement-new's null test
//     m_cur += 4;
//
// which is STLport's deque<T>::push_back: write into the finish iterator's
// current slot unless it is the last one in the node, and hand the awkward
// case to _M_push_back_aux_v. The ILTs the tail jumps go through are pinned
// with exactly that name for three deque instantiations, so the shape is not
// in doubt; what the bytes cannot say is WHICH instantiation each of these
// twelve is, since identical-code folding put several on the same aux.
//
// Two consequences for the ledger. The element is four bytes wide (the sub of
// 4 and the add of 4) and the argument is dereferenced once, so it arrives by
// reference -- modelled here as void * rather than guessed into a class. And
// the five-byte tail jump at +0x20 belongs to this body: the je inside it
// branches there. It had been claimed as a standalone gap thunk, retired in
// the previous commit.
//
// The linker left twelve separate copies, so each takes its name from its own
// address.

typedef int Int;

// Exact matched auxiliary declarations; keep these calls out of line.
class Gen_00089d90;
class Gen_0035b840;
class Gen_0035b870;
class Gen_0035bb10;
class Gen_0035bb40;
class Gen_0035c3a0;
class Gen_0035c3d0;
class Gen_0035c840;
class Gen_0035c870;
class Gen_00369a30;
class Gen_00369e30;
class Gen_00647430;
class MapObject;
struct Gen_t_00089ce0_p4pod;
struct Gen_t_0035ae40_p4pod;
struct Gen_t_0035aec0_p4pod;
struct Gen_t_0035b2a0_p4pod;
struct Gen_t_0035b320_p4pod;
namespace _STL
{
template <class Value> class allocator;
template <class Value, class Alloc> class deque
{
    friend class ::Gen_00089d90;
    friend class ::Gen_0035b840;
    friend class ::Gen_0035b870;
    friend class ::Gen_0035bb10;
    friend class ::Gen_0035bb40;
    friend class ::Gen_0035c3a0;
    friend class ::Gen_0035c3d0;
    friend class ::Gen_0035c840;
    friend class ::Gen_0035c870;
    friend class ::Gen_00369a30;
    friend class ::Gen_00369e30;
    friend class ::Gen_00647430;
protected:
    void _M_push_back_aux_v(const Value &);
};
}

class Gen_00089d90
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035b840
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035b870
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035bb10
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035bb40
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035c3a0
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035c3d0
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035c840
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_0035c870
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_00369a30
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_00369e30
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

class Gen_00647430
{
public:
	void bfmeAppend(void *const &value);

private:
	char m_bfmeHead[0x10];
	void **m_bfmeCur;							// +0x10
	char m_bfmeMid[0x18 - 0x14];
	void **m_bfmeLast;							// +0x18
};

// ?bfmeAppend@Gen_00089d90@@QAEXABQAX@Z
void Gen_00089d90::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_00089ce0_p4pod, _STL::allocator<Gen_t_00089ce0_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_00089ce0_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035b840@@QAEXABQAX@Z
void Gen_0035b840::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035ae40_p4pod, _STL::allocator<Gen_t_0035ae40_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035ae40_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035b870@@QAEXABQAX@Z
void Gen_0035b870::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035aec0_p4pod, _STL::allocator<Gen_t_0035aec0_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035aec0_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035bb10@@QAEXABQAX@Z
void Gen_0035bb10::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035b2a0_p4pod, _STL::allocator<Gen_t_0035b2a0_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035b2a0_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035bb40@@QAEXABQAX@Z
void Gen_0035bb40::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035b320_p4pod, _STL::allocator<Gen_t_0035b320_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035b320_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035c3a0@@QAEXABQAX@Z
void Gen_0035c3a0::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035ae40_p4pod, _STL::allocator<Gen_t_0035ae40_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035ae40_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035c3d0@@QAEXABQAX@Z
void Gen_0035c3d0::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035aec0_p4pod, _STL::allocator<Gen_t_0035aec0_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035aec0_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035c840@@QAEXABQAX@Z
void Gen_0035c840::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035b2a0_p4pod, _STL::allocator<Gen_t_0035b2a0_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035b2a0_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_0035c870@@QAEXABQAX@Z
void Gen_0035c870::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<Gen_t_0035b320_p4pod, _STL::allocator<Gen_t_0035b320_p4pod> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const Gen_t_0035b320_p4pod &>(value));
	}
}

// ?bfmeAppend@Gen_00369a30@@QAEXABQAX@Z
void Gen_00369a30::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<MapObject *, _STL::allocator<MapObject *> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<MapObject *const &>(value));
	}
}

// ?bfmeAppend@Gen_00369e30@@QAEXABQAX@Z
void Gen_00369e30::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<MapObject *, _STL::allocator<MapObject *> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<MapObject *const &>(value));
	}
}

// ?bfmeAppend@Gen_00647430@@QAEXABQAX@Z
void Gen_00647430::bfmeAppend(void *const &value)
{
	if (m_bfmeCur != m_bfmeLast - 1)
	{
		if (m_bfmeCur)
			*m_bfmeCur = value;

		++m_bfmeCur;
	}
	else
	{
		reinterpret_cast<_STL::deque<int, _STL::allocator<int> > *>(this)
            ->_M_push_back_aux_v(reinterpret_cast<const int &>(value));
	}
}
