// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef bool Bool;

class Money
{
public:
	void deposit(UnsignedInt amount, Bool playSound);
};

class Rva00027D6DMoney
{
public:
	void unidentified_00027d6d(UnsignedInt amount, Bool playSound);
};

void Rva00027D6DMoney::unidentified_00027d6d(UnsignedInt amount, Bool playSound)
{
	((Money *)this)->deposit(amount, playSound);
}
