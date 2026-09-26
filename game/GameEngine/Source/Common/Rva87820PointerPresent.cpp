class Rva87820PointerPresent
{
public:
    unsigned int has_value();

private:
    void *value;
};

unsigned int Rva87820PointerPresent::has_value()
{
    return value != 0;
}
