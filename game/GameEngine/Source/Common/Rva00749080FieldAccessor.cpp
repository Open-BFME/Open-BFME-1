// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct Rva00749080FieldAccessor
{
	void *reserved00;
	void *field;

	void *get();
};

void *Rva00749080FieldAccessor::get()
{
	return field;
}
