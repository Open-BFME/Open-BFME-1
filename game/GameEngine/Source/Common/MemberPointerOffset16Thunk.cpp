struct MemberPointerOffset16Thunk
{
    char *value;

    void *get() const;
    void *getAlternate() const;
    void *getThird() const;
    void *getFourth() const;
};

// ?d_0036d100@@YAXXZ
void *MemberPointerOffset16Thunk::get() const
{
    return value + 16;
}

// ?d_0036d110@@YAXXZ
void *MemberPointerOffset16Thunk::getAlternate() const
{
    return value + 16;
}

// ?d_0036d120@@YAXXZ
void *MemberPointerOffset16Thunk::getThird() const
{
    return value + 16;
}

// ?d_0036d130@@YAXXZ
void *MemberPointerOffset16Thunk::getFourth() const
{
    return value + 16;
}
