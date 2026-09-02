// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva007E3160
{
public:
	virtual void v0();
	int ready();

private:
	void *m_04;
	int m_08;
};

// ?ready@Rva007E3160@@QAEHXZ
int Rva007E3160::ready()
{
	return m_04 && (m_08 == 6 || m_08 == 7);
}
