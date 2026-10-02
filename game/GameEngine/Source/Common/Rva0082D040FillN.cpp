// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail's 0x0082ADB0 is the STLport _STL::fill<char> out-of-line copy; the
// other seven objects that instantiate it carry it as a COMDAT, so naming it
// by its real spelling links against retail's ICF alias.
namespace _STL { void fill(char *, char *, const char &); }

char *rva0082D040FillN(char *first, int n, const char &value)
{
  char *unused;
  _STL::fill(first, first + n, value);
  return first + n;
}
