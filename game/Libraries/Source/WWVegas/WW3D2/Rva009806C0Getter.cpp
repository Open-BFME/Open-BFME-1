// cl: /O2 /MD

// Retail places this four-byte getter straight after
// AggregateDefClass::Save_Class_Info.  Nothing calls it and no table points at
// it, so its owner is unknown; the class is named for the address.

class Rva009806C0Owner
{
    char m_unknown[0x10];
    int m_field10;

public:
    int getField10() const;
};

int Rva009806C0Owner::getField10() const
{
    return m_field10;
}
