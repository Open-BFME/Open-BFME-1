// cl: /O2 /Ob0

#define P(n) virtual void pad##n()
class Rva0021A310Obj
{
public:
	P(0); P(1); P(2); P(3); P(4); P(5); P(6); P(7);
	P(8); P(9); P(10); P(11); P(12); P(13); P(14); P(15);
	P(16); P(17); P(18); P(19); P(20); P(21); P(22); P(23);
	P(24); P(25); P(26); P(27); P(28); P(29); P(30);
	virtual void slot31(void *);
};
#undef P

void rva0021a310(void *a, Rva0021A310Obj *b)
{
	b->slot31(a);
}
