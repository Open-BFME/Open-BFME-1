// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail pointer emptiness predicate.

class PointerPresencePredicate
{
public:
	bool empty() const;

private:
	void *m_value;
};

bool PointerPresencePredicate::empty() const
{
	return m_value == 0;
}
