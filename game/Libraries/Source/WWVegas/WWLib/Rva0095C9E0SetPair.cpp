struct Rva0095C9E0Pair
{
	unsigned first;
	unsigned second;
};

class Rva0095C9E0Owner
{
public:
	void setPair(const Rva0095C9E0Pair *value);

private:
	char m_reserved[0x30];
	Rva0095C9E0Pair m_pair;
};

void Rva0095C9E0Owner::setPair(const Rva0095C9E0Pair *value)
{
	m_pair.first = value->first;
	m_pair.second = value->second;
}
