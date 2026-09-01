// cl: /O1
// Clean reconstruction of the three-field pointer-array RemoveAll operation.

void __cdecl operator delete(void *memory);

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
		::operator delete(values);
		values = 0;
	}
	count = 0;
	capacity = 0;
}
