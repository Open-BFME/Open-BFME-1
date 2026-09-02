// cl: /O1 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of the indexed pointer-slot assignment.

class Rva009F6948Array
{
public:
    void setAt(int index, void *const &value);

private:
    void **m_values;
};

void Rva009F6948Array::setAt(int index, void *const &value)
{
    void **slot = m_values + index;
    if (slot != 0) {
        index = reinterpret_cast<int>(value);
        *slot = reinterpret_cast<void *>(index);
    }
}
