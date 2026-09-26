struct SecondWordClearThunk
{
    unsigned long first;
    unsigned long second;

    SecondWordClearThunk *clearSecond();
};

SecondWordClearThunk *SecondWordClearThunk::clearSecond()
{
    second = 0;
    return this;
}
