// ?setText@SuperweaponInfo@@QAEXABVUnicodeString@@0@Z
// partial score=0.82 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
class UnicodeString
{
private:
	void *m_data;
public:
	UnicodeString(const UnicodeString &that);
	~UnicodeString();
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
};

class SuperweaponInfo
{
private:
	void *m_vtable;
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;
public:
	void setText(const UnicodeString &name, const UnicodeString &time);
};

void SuperweaponInfo::setText(const UnicodeString &name, const UnicodeString &time)
{
	m_nameDisplayString->setText(UnicodeString(name));
	m_timeDisplayString->setText(UnicodeString(time));
}
