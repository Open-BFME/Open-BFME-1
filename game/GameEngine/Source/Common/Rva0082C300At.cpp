// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// retail callee at 0x006434C0, reached through the ILT thunk at 0x000132CD;
// declaration only, the body is game/gen_small/fun_004.cpp
struct Gen_006434c0 { void m(); };

class Rva0082C300Buf
{
public:
  char *at(int n);

private:
  char *m_start;
  char *m_finish;
};

char *Rva0082C300Buf::at(int n)
{
  if ((unsigned)n >= (unsigned)(m_finish - m_start))
    ((Gen_006434c0 *)this)->m();
  return m_start + n;
}

class Rva0082C330Buf
{
public:
  char *at(int n);

private:
  char *m_start;
  char *m_finish;
};

char *Rva0082C330Buf::at(int n)
{
  if ((unsigned)n >= (unsigned)(m_finish - m_start))
    ((Gen_006434c0 *)this)->m();
  return m_start + n;
}
