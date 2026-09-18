struct Rva0075D100PointerGetter
{
	void *get() const;
};

void *Rva0075D100PointerGetter::get() const
{
	return *reinterpret_cast<void *const *>(
		reinterpret_cast<const char *>(this) + 0x4);
}
