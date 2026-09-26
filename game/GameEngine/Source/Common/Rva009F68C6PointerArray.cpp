// cl: /O1
// Clean reconstruction of the three-field pointer-array RemoveAll operation.

// BFME releases this array through the CRT free import at 0x009F6C3A, not
// through ::operator delete.
extern "C" void __cdecl free(void *memory);

class Rva009F68C6PointerArray
{
public:
	void RemoveAll();

private:
	void *values;
	int count;
	int capacity;
};

void Rva009F68C6PointerArray::RemoveAll()
{
	if (values != 0) {
		free(values);
		values = 0;
	}
	count = 0;
	capacity = 0;
}
