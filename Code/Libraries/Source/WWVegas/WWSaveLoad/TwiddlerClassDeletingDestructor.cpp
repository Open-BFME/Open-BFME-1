// cl: /O2
// Open-BFME: TwiddlerClass scalar-deleting destructor wrapper, retail
// 0x0078F9D0 (30 bytes). TwiddlerClass vtable 0x01126ED0 slot zero routes
// here through ILT 0x00006550; the matched constructor at 0x0078F500
// installs that vtable and the wrapper calls the destructor through its ILT.

class TwiddlerClass
{
public:
    __declspec(noinline) virtual ~TwiddlerClass();
};

TwiddlerClass::~TwiddlerClass()
{
}
