class Rva00436750StrideAdd {
public:
    static void add(int *value, int index);
};

void Rva00436750StrideAdd::add(int *value, int index)
{
    *value += index * 8;
}
