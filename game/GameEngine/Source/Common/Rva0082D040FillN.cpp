// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

void rva0082ADB0Fill(char *, char *, const char &);

char *rva0082D040FillN(char *first, int n, const char &value)
{
  char *unused;
  rva0082ADB0Fill(first, first + n, value);
  return first + n;
}
