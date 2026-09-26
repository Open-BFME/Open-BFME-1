// cl: /DNDEBUG /MD /EHsc

class AptValue
{
public:
    virtual void Release();

    bool GetMaxRefCountHit() const
    {
        return (m_flags >> 30 & 1) != 0;
    }

private:
    unsigned m_flags;
};

class AptInteger : public AptValue
{
public:
    static AptInteger *Create(int value);
};

class Rva008CAF00Array
{
public:
    int m_count;
    char m_gap04[4];
    AptValue **m_values;
};

void rva008CAF00IntegerAppend(Rva008CAF00Array *array)
{
    AptValue *value = AptInteger::Create(0);
    array->m_values[array->m_count] = value;
    ++array->m_count;

    if (!value->GetMaxRefCountHit())
        value->Release();
}
