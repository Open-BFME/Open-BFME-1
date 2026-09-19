// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME: clean C++ instantiation of VectorClass<HLodClass::ModelNodeClass>
// assignment at retail RVA 0x0097ACA0 (234 bytes).
//
// This TU deliberately keeps the known BFME ModelNode layout local.  The
// retail vector body calls the element's non-trivial default constructor when
// allocating (the Vector3 member makes that constructor non-trivial), then
// copies all five words of the 0x14-byte node.  The explicit state updates are
// the BFME VectorClass ABI; the reference header's generic assignment omits
// those two IsValid transitions and therefore cannot reproduce this body.

void __cdecl operator delete[](void *) throw();

#include "vector3.h"

class RenderObjClass;

class HLodClass
{
public:
	class ModelNodeClass
	{
	public:
		RenderObjClass *Model;
		int BoneIndex;
		Vector3 Offset;

		bool operator == (const ModelNodeClass &that) const
		{
			return (Model == that.Model) && (BoneIndex == that.BoneIndex);
		}

		bool operator != (const ModelNodeClass &that) const
		{
			return !operator == (that);
		}
	};
};

template<class T>
class VectorClass
{
public:
	virtual ~VectorClass(void);
	virtual bool operator == (const VectorClass<T> &) const;
	virtual bool Resize(int, const T * = 0);
	virtual void Clear(void);
	virtual int ID(const T *);
	virtual int ID(const T &);

	VectorClass<T> &operator = (const VectorClass<T> &that)
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

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template VectorClass<HLodClass::ModelNodeClass> &
VectorClass<HLodClass::ModelNodeClass>::operator =
	(const VectorClass<HLodClass::ModelNodeClass> &);
