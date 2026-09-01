// ?d_00479210@@YAXXZ
// partial score=0.91 date=2026-08-31
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00479210Object
{
public:
	virtual void slot0(void) = 0;
	virtual void slot4(void) = 0;
	virtual void dispatch(void) = 0;

	void forward(void);

private:
	unsigned char m_pad4[0x1D8];
	Rva00479210Object *m_forwardTarget;
};

void Rva00479210Object::forward(void)
{
	if (m_forwardTarget)
		m_forwardTarget->dispatch();
	else
		dispatch();
}
