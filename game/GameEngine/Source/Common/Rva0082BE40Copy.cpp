// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva0082C6E0Value;

Rva0082C6E0Value *rva0082C6E0CopyValues(Rva0082C6E0Value *, Rva0082C6E0Value *, Rva0082C6E0Value *);

Rva0082C6E0Value *rva0082BE40Copy(Rva0082C6E0Value *a, Rva0082C6E0Value *b, Rva0082C6E0Value *c)
{
  return rva0082C6E0CopyValues(a, b, c);
}
