struct InlineRangeState
{
    bool flag;
    char padding[3];
    unsigned long size;
    InlineRangeState *begin;
    InlineRangeState *end;
};

struct InlineRangeResetThunk
{
    InlineRangeState *state;

    void reset();
    void resetAlternate();
    void resetThird();
    void resetFourth();
};

// ?d_0036d330@@YAXXZ
void InlineRangeResetThunk::reset()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}

// ?d_0036d370@@YAXXZ
void InlineRangeResetThunk::resetAlternate()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}

// ?d_0036d3a0@@YAXXZ
void InlineRangeResetThunk::resetThird()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}

// ?d_0036d3d0@@YAXXZ
void InlineRangeResetThunk::resetFourth()
{
    state->flag = false;
    state->size = 0;
    state->begin = state;
    state->end = state;
}
