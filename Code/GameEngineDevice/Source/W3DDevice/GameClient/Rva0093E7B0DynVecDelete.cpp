// ?Delete@?$DynamicVectorClass@URendererDataStruct@Render2DSentenceClass@@@@QAE_NH@Z
// Open-BFME7: DynamicVectorClass<RendererDataStruct>::Delete(int) at
// 0x0093E7B0. Element assignment AddRefs the incoming Surface pointer then
// Releases the outgoing one (COM-style vtable slots 1/2) before the raw
// Renderer pointer is copied in place; near-twin of the local
// DynamicVectorClass model already used for Render2DSentenceClass::Reset in
// Render2DSentenceClassReset.cpp.

class Rva0093E7B0Ref
{
public:
	virtual void __stdcall QueryInterface();
	virtual void __stdcall AddRef();
	virtual void __stdcall Release();
};

template <class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass() {}
	int Count(void) const { return m_activeCount; }
	T &operator[](int index) { return m_vector[index]; }
	bool Delete(int index);

public:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	char m_pad0a[2];
	int m_activeCount;
	int m_growthStep;
};

template <class T>
bool DynamicVectorClass<T>::Delete(int index)
{
	if (index < m_activeCount)
	{
		m_activeCount--;
		for (int i = index; i < m_activeCount; i++)
			(*this)[i] = (*this)[i + 1];
		return true;
	}
	return false;
}

class Render2DSentenceClass
{
public:
	struct RendererDataStruct
	{
		void *Renderer;
		Rva0093E7B0Ref *Surface;

		RendererDataStruct &operator=(const RendererDataStruct &other)
		{
			Renderer = other.Renderer;
			if (other.Surface)
				other.Surface->AddRef();
			if (Surface)
				Surface->Release();
			Surface = other.Surface;
			return *this;
		}
	};
};

template bool DynamicVectorClass<Render2DSentenceClass::RendererDataStruct>::Delete(int);
