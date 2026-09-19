// cl: /O2

// The carved body only proves a receiver-pointer load.  No caller or table
// provides a semantic name for the returned pointer.
class Rva006521D0PointerGetter
{
public:
	void *get() const;

private:
	void *m_value;
};

void *Rva006521D0PointerGetter::get() const
{
	return m_value;
}
