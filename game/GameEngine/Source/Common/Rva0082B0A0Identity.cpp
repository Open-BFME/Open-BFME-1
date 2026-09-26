// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0082B0A0Identity
{
public:
    Rva0082B0A0Identity *self();
    void touch();
};

Rva0082B0A0Identity *Rva0082B0A0Identity::self()
{
    return this;
}

void Rva0082B0A0Identity::touch()
{
}

class Rva0082B0E0Identity
{
public:
    Rva0082B0E0Identity *self();
    void touch();
};

Rva0082B0E0Identity *Rva0082B0E0Identity::self()
{
    return this;
}

void Rva0082B0E0Identity::touch()
{
}

class Rva0082B140Helpers
{
public:
    int firstValue(int value);
    int secondValue(int value);
    int maximumIndex();
    int alternateMaximumIndex();
    void ignoreValue(int value);
    int upperWord();
    bool wordsEqual();

private:
    int m_lowerWord;
    int m_upperWord;
};

int Rva0082B140Helpers::firstValue(int value)
{
    return value;
}

int Rva0082B140Helpers::secondValue(int value)
{
    return value;
}

int Rva0082B140Helpers::maximumIndex()
{
    return 0x3fffffff;
}

int Rva0082B140Helpers::alternateMaximumIndex()
{
    return 0x3fffffff;
}

void Rva0082B140Helpers::ignoreValue(int)
{
}

int Rva0082B140Helpers::upperWord()
{
    return m_upperWord;
}

bool Rva0082B140Helpers::wordsEqual()
{
    return m_lowerWord == m_upperWord;
}

class Rva0082B1D0PointerRange
{
public:
    int *firstPointer();
    int *alternateFirstPointer();
    int *lastElement();
    int *alternateLastElement();
    int *elementAt(int index);
    int *alternateElementAt(int index);

private:
    int *m_first;
    int *m_end;
};

int *Rva0082B1D0PointerRange::firstPointer()
{
    int *result = m_first;
    return result;
}

int *Rva0082B1D0PointerRange::alternateFirstPointer()
{
    int *result = m_first;
    return result;
}

int *Rva0082B1D0PointerRange::lastElement()
{
    int *result = m_end;
    return result - 1;
}

int *Rva0082B1D0PointerRange::alternateLastElement()
{
    int *result = m_end;
    return result - 1;
}

int *Rva0082B1D0PointerRange::elementAt(int index)
{
    int *result = m_first;
    return result + index;
}

int *Rva0082B1D0PointerRange::alternateElementAt(int index)
{
    int *result = m_first;
    return result + index;
}

class Rva0082B060Identity
{
public:
    Rva0082B060Identity *self();
    void touch();
};

Rva0082B060Identity *Rva0082B060Identity::self()
{
    return this;
}

void Rva0082B060Identity::touch()
{
}

class Rva0082B000Helpers
{
public:
    int firstValue(int value);
};

int Rva0082B000Helpers::firstValue(int value)
{
    return value;
}

class Rva0082BFC0Identity
{
public:
    Rva0082BFC0Identity *self();
};

Rva0082BFC0Identity *Rva0082BFC0Identity::self()
{
    return this;
}

class Rva0082B010Fail
{
public:
	int fail();
};

int Rva0082B010Fail::fail()
{
	return -1;
}
