// Reconstruction shaping: the compiler barrier retains retail loads and the
// empty copy loop without emitted instructions; it is not original-source evidence.
// cl: /DNDEBUG /MD /EHsc
// Retail 0x003BA810: initialize an eight-byte range container and copy the
// empty finish-to-finish range back into its finish pointer.

extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva003BA810Elem
{
	int first;
	int second;
};

inline Rva003BA810Elem *rva003ba810Copy(Rva003BA810Elem *destination,
	const Rva003BA810Elem *first, const Rva003BA810Elem *last)
{
	int count = last - first;
	if (count > 0)
	{
		do
		{
			*destination = *first;
			++first;
			++destination;
		}
		while (--count);
	}
	return destination;
}

class Rva003BA810
{
public:
	Rva003BA810();

private:
	Rva003BA810Elem *m_start;
	Rva003BA810Elem *m_finish;
	Rva003BA810Elem *m_end;
};

// ??0Rva003BA810@@QAE@XZ
Rva003BA810::Rva003BA810()
	: m_start(0), m_finish(0), m_end(0)
{
	_ReadWriteBarrier();
	m_finish = rva003ba810Copy(m_start, m_finish, m_finish);
}
