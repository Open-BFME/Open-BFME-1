// cl: /O2 /Ob0 /DNDEBUG /MD /EHs-c-

class Rva006516D0DwordGetter
{
public:
	int get() const;

private:
	char m_padding[0x464];
	int m_value;
};

int Rva006516D0DwordGetter::get() const
{
	return m_value;
}

class Rva006516E0DwordGetter
{
public:
	int get() const;

private:
	char m_padding[0x68];
	int m_value;
};

int Rva006516E0DwordGetter::get() const
{
	return m_value;
}

class Rva00651720Counter
{
public:
	void decrement();

private:
	char m_padding[0x54];
	int m_value;
};

void Rva00651720Counter::decrement()
{
	--m_value;
}

class Rva00651740DwordGetter
{
public:
	int get() const;

private:
	char m_padding[0x54];
	int m_value;
};

int Rva00651740DwordGetter::get() const
{
	return m_value;
}

class Rva006518E0Identity
{
public:
	void *identity();
};

void *Rva006518E0Identity::identity()
{
	return this;
}

class Rva00651930Identity
{
public:
	void *identity();
};

void *Rva00651930Identity::identity()
{
	return this;
}

class Rva00651980Identity
{
public:
	void *identity();
};

void *Rva00651980Identity::identity()
{
	return this;
}

class Rva006519A0Identity
{
public:
	void *identity();
};

void *Rva006519A0Identity::identity()
{
	return this;
}

class Rva006519D0GetPlusTen
{
public:
	int get() const;

private:
	int m_value;
};

int Rva006519D0GetPlusTen::get() const
{
	return m_value + 0x10;
}

class Rva00651A10DwordGetter
{
public:
	int get() const;

private:
	int m_value;
};

int Rva00651A10DwordGetter::get() const
{
	return m_value;
}

class Rva00651A20DwordGetter
{
public:
	int get() const;

private:
	int m_value;
};

int Rva00651A20DwordGetter::get() const
{
	return m_value;
}

class Rva00651DB0DwordGetter
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva00651DB0DwordGetter::get() const
{
	return m_value;
}

class Rva00651E50DwordGetter
{
public:
	int get() const;

private:
	int m_value;
};

int Rva00651E50DwordGetter::get() const
{
	return m_value;
}

unsigned char Rva00651F80False()
{
	return 0;
}

unsigned char Rva00652070False()
{
	return 0;
}

unsigned char Rva00652080False()
{
	return 0;
}

unsigned char Rva00652090False()
{
	return 0;
}

unsigned char Rva00652110False()
{
	return 0;
}

class Rva006521B0DwordGetter
{
public:
	int get() const;

private:
	int m_value;
};

int Rva006521B0DwordGetter::get() const
{
	return m_value;
}
