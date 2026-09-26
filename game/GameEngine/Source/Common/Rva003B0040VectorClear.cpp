// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

struct Elem003AF980
{
	virtual ~Elem003AF980();
	char m_body[0x10];
	Elem003AF980();
	Elem003AF980(const Elem003AF980 &);
	Elem003AF980 &operator=(const Elem003AF980 &);
};

class Rva003B0040Vector
{
public:
	void clear();

private:
	Elem003AF980 *m_begin;
	Elem003AF980 *m_end;
};

void Rva003B0040Vector::clear()
{
	_STL::vector<Elem003AF980> *vector =
		reinterpret_cast<_STL::vector<Elem003AF980> *>(this);
	vector->erase(m_begin, m_end);
}
