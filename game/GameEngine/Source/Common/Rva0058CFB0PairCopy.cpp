// Open-BFME5: clean C++ conversion of the indirect pair copy.

struct Rva0058CFB0Pair
{
    int first;
    int second;
};

class Rva0058CFB0Owner
{
public:
    Rva0058CFB0Pair copyPair(const void *) const;

private:
    char m_pad00[8];
    const int *m_first;
    const int *m_second;
};

Rva0058CFB0Pair Rva0058CFB0Owner::copyPair(const void *) const
{
    Rva0058CFB0Pair result;
    result.second = *m_second;
    result.first = *m_first;
    return result;
}
