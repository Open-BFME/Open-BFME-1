// cl: /DNDEBUG /MD
// Nine retail bodies share one 15-byte shape: forward the one stack argument
// plus a constant flag to a two-argument callee, ret 4:
//   mov eax,[esp+4]; push <flag>; push eax; call <callee>; ret 4
// Their ?dup_ rows used to take these bytes from Zero Hour's inline
// Pathfinder::add/removeObjectFromPathfindMap copy compiled into Player.cpp.
// BFME's real add/removeObjectToPathfindMap are three-argument out-of-line
// functions (PathfindMapObjectWrappers.cpp), so that copy no longer exists;
// each body is written here against its own retail callee (read from the
// call site's ILT thunk). Identities stay unknown: the rows keep their
// address names, and every wrapper below is address-named.

class ModelConditionFlags;

// 0x00229F90 -> ILT 0x000307E7 -> Object::applyRva1C7370 (pinned)
class Object
{
public:
	void applyRva1C7370(const ModelConditionFlags &flags, bool set);
	void rva00229F90(const ModelConditionFlags &flags);
};

void Object::rva00229F90(const ModelConditionFlags &flags)
{
	applyRva1C7370(flags, false);
}

// 0x002ED640 -> ILT 0x0003921B -> BfmeGlobalDFD::bfmeRunDFD (pinned)
class BfmeGlobalDFD
{
public:
	void bfmeRunDFD(int value, int flag);
	void rva002ED640(int value);
};

void BfmeGlobalDFD::rva002ED640(int value)
{
	bfmeRunDFD(value, 0);
}

// 0x002ED660 -> ILT 0x0002054F -> BfmeSinkBMF::bfmeDoBMF (pinned)
class BfmeSinkBMF
{
public:
	void bfmeDoBMF(int value, int flag);
	void rva002ED660(int value);
};

void BfmeSinkBMF::rva002ED660(int value)
{
	bfmeDoBMF(value, 0);
}

// 0x00532980 / 0x005329A0 -> ILT 0x00047807 -> bfmeNote1049 (pinned, __stdcall)
void __stdcall bfmeNote1049(int value, int flag);

void __stdcall rva00532980(int value)
{
	bfmeNote1049(value, 0);
}

void __stdcall rva005329A0(int value)
{
	bfmeNote1049(value, 1);
}

// The last four forward to matched STLport vector<T>::resize(count, fill)
// bodies, passing `this` straight through: the vector sits at this+0 of an
// owner nobody has identified, and the pushed constant is T(0). BFME's resize
// takes the fill BY VALUE (IntVectorResizeThunk.cpp has the evidence), so the
// class is spelled here with just that declaration, like the *ResizeThunk.cpp
// family that defines each callee.
enum ObjectID {};

namespace _STL
{

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	void resize(unsigned int count, Type value);

private:
	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

}

// 0x001DC500 -> ILT 0x0004AEFD -> 0x001DC360 vector<int>::resize (matched)
class Rva001DC500Owner
{
	_STL::vector<int, _STL::allocator<int> > m_values;	// this+0x00

public:
	void rva001DC500(unsigned int count);
};

void Rva001DC500Owner::rva001DC500(unsigned int count)
{
	m_values.resize(count, 0);
}

// 0x00754DF0 -> ILT 0x0002237C -> 0x00754A60 vector<Object *>::resize (matched)
class Rva00754DF0Owner
{
	_STL::vector<Object *, _STL::allocator<Object *> > m_objects;	// this+0x00

public:
	void rva00754DF0(unsigned int count);
};

void Rva00754DF0Owner::rva00754DF0(unsigned int count)
{
	m_objects.resize(count, 0);
}

// 0x002CD490 -> ILT 0x0004ADE0 -> 0x002CD1B0 vector<ObjectID>::resize (matched)
class Rva002CD490Owner
{
	_STL::vector<ObjectID, _STL::allocator<ObjectID> > m_ids;	// this+0x00

public:
	void rva002CD490(unsigned int count);
};

void Rva002CD490Owner::rva002CD490(unsigned int count)
{
	m_ids.resize(count, (ObjectID)0);
}

// 0x00459FE0 -> ILT 0x0003CAA1 -> 0x00459F70 vector<float>::resize (matched)
class Rva00459FE0Owner
{
	_STL::vector<float, _STL::allocator<float> > m_values;	// this+0x00

public:
	void rva00459FE0(unsigned int count);
};

void Rva00459FE0Owner::rva00459FE0(unsigned int count)
{
	m_values.resize(count, 0.0f);
}
