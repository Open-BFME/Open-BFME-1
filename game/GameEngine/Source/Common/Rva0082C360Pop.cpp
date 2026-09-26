// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

namespace _STL
{
template <class T>
struct char_traits
{
};

template <>
struct char_traits<char>
{
  static void assign(char &, const char &);
};
}

class Rva0082C360Buf
{
public:
  void pop();

private:
  char *m_start;
  char *m_finish;
};

void Rva0082C360Buf::pop()
{
  char dummy = 0;
  _STL::char_traits<char>::assign(*(m_finish - 1), dummy);
  m_finish = m_finish - 1;
}
