// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TeamTemplateInfo scalar-deleting destructor at retail
// 0x000F0D70 (30 bytes).  The matched complete destructor at 0x000ED580,
// constructor at 0x000EFEB0, and named TeamTemplateInfo methods establish the
// class identity.

class TeamTemplateInfo
{
public:
	~TeamTemplateInfo();
};

void Force_TeamTemplateInfo_Deleting_Destructor(TeamTemplateInfo *value)
{
	delete value;
}
