struct EmptyCopyAssignThunk
{
    EmptyCopyAssignThunk &assign(const EmptyCopyAssignThunk &other);
    EmptyCopyAssignThunk &assignAlternate(const EmptyCopyAssignThunk &other);
};

// ?d_0036c770@@YAXXZ
EmptyCopyAssignThunk &EmptyCopyAssignThunk::assign(const EmptyCopyAssignThunk &)
{
    return *this;
}

// ?d_0036c780@@YAXXZ
EmptyCopyAssignThunk &EmptyCopyAssignThunk::assignAlternate(const EmptyCopyAssignThunk &)
{
    return *this;
}

struct Rva0006C780CopyAssign
{
    Rva0006C780CopyAssign &returnThis();
};

Rva0006C780CopyAssign &Rva0006C780CopyAssign::returnThis()
{
    return *this;
}
