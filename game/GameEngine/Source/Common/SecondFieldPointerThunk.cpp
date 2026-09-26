// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail second-field pointer helper.

struct TwoFieldRecord
{
	unsigned int first;
	unsigned int second;
};

class SecondFieldPointer
{
public:
	unsigned int *get() const;

private:
	TwoFieldRecord *m_record;
};

// ?d_000ca040@@YAXXZ
unsigned int *SecondFieldPointer::get() const
{
	return &m_record->second;
}
