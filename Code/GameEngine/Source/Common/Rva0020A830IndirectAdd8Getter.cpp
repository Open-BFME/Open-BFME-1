// cl: /O2 /MD /EHsc-

class Rva0020A830IndirectAdd8Getter
{
public:
	void *get() const;

private:
	void *m_base;
};

void *Rva0020A830IndirectAdd8Getter::get() const
{
	return (char *)m_base + 8;
}
