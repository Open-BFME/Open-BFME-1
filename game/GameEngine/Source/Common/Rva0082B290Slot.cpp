// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0082B290Slot
{
public:
	Rva0082B290Slot *set(int value);

private:
	int m_value;
};

Rva0082B290Slot *Rva0082B290Slot::set(int value)
{
	m_value = value;
	return this;
}

class Rva0082B2B0Slot
{
public:
	Rva0082B2B0Slot *set(int value);

private:
	int m_value;
};

Rva0082B2B0Slot *Rva0082B2B0Slot::set(int value)
{
	m_value = value;
	return this;
}

class Rva0082B2D0Slot
{
public:
	Rva0082B2D0Slot *set(int value);

private:
	int m_value;
};

Rva0082B2D0Slot *Rva0082B2D0Slot::set(int value)
{
	m_value = value;
	return this;
}

class Rva0082BD80Slot
{
public:
	Rva0082BD80Slot *assignFrom(const int *src);

private:
	int m_value;
};

Rva0082BD80Slot *Rva0082BD80Slot::assignFrom(const int *src)
{
	m_value = *src;
	return this;
}
