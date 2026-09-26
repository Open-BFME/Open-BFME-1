// cl: /O2 /DNDEBUG /MD
// The carved boundary proves a nine-byte thiscall that clears and returns one pointer.
// No evidence proves a semantic owner, so the class and method keep the address token.

class Rva005DC8F0Owner
{
public:
	__declspec(noinline) void *clear()
	{
		void *value = m_value;
		m_value = 0;
		return value;
	}

private:
	void *m_value;
};

__declspec(noinline) void *Rva005DC8F0Emit(Rva005DC8F0Owner *owner)
{
	return owner->clear();
}
