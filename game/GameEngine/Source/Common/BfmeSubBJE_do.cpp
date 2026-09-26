// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class TextureBaseClass
{
public:
	void Add_Ref(void)
	{
		++*(unsigned short *)((char *)this + 4);
	}

	void Release_Ref(void);
};

class BfmeRef
{
public:
	BfmeRef &operator=(const BfmeRef &that)
	{
		if (that.pointer)
			that.pointer->Add_Ref();
		if (pointer)
			pointer->Release_Ref();
		pointer = that.pointer;
		return *this;
	}

	TextureBaseClass *pointer;
};

class BfmeSubBJE
{
public:
	virtual bool Equal(const BfmeSubBJE &that) const;
	virtual bool Unused(void);
	virtual bool Resize(int newsize, const void *array = 0);

	bool bfmeDoBJE(void *what);
	int activeCount() const { return active_count; }

private:
	BfmeRef *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
	int active_count;
	int growth_step;
};

bool BfmeSubBJE::bfmeDoBJE(void *what)
{
	if (active_count >= vector_max) {
		if ((is_allocated || !vector_max) && growth_step > 0) {
			if (!Resize(vector_max + growth_step, 0))
				return false;
		} else {
			return false;
		}
	}

	int index = active_count;
	active_count = index + 1;
	vector[index] = *(BfmeRef *)what;
	return true;
}

struct Rva0096E9F0Owner
{
	char m_reserved[0xf4];
	BfmeSubBJE m_sub;

	int appendAndReturnIndex(void *value);
};

int Rva0096E9F0Owner::appendAndReturnIndex(void *value)
{
	int index = m_sub.activeCount();
	m_sub.bfmeDoBJE(value);
	return index;
}
