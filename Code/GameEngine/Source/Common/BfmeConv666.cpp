extern "C" unsigned char bfmeObjDAA[];
extern "C" void bfmeDtorDAA(void *what);

void __stdcall bfmeRegisterDAA(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAA()
{
	bfmeRegisterDAA(bfmeObjDAA, 4, 0x20, bfmeDtorDAA);
}
