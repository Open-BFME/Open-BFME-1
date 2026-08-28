extern "C" unsigned char bfmeObjDAE[];
extern "C" void bfmeDtorDAE(void *what);

void __stdcall bfmeRegisterDAE(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAE()
{
	bfmeRegisterDAE(bfmeObjDAE, 4, 0xb2, bfmeDtorDAE);
}
