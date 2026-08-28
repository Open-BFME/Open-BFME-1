extern "C" unsigned char bfmeStrDULa[];
extern "C" unsigned char bfmeStrDULb[];
extern "C" unsigned char bfmeStrDULc[];
extern "C" unsigned char bfmeStrDULd[];
extern "C" unsigned char bfmeStrDULe[];

void __stdcall bfmeCallDUL(void *other, const void *what);

void *__stdcall bfmeGoDULa(void *other)
{
	volatile int tmp = 0;
	bfmeCallDUL(other, bfmeStrDULa);
	return other;
}

void *__stdcall bfmeGoDULb(void *other)
{
	volatile int tmp = 0;
	bfmeCallDUL(other, bfmeStrDULb);
	return other;
}

void *__stdcall bfmeGoDULc(void *other)
{
	volatile int tmp = 0;
	bfmeCallDUL(other, bfmeStrDULc);
	return other;
}

void *__stdcall bfmeGoDULd(void *other)
{
	volatile int tmp = 0;
	bfmeCallDUL(other, bfmeStrDULd);
	return other;
}

void *__stdcall bfmeGoDULe(void *other)
{
	volatile int tmp = 0;
	bfmeCallDUL(other, bfmeStrDULe);
	return other;
}
