// The carved body at 0x00626930 contains only ret.  Its caller proves the
// boundary but not a semantic owner, so the function keeps its address name.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

void Rva00626930Noop()
{
}
