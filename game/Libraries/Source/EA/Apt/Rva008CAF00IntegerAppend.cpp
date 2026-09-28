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

// Gap boundary evidence: each entry is preceded by int3 and ends in RET
// before the next aligned entry; retail RVA 008CAF30/60/90 are 47 bytes,
// 008CAFC0 is 37 bytes. Slot zero is preserved as in the existing wrapper.
class AptBoolean : public AptValue
{
public:
    static AptBoolean *Create(bool value);
};
extern AptValue *g_bfmeFallbackDB;

void rva008CAF30Append(Rva008CAF00Array *array)
{
    AptValue *value = AptInteger::Create(1);
    array->m_values[array->m_count] = value;
    ++array->m_count;
    if (!value->GetMaxRefCountHit())
        value->Release();
}

void rva008CAF60Append(Rva008CAF00Array *array)
{
    AptValue *value = AptBoolean::Create(true);
    array->m_values[array->m_count] = value;
    ++array->m_count;
    if (!value->GetMaxRefCountHit())
        value->Release();
}

void rva008CAF90Append(Rva008CAF00Array *array)
{
    AptValue *value = AptBoolean::Create(false);
    array->m_values[array->m_count] = value;
    ++array->m_count;
    if (!value->GetMaxRefCountHit())
        value->Release();
}

void rva008CAFC0Append(Rva008CAF00Array *array)
{
    AptValue *value = g_bfmeFallbackDB;
    array->m_values[array->m_count] = value;
    ++array->m_count;
    if (!value->GetMaxRefCountHit())
        value->Release();
}
