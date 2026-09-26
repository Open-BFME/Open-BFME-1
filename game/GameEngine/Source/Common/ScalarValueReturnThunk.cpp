struct ScalarValueResult
{
    unsigned long value;
};

struct ScalarValueReturnThunk
{
    unsigned long value;

    ScalarValueResult get() const;
    ScalarValueResult getAlternate() const;
    ScalarValueResult getThird() const;
    ScalarValueResult getFourth() const;
    ScalarValueResult getFifth() const;
    ScalarValueResult getSixth() const;
    ScalarValueResult getSeventh() const;
    ScalarValueResult getEighth() const;
    ScalarValueResult getNinth() const;
};

// ?d_0036d140@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::get() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036d150@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getAlternate() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036d210@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getThird() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036d280@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getFourth() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036d2f0@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getFifth() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036dc00@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getSixth() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036dc10@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getSeventh() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036dc40@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getEighth() const
{
    ScalarValueResult result = { value };
    return result;
}

// ?d_0036dc90@@YAXXZ
ScalarValueResult ScalarValueReturnThunk::getNinth() const
{
    ScalarValueResult result = { value };
    return result;
}
