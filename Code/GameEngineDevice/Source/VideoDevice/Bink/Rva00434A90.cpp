// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

template<class T> struct StringData
{
	int ref_count;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template<class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringData<T> *data;
	StringBase() : data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &text);
	~StringBase() { releaseBuffer(); }
	void concat(const T *text, int length);
	void set(const StringBase &text);
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &text) : StringBase<char>(text) {}
	~AsciiString() {}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const StringBase<unsigned short> &text)
	{
		((StringBase<unsigned short> *)this)->set(text);
	}
	UnicodeString(const UnicodeString &text)
	{
		((StringBase<unsigned short> *)this)->set(
			(const StringBase<unsigned short> &)text);
	}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &text)
	{
		((StringBase<unsigned short> *)this)->set(
			(const StringBase<unsigned short> &)text);
		return *this;
	}
};

typedef bool Bool;

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class Rva00434A90
{
public:
	static Bool lookup(const char *label, UnicodeString *subtitle);
};

Bool Rva00434A90::lookup(const char *label, UnicodeString *subtitle)
{
	AsciiString subtitleLabel("SUBTITLE:");
	Bool exists;
	subtitleLabel.concat(label, label ? (int)strlen(label) : 0);
	*subtitle = TheGameText->fetch(subtitleLabel, &exists);
	return exists;
}
