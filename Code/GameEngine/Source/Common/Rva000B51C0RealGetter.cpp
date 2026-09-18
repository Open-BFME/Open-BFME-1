struct Rva000B51C0RealGetter
{
	float get() const;
};

float Rva000B51C0RealGetter::get() const
{
	return *reinterpret_cast<const float *>(
		reinterpret_cast<const char *>(this) + 0x74);
}
