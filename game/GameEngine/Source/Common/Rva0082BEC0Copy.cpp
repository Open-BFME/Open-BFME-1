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

class Rva0082BEC0Copy
{
public:
  void copy(char *first, char *last, char *out);
};

void Rva0082BEC0Copy::copy(char *first, char *last, char *out)
{
  for (; first != last; ++first, ++out)
    _STL::char_traits<char>::assign(*out, *first);
}

class Rva0082BF40Copy
{
public:
  void copy(char *first, char *last, char *out);
};

void Rva0082BF40Copy::copy(char *first, char *last, char *out)
{
  for (; first != last; ++first, ++out)
    _STL::char_traits<char>::assign(*out, *first);
}
