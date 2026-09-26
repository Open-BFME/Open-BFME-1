// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Address-qualified carved no-ops in the audio region. Each is a one-byte
// RET reached only through an unresolved ILT thunk, so no semantic owner is
// asserted.
void Rva001DB170Noop()
{
}

void Rva001DB830Noop()
{
}
