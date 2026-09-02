// cl: /DNDEBUG /MD /EHsc /O2

class Rva00784560StringBase
{
protected:
	Rva00784560StringBase(const Rva00784560StringBase &other);
	~Rva00784560StringBase();
	void *m_data;
};

class Rva00784560String : private Rva00784560StringBase
{
public:
	Rva00784560String(const Rva00784560String &other) : Rva00784560StringBase(other) {}
	~Rva00784560String() {}
};

class Rva00784560Backend
{
public:
	virtual void bfmeSlot00(void);
	virtual void bfmeUseName(Rva00784560String name);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot0c(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot1c(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot2c(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot38(void);
	virtual void bfmeGetSize(int *width, int *height);
	virtual void bfmeSlot40(void);
	virtual void bfmeSlot44(void);
	virtual void bfmeSetOrigin(int x, int y);
};

class Rva00784560Viewport
{
public:
	void bfmeSetup(const Rva00784560String *name);

	char m_pad00[8];
	Rva00784560Backend *m_backend;
	char m_pad0c[0x10];
	float m_width;
	float m_height;
};

// @?bfmeSetup@Rva00784560Viewport@@QAEXPBVRva00784560String@@@Z 0x00784560
void Rva00784560Viewport::bfmeSetup(const Rva00784560String *name)
{
	m_backend->bfmeSetOrigin(0, 0);
	m_backend->bfmeUseName(*name);

	int width;
	int height;
	m_backend->bfmeGetSize(&width, &height);
	m_width = (float)width;
	m_height = (float)height;
}
