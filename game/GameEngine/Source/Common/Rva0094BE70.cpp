// cl: /DNDEBUG /MD
// Native source identity is unproven; these are separate address-derived views.
class Rva0094BE70
{
public:
    unsigned int method(const Rva0094BE70 *other) const;
private:
    unsigned int m00;
};
unsigned int Rva0094BE70::method(const Rva0094BE70 *other) const
{
    return m00 < other->m00;
}
class Rva0094BE80
{
public:
    Rva0094BE80 *method(const void *argument);
};
Rva0094BE80 *Rva0094BE80::method(const void *)
{
    return this;
}
