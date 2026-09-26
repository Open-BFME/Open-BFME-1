struct Rva000B2300FieldPredicate
{
	int value();
};

int Rva000B2300FieldPredicate::value()
{
	if ( *(int *)((char *)this + 0x30) == 5 )
		return *(int *)((char *)this + 0x2C);
	return 0;
}
