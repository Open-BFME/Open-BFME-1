// cl: /DNDEBUG /MD /EHs-c-
// Opaque aggregate-return virtual dispatch, two adjacent vtable slots.
struct Rva0083FDF0Result
{
    unsigned int m_value;
    Rva0083FDF0Result();
    Rva0083FDF0Result(const Rva0083FDF0Result &other);
    ~Rva0083FDF0Result();
};

struct Rva0083FDF0Owner
{
    virtual void slotZero();
    virtual void slotOne();
    virtual Rva0083FDF0Result slotTwo(int first, int second, int third);
    virtual Rva0083FDF0Result slotThree(int first, int second, int third);

    Rva0083FDF0Result forwardSlotTwo(int first, int second, int third);
    Rva0083FDF0Result forwardSlotThree(int first, int second, int third);
};

Rva0083FDF0Result Rva0083FDF0Owner::forwardSlotTwo(int first, int second, int third)
{
    return slotTwo(first, second, third);
}

Rva0083FDF0Result Rva0083FDF0Owner::forwardSlotThree(int first, int second, int third)
{
    return slotThree(first, second, third);
}
