extern "C" unsigned char bfmeObjDAB[];
extern "C" void bfmeDtorDAB(void *what);

void __stdcall bfmeRegisterDAB(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAB()
{
	bfmeRegisterDAB(bfmeObjDAB, 0x7c, 6, bfmeDtorDAB);
}
