class Rva00696C10Offset8Getter
{
public:
	void *get() const;

private:
	void *m_value;
};

void *Rva00696C10Offset8Getter::get() const
{
	return (char *)m_value + 8;
}
