// cl: /DNDEBUG /MD /EHsc
// stlport
#include <vector>

// Address-derived view: retail passes the fill byte by value, unlike the
// previously claimed const-reference overload. See identity_evidence/
// 0074e620-value-argument.md for caller and complete-boundary evidence.
class Rva0074E620 : public std::vector<unsigned char> {
public:
    void method(unsigned int count, unsigned char value);
};
void Rva0074E620::method(unsigned int count, unsigned char value)
{
    if (count < size())
        erase(begin() + count, end());
    else
        insert(end(), count - size(), value);
}
