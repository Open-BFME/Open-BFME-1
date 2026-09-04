// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Bfme5TextWidget's by-value UnicodeString setter.  The parameter is compared
// with the inline StringBase member before the member is replaced and the
// widget notification is dispatched.

class UnicodeString;
class Rva004101B0TextWidget;

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &other) const;
	void set(const StringBase<T> &other);

private:
	friend class UnicodeString;
	friend class Rva004101B0TextWidget;
	StringBase();
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class Rva004101B0TextWidget
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void onTextChanged();

	void setText(UnicodeString text);

	StringBase<unsigned short> m_text;
};

void Rva004101B0TextWidget::setText(UnicodeString text)
{
	if (text.compare(m_text) != 0)
	{
		m_text.set(text);
		onTextChanged();
	}
}
