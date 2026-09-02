// Open-BFME5: clean C++ conversion of the eleven-word aggregate comparison.

struct Rva002E4FD0Tail
{
	bool equals(const Rva002E4FD0Tail *other) const;
};

class Rva002E4FD0Value
{
public:
	int equals(const Rva002E4FD0Value *other) const;

private:
	int m_kind;
	int m_values[10];
	Rva002E4FD0Tail m_tail;
};

int Rva002E4FD0Value::equals(const Rva002E4FD0Value *other) const
{
	if (m_kind == other->m_kind) {
		for (unsigned int index = 0; index < 10; ++index) {
			if (m_values[index] != other->m_values[index]) {
				return false;
			}
		}

		if (m_tail.equals(&other->m_tail)) {
			return true;
		}
	}

	return false;
}
