// cl: /DNDEBUG /MD /Oy- /EHsc

// Open-BFME5: Debug::operator<<(bool). const char* stream at vtable +0x38.

class Debug
{
public:
	virtual ~Debug();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual Debug &operator<<(char const *);
	Debug &operator<<(bool);
};

// ??6Debug@@QAEAAV0@_N@Z
Debug &Debug::operator<<(bool value)
{
	const char *text;
	if (value)
		text = "true";
	else
		text = "false";
	return (*this) << text;
}