// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class GameWindow
{
public:
	void *winGetUserData();
	unsigned int winClearStatus(unsigned int status);
	unsigned int winSetStatus(unsigned int status);
};

struct ComboBoxDataBFME
{
	bool isEditable;
	unsigned char unused01[0x27];
	GameWindow *editBox;
};

void GadgetComboBoxSetIsEditable(GameWindow *comboBox, bool isEditable)
{
	ComboBoxDataBFME *comboData = (ComboBoxDataBFME *)comboBox->winGetUserData();
	ComboBoxDataBFME *componentData = (ComboBoxDataBFME *)comboBox->winGetUserData();
	GameWindow *editBox = componentData ? componentData->editBox : 0;

	if (!editBox)
		return;

	comboData->isEditable = isEditable;
	if (isEditable)
		editBox->winClearStatus(0x600);
	else
		editBox->winSetStatus(0x600);
}
