class __declspec(dllimport) exception
{
public:
	exception(const exception &other);
};

extern "C" unsigned char bfmeVftUA[];

class BfmeExcUA : public exception
{
public:
	BfmeExcUA(const BfmeExcUA &other);
};

BfmeExcUA::BfmeExcUA(const BfmeExcUA &other) : exception(other)
{
	*(void **)this = bfmeVftUA;
}
