// cl: /DNDEBUG /MD /EHsc

typedef void (*Rva00945B80CellFunction)(void *);

extern void __stdcall rva00906340VecCtor(
	void *ptr,
	unsigned element_size,
	int count,
	Rva00945B80CellFunction ctor,
	Rva00945B80CellFunction dtor);
extern void rva00906340CellCtor(void *self);
extern void rva00906340CellDtor(void *self);

class Rva00945B80
{
public:
	Rva00945B80();

private:
	unsigned char cells[0x200];
	int zero_array[0x40];
	int fill_array[0x40];
	int tail;
};

Rva00945B80::Rva00945B80()
{
	rva00906340VecCtor(
		this,
		4,
		0x80,
		rva00906340CellCtor,
		rva00906340CellDtor);

	for (int index = 0; index < 0x40; ++index)
		fill_array[index] = 0x0010441B;

    tail = 0;

    for (int index = 0; index < 0x40; ++index)
        zero_array[index] = 0;
}
