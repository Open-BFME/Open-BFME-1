// cl: /DNDEBUG /MD
// Separate address-derived views: the native owners and their relationship
// have not been established by callers or type-layout witnesses.
class Rva007F90B0
{
public:
    Rva007F90B0 *method(const Rva007F90B0 *other);
private:
    unsigned int m00;
    unsigned int m04;
};
Rva007F90B0 *Rva007F90B0::method(const Rva007F90B0 *other)
{
    m04 = other->m04;
    return this;
}
class Rva007F90C0
{
public:
    unsigned int method() const;
private:
    unsigned int m00;
};
unsigned int Rva007F90C0::method() const
{
    return m00;
}
