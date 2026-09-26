int __stdcall bfmeCallDSC(void *what);

bool __stdcall bfmeGoDSC(void *what)
{
	return bfmeCallDSC(what) == 0;
}
