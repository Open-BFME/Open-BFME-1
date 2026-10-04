// cl: /DNDEBUG /MD /EHsc-

// Retail 0x0006AA90 inserts a 16-byte function-curve record into the sorted
// vector owned by Rva0006AB10Curve::set at 0x0006AB10.  The lower-bound call,
// vector-insert thunk, and the 97-byte retail body establish this ownership.

struct Rva0006AA90Element
{
	float m_key;
	int m_value[3];
};

struct Rva0006AA90InsertResult
{
	Rva0006AA90InsertResult() {}
	Rva0006AA90InsertResult(const Rva0006AA90InsertResult &other)
		: m_first(other.m_first), m_second(other.m_second) {}
	Rva0006AA90InsertResult(Rva0006AA90Element *const &first,
		const unsigned char &second)
	{
		m_second = second;
		m_first = first;
	}

	Rva0006AA90Element *m_first;
	bool m_second;
};

// Retail 0x00049896 is the lower-bound helper the vector-insert body calls.
// Its proven identity is bfmeSendEventA19 (a void-returning dispatch wrapper
// that retail passes the raw pointers to), so declare that real name here and
// reach its pointer-returning result through a call through it: the retail
// body keeps the returned iterator in eax.
void __cdecl bfmeSendEventA19(void *, void *, void *, unsigned int, int);

typedef void *(__cdecl *Rva0006AA90CurveFind)(void *, void *, void *,
	unsigned int, int);

// Retail 0x00040566 is the ILT thunk the body reaches the vector insert
// through; the thunk itself carries no signature, so call it through a
// same-shaped member pointer (as the other recovered bodies do).
extern void j_00040566();

class Rva0006AA90Vector
{
public:
	Rva0006AA90InsertResult insertUnique(const Rva0006AA90Element &value);

	Rva0006AA90Element *m_start;
	Rva0006AA90Element *m_finish;
	Rva0006AA90Element *m_end;
	unsigned char m_padding;
	unsigned char m_flag;
};

Rva0006AA90InsertResult Rva0006AA90Vector::insertUnique(
	const Rva0006AA90Element &value)
{
	bool duplicate = true;
	unsigned char *flag = this ? &m_flag : 0;
	unsigned int code = *flag;
	Rva0006AA90Element *start = m_start;
	Rva0006AA90Element *finish = m_finish;
	Rva0006AA90Element *position = (Rva0006AA90Element *)((
		Rva0006AA90CurveFind)(void *)bfmeSendEventA19)(
			start, finish, (void *)&value, code, 0);
	if (position == finish || value.m_key < position->m_key)
	{
		typedef void *(Rva0006AA90Vector::*Rva0006AA90Insert)(
			void *, const void *);
		union { void (*fn)(); Rva0006AA90Insert call; }
			insertThunk = { j_00040566 };
		position = (Rva0006AA90Element *)(this->*insertThunk.call)(
			position, &value);
		duplicate = false;
	}
	bool inserted = !duplicate;
	Rva0006AA90InsertResult result(position, inserted);
	return result;
}
