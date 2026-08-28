// cl: /DNDEBUG /MD /EHsc

// Slot 78, immediately after Control_Bone at slot 77, which is exactly where
// animobj.h declares it:
//
//     virtual void                Control_Bone(int, const Matrix3D &, bool);
//     virtual const HTreeClass *  Get_HTree(void) const { return HTree; }
//
// The body is a seven-byte getter returning the pointer member at +0xFC, and the
// four bone methods in the slots just below all read that same member -- HTree is
// what they operate on.
class HTreeClass;
class Matrix3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
public:
	virtual ~Animatable3DObjClass();
	virtual void Capture_Bone(int boneindex);
	virtual void Release_Bone(int boneindex);
	virtual bool Is_Bone_Captured(int boneindex) const;
	virtual void Control_Bone(int bindex, const Matrix3D &objtm, bool world_space_translation);
	virtual const HTreeClass *Get_HTree(void) const;

private:
	unsigned char m_head[0xF8];
	HTreeClass *m_htree;
};

// ?Get_HTree@Animatable3DObjClass@@UBEPBVHTreeClass@@XZ
const HTreeClass *Animatable3DObjClass::Get_HTree(void) const
{
	return m_htree;
}
