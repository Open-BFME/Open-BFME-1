// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Retail 0x00943D50 is the vector-deleting wrapper used by the BFME scene
// vector.  The scalar callback is the existing offset thunk at 0x00943970,
// which names the matched BfmeSceneVectorElement destructor.  The retail
// __ehvec_dtor operand fixes each scene-vector element at 0x1C bytes.
void operator delete[](void *block);

class BfmeSceneVectorElement
{
public:
	~BfmeSceneVectorElement(void);

private:
	unsigned char m_storage[0x1c];
};

BfmeSceneVectorElement *MakeBfmeSceneVectorElementArray(void)
{
	return new BfmeSceneVectorElement[2];
}

void DeleteBfmeSceneVectorElementArray(BfmeSceneVectorElement *array)
{
	delete[] array;
}
