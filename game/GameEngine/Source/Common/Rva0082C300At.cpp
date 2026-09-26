// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0082C300Buf
{
public:
  char *at(int n);

private:
  void grow();

  char *m_start;
  char *m_finish;
};

char *Rva0082C300Buf::at(int n)
{
  if ((unsigned)n >= (unsigned)(m_finish - m_start))
    grow();
  return m_start + n;
}

class Rva0082C330Buf
{
public:
  char *at(int n);

private:
  void grow();

  char *m_start;
  char *m_finish;
};

char *Rva0082C330Buf::at(int n)
{
  if ((unsigned)n >= (unsigned)(m_finish - m_start))
    grow();
  return m_start + n;
}
