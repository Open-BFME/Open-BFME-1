// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

class Rva007AE5E0Referenced
{
public:
	virtual void release();
	UnsignedInt m_refCount;
};

class Rva007AE5E0Owner
{
public:
	void setReferenced( Rva007AE5E0Referenced *value );

private:
	unsigned char m_pad0[0x70];
	Rva007AE5E0Referenced *m_referenced;
};

void Rva007AE5E0Owner::setReferenced( Rva007AE5E0Referenced *value )
{
	if ( value != 0 ) {
		++value->m_refCount;
	}

	Rva007AE5E0Referenced *current = m_referenced;
	if ( current != 0 && --current->m_refCount == 0 ) {
		current->release();
	}

	m_referenced = value;
}
