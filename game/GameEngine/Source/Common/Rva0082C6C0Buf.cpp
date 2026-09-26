// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0082C6C0Buf
{
public:
	void pop();

private:
	int *m_start;
	int *m_finish;
};

void Rva0082C6C0Buf::pop()
{
	--m_finish;
}
