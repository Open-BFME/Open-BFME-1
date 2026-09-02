// cl: /DNDEBUG /MD /EHsc
// Clean C++ instantiation of the four-byte trivial VectorClass assignment body.

template<class T>
class VectorClass
{
public:
	virtual ~VectorClass(void);
	virtual bool operator==(const VectorClass<T> &that) const;
	virtual bool Resize(int size, const T *array = 0);
	virtual void Clear(void);
	virtual int ID(const T *ptr);
	virtual int ID(const T &value);

	VectorClass<T> &operator=(const VectorClass<T> &that);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool Pad[2];
};

template<class T>
VectorClass<T> &VectorClass<T>::operator=(const VectorClass<T> &that)
{
	if (this != &that) {
		Clear();
		IsValid = false;
		VectorMax = that.VectorMax;
		if (VectorMax) {
			Vector = new T[VectorMax];
			if (Vector) {
				IsAllocated = true;
				IsValid = true;
				for (int index = 0; index < VectorMax; ++index)
					Vector[index] = that.Vector[index];
			}
		} else {
			Vector = 0;
			IsAllocated = false;
			IsValid = true;
		}
	}
	return *this;
}

template VectorClass<int> &VectorClass<int>::operator=(const VectorClass<int> &that);
