struct Rva0045BD60RealGetter
{
	float get() const;
};

float Rva0045BD60RealGetter::get() const
{
	return *reinterpret_cast<const float *>(
		reinterpret_cast<const char *>(this) + 0x3c);
}
