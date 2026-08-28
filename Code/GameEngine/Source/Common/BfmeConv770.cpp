char __stdcall bfmeCallDSD(void *what);

bool __stdcall bfmeGoDSD(void *what)
{
	return bfmeCallDSD(what) == 0;
}
