// Open-BFME5: clean C++ conversion of the eleven-word aggregate comparison.

class T4Host002E4D60
{
public:
	bool equals(const T4Host002E4D60 &other) const;

private:
	int m_val[10];
};

class Rva002E4FD0Value
{
public:
	int equals(const Rva002E4FD0Value *other) const;

private:
	int m_kind;
	int m_values[10];
	T4Host002E4D60 m_tail;
};

int Rva002E4FD0Value::equals(const Rva002E4FD0Value *other) const
{
	if (m_kind == other->m_kind) {
		for (unsigned int index = 0; index < 10; ++index) {
			if (m_values[index] != other->m_values[index]) {
				return false;
			}
		}

		if (m_tail.equals(other->m_tail)) {
			return true;
		}
	}

	return false;
}

class T4Host002E4D20
{
public:
	bool equals(const T4Host002E4D20 &other) const;

private:
	int m_val[3];
};

class Rva002E5030Value
{
public:
	int equals(const Rva002E5030Value *other) const;

private:
	int m_kind;
	int m_values[3];
	T4Host002E4D20 m_tail;
};

int Rva002E5030Value::equals(const Rva002E5030Value *other) const
{
	if (m_kind == other->m_kind) {
		for (unsigned int index = 0; index < 3; ++index) {
			if (m_values[index] != other->m_values[index]) {
				return false;
			}
		}

		if (m_tail.equals(other->m_tail)) {
			return true;
		}
	}

	return false;
}
