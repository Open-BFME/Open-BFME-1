// cl: /Od /Ob1

struct Rva0082C6E0Value
{
	unsigned long m_value;
};

struct Rva0082C6E0FalseType
{
};

extern Rva0082C6E0Value *__cdecl rva0082C6E0CopyValues(
	Rva0082C6E0Value *first,
	Rva0082C6E0Value *last,
	Rva0082C6E0Value *result );

inline Rva0082C6E0Value *rva0082C6E0CopyPointers(
	Rva0082C6E0Value *first,
	Rva0082C6E0Value *last,
	Rva0082C6E0Value *result,
	const Rva0082C6E0FalseType & )
{
	return rva0082C6E0CopyValues( first, last, result );
}

inline void rva0082C6E0Destroy( Rva0082C6E0Value * )
{
}

class Rva0082C6E0Vector
{
public:
	Rva0082C6E0Value *erase( Rva0082C6E0Value *position );

private:
	Rva0082C6E0Value *end()
	{
		return m_finish;
	}

	Rva0082C6E0Value *m_start;
	Rva0082C6E0Value *m_finish;
	Rva0082C6E0Value *m_capacity;
};

Rva0082C6E0Value *Rva0082C6E0Vector::erase( Rva0082C6E0Value *position )
{
	if ( position + 1 != end() )
	{
		rva0082C6E0CopyPointers(
			position + 1, m_finish, position, Rva0082C6E0FalseType() );
	}

	--m_finish;
	rva0082C6E0Destroy( m_finish );
	return position;
}
