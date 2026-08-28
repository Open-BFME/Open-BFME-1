// cl: /DNDEBUG /MD /EHsc

class RenderObjClass
{
public:
	virtual ~RenderObjClass();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/bmp2d.h
class Bitmap2DObjClass : public RenderObjClass
{
public:
	Bitmap2DObjClass(const Bitmap2DObjClass &that);
	virtual RenderObjClass *Clone() const;

private:
	unsigned char m_data[0x108];
};

RenderObjClass *Bitmap2DObjClass::Clone() const
{
	return new Bitmap2DObjClass(*this);
}
