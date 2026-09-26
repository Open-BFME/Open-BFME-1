// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ControlBarSchemeImage scalar-deleting destructor at retail
// 0x004ACE00 (30 bytes).  The matched constructor at 0x004ACD00 and complete
// destructor at 0x004ACD70 establish the class identity in ControlBarScheme.cpp.

class ControlBarSchemeImage
{
public:
	~ControlBarSchemeImage();
};

void Force_ControlBarSchemeImage_Deleting_Destructor(
	ControlBarSchemeImage *value)
{
	delete value;
}
