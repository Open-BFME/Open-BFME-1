extern "C" unsigned char bfmeObjDAD[];
extern "C" void bfmeDtorDAD(void *what);

void __stdcall bfmeRegisterDAD(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAD()
{
	bfmeRegisterDAD(bfmeObjDAD, 4, 0x41a, bfmeDtorDAD);
}
