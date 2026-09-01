// cl: /DNDEBUG /MD /EHsc

class DX8Caps
{
public:
	~DX8Caps();
};

void Force_DX8Caps_Deleting_Destructor(DX8Caps *caps)
{
	delete caps;
}
