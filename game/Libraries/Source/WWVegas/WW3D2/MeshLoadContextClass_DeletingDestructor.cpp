// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: MeshLoadContextClass scalar-deleting destructor at retail
// 0x0096FF50 (30 bytes).  The matched private constructor at 0x00970180 and
// private complete destructor at 0x0096FD30 establish the class identity;
// the neighboring meshmdlio TUs provide the named context methods and layout.

class MeshLoadContextClass
{
	friend void Force_MeshLoadContextClass_Deleting_Destructor(
		MeshLoadContextClass *value);

private:
	~MeshLoadContextClass();
};

void Force_MeshLoadContextClass_Deleting_Destructor(
	MeshLoadContextClass *value)
{
	delete value;
}
