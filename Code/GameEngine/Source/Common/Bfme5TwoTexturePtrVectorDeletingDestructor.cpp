// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the vector-deleting wrapper for the two-texture holder at
// retail RVA 0x0092FF30.  Its scalar-destructor operand is ILT 0x0001AAD2,
// which routes to the matched Gen_0092F190 destructor at 0x0092F190.
// The two BfmeTexPtr members make the element width eight bytes.

void operator delete[](void *block);

class TextureClass
{
public:
	void Release_Ref(void);
};

class BfmeTexPtr
{
public:
	TextureClass *m_ptr;
};

class Gen_0092F190
{
public:
	~Gen_0092F190(void);

private:
	BfmeTexPtr m_first;
	BfmeTexPtr m_second;
};

Gen_0092F190 *MakeGen0092F190Array(void)
{
	return new Gen_0092F190[2];
}

void DeleteGen0092F190Array(Gen_0092F190 *array)
{
	delete[] array;
}
