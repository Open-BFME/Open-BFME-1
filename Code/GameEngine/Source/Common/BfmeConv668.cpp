extern "C" unsigned char bfmeObjDAC[];
extern "C" void bfmeDtorDAC(void *what);

void __stdcall bfmeRegisterDAC(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAC()
{
	bfmeRegisterDAC(bfmeObjDAC, 4, 1, bfmeDtorDAC);
}
