void bfmeFreeBIB(void *what, unsigned int bytes);

void __stdcall bfmeGoBIB(void *what)
{
	if (what != 0)
		bfmeFreeBIB(what, 0x68);
}
