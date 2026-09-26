// Open-BFME5: clean C++ conversion of the embedded two-word reset.

class Rva00523360Owner
{
public:
    void resetPair();

private:
    char m_pad00[0x12C];
    int m_values[2];
};

void Rva00523360Owner::resetPair()
{
    for (unsigned int i = 0; i != 2; ++i) {
        m_values[i] = 0;
    }
}
