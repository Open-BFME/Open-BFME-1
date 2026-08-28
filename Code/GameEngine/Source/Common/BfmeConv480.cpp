void __stdcall bfmeOneBKE(void *what);
void bfmeTwoBKE(void *what);

void __stdcall bfmeGoBKE(void *what)
{
	bfmeOneBKE(what);
	bfmeTwoBKE(what);
}
