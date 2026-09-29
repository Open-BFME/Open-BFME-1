extern const char *const ModelConditionNames[];
extern const char *const Rva00209130StatusNames[];

struct Rva0022A1F0ConstantGetter
{
	void *get();
};

void *Rva0022A1F0ConstantGetter::get()
{
	return (void *)ModelConditionNames;
}

struct Rva0022A200ConstantGetter
{
	void *get();
};

void *Rva0022A200ConstantGetter::get()
{
	return (void *)Rva00209130StatusNames;
}
