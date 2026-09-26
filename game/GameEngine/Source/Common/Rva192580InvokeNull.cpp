class Rva192580Target
{
public:
    virtual void invoke(void *value) = 0;
};

void rva_192580_invoke_null(Rva192580Target *target)
{
    target->invoke(0);
}
