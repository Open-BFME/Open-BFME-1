// ?get@Rva000E0AC0@@QAEPAXXZ
// Retail body 0x000E0AC0. The carved boundary is three bytes and the body
// reads the object's first pointer field before returning.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva000E0AC0
{
public:
	void *get(void);

private:
	void *m_value;
};

void *Rva000E0AC0::get(void)
{
	return m_value;
}
