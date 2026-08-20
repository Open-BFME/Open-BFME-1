// cl: /DNDEBUG /MD /EHsc

// Retail 0x00703EF0. If m_ptr, tail-call its first virtual; else return 0.

class Gen_00703ef0_Iface
{
public:
	virtual int first(void);
};

class Gen_00703ef0
{
public:
	int call(void);

private:
	Gen_00703ef0_Iface *m_ptr;
};

// ?call@Gen_00703ef0@@QAEHXZ
int Gen_00703ef0::call(void)
{
	if (m_ptr)
		return m_ptr->first();
	return 0;
}
