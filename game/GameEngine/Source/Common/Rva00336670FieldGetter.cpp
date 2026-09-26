// cl: /DNDEBUG /MD /EHsc

struct Rva00336670FieldGetter
{
	int getField1C() const;
};

int Rva00336670FieldGetter::getField1C() const
{
	return *(const int *)((const char *)this + 0x1c);
}
