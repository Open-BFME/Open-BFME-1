// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?Render@WW3D@@: Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp
// Open-BFME5: WW3D::Render(const LayerClass &), retail 0x008FE7D0,
// zh_sweep packet 008fe7d0.
//
// The Zero Hour body is one line and ports unchanged. What does not port is its
// type. Zero Hour returns WW3DErrorType, a plain enum with WW3D_ERROR_OK = 0,
// and that will not reproduce these bytes: retail answers the not-initted case
// with `b0 01`, a one-byte `mov al,1`, where an enum return emits `33 c0` or
// `b8 01 00 00 00`. Only al is ever written, and only al is ever read -- the
// sibling overload at 0x008FE810 tests this function's result with `cmp al,1`.
//
// A byte-wide value whose success case is 1 and which a caller compares with
// `!= 1` is a bool returning true. So these two overloads answer a bool where
// Zero Hour writes `return WW3D_ERROR_OK`. The mangled name is `_N` either way
// -- whether the header changed the functions or made WW3DErrorType a typedef
// for bool -- which is why the name can be spent on this reading.
//
// This is NOT a claim about WW3DErrorType generally. Nineteen ledger rows
// return it as a four-byte enum and byte-match doing so, from
// ?End_Render@WW3D@@ through the MeshModelClass read_* family. It is these two
// overloads that are narrow, and the evidence for that is local to them.
//
// Its own TU because ww3d.cpp declares the enum-returning overload and lands 25
// rows against it.

typedef float Real;

class SceneClass;
class CameraClass;

class Vector3
{
public:
	Real X, Y, Z;
};

// LISTNODE.H unchanged, and the list overload below dates every offset in it:
// Last() is one load from [list+0x18], which is LastNode.PrevNode once the
// vptr, FirstNode and LastNode are laid out in order, and Is_Valid() is the
// three tests -- this, NextNode, PrevNode -- that retail spells out.
class GenericNode
{
public:
	virtual ~GenericNode( void );

	GenericNode *Next( void ) const { return NextNode; }		///< +0x04
	GenericNode *Prev( void ) const { return PrevNode; }		///< +0x08
	bool Is_Valid( void ) const { return (this != (GenericNode *)0 && NextNode != (GenericNode *)0 && PrevNode != (GenericNode *)0); }

protected:
	GenericNode *NextNode;
	GenericNode *PrevNode;
};

template<class T> class Node : public GenericNode
{
public:
	T Next( void ) const { return (T)GenericNode::Next(); }
	T Prev( void ) const { return (T)GenericNode::Prev(); }
	bool Is_Valid( void ) const { return GenericNode::Is_Valid(); }
};

class GenericList
{
public:
	virtual ~GenericList( void );

	GenericNode *Last( void ) const { return LastNode.Prev(); }

protected:
	GenericNode FirstNode;									///< +0x04
	GenericNode LastNode;									///< +0x10
};

template<class T> class List : public GenericList
{
public:
	T Last( void ) const { return (T)GenericList::Last(); }
};

// Only the five fields these bodies forward are reconstructed; the spacing
// between them and the node base is retail's.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/layer.h
class LayerClass : public Node<LayerClass *>
{
public:
	bool Clear;												///< +0x0C
	bool ClearZ;											///< +0x0D
	unsigned char m_unreconstructed_0e[2];
	Vector3 ClearColor;										///< +0x10
	SceneClass *Scene;										///< +0x1C
	CameraClass *Camera;									///< +0x20
};

typedef List<LayerClass *> LayerListClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static bool Render( SceneClass *scene, CameraClass *cam, bool clear, bool clearz, const Vector3 &color );
	static bool Render( const LayerClass &Layer );
	static bool Render( const LayerListClass &LayerList );

private:
	static bool IsInitted;
};

// ?Render@WW3D@@SA_NABVLayerClass@@@Z
bool WW3D::Render(const LayerClass &Layer)
{
	if (!IsInitted) {
		return(true);
	}

	return Render(Layer.Scene, Layer.Camera, Layer.Clear, Layer.ClearZ, Layer.ClearColor);

}

// ?Render@WW3D@@SA_NABV?$List@PAVLayerClass@@@@@Z
//
// Retail inlines the overload above into this one -- the second IsInitted load
// at 0x008FE836 is that inlined copy's own guard -- and then compares the
// result with `cmp al,1`, which is the `!= true` this reading predicts.
bool WW3D::Render(const LayerListClass &LayerList)
{
	if (!IsInitted) {
		return(true);
	}

	LayerClass *layer = LayerList.Last();

	while (layer->Is_Valid()) {
		bool result = Render(*layer);

		if (result != true) {
			return result;
		}

		layer = layer->Prev();
	}

	return true;
}
