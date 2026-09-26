class Rva004362B0StrideAdd {
public:
    static void add(int *value, int index);
};

void Rva004362B0StrideAdd::add(int *value, int index)
{
    *value += index * 8;
}
