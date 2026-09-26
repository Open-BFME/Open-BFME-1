// cl: /DNDEBUG /MD /EHsc
// Authentic W3DRadar destructor ILT at retail 0x0001FD3E.

class W3DRadarDestructorBody
{
public:
	void destroy();
};

class __declspec(novtable) W3DRadar
{
public:
	virtual ~W3DRadar();
};

W3DRadar::~W3DRadar()
{
	((W3DRadarDestructorBody *)this)->destroy();
}
