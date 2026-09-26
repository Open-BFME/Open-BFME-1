// cl: /DNDEBUG /MD /EHsc
//
// BFME recovery for retail RVA 0x005A3E00 (181 bytes).
// This is deliberately address-qualified.  The original ZH source calls the
// operation Keyboard::checkKeyRepeat, but BFME moved the event stream from the
// inline ZH array to a three-pointer vector at +0x0c.
//
// Identity anchors (read-only evidence):
//   * Keyboard ctor 0x005A3AC0 (69B) stores vtable 0x0110CD60.
//   * vtable 0x0110CD60 slot +0x14 -> j_0001ce45 -> 0x005A41F0.
//   * 0x005A41F0's tail call enters 0x005A3EF0, whose j_00039144 call
//     enters this body at 0x005A3E00.
//   * The ctor and the matched Keyboard implementation pin the event range
//     at +0x0c/+0x10/+0x14, status records at +0x18 (8-byte stride), names at
//     +0x818, and input frame at +0xe18.
//
// Retail extent: 0x005A3E00..0x005A3EB4 inclusive (181 bytes).  The only
// non-local relocation is j_00010e33 -> 0x005A3C00, the STL vector
// _M_insert_overflow body for this 8-byte event type.

// BFME recovery for retail RVA 0x005A3EF0 (179 bytes).
// The historical ZH source calls the operation Keyboard::updateKeys, but
// BFME splits acquisition (0x005A40E0) from this event/status pass.  The name
// below is intentionally address-qualified because the original BFME split-method spelling is
// unknown; constructor and vtable evidence establish Keyboard ownership.
//
// Identity anchors (read-only evidence):
//   * Keyboard ctor 0x005A3AC0 (69B) stores vtable 0x0110CD60.
//   * vtable slot +0x14 is j_0001ce45 -> 0x005A41F0; that body calls
//     0x005A40E0 and tail-jumps through j_00039671 -> this 0x005A3EF0.
//   * This body calls j_00039144 -> 0x005A3E00 and j_00025374 ->
//     0x005A3460 (the Keyboard modifier/character translation body; still ASM).
//   * The matched DirectInputKeyboard vtable 0x0111CDCC resolves slot +0x2c
//     through j_000149c0 -> 0x006BB320 (getKey), proving the surrounding
//     vector is Keyboard input state rather than an unrelated 8-byte array.
//
// Retail extent: 0x005A3EF0..0x005A3FA2 inclusive (179 bytes).  There are two
// direct/ILT code relocations: j_00025374 -> 0x005A3460 and j_00039144 ->
// 0x005A3E00.  No CRT/import calls occur in this body.


enum
{
	KEY_NONE   = 0x00,
	KEY_TAB    = 0x0f,
	KEY_CAPS   = 0x3a,
	KEY_LCTRL  = 0x1d,
	KEY_RCTRL  = 0x9d,
	KEY_LSHIFT = 0x2a,
	KEY_RSHIFT = 0x36,
	KEY_LALT   = 0x38,
	KEY_RALT   = 0xb8,
	KEY_STATE_DOWN = 0x0002
};

typedef unsigned char  UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int   UnsignedInt;
typedef bool           Bool;

struct KeyboardIO
{
	UnsignedByte  key;
	UnsignedByte  status;
	UnsignedShort state;
	UnsignedInt   sequence;
};

// The empty tag and helper signature follow the retail call to the existing
// STL body at RVA 0x005A3C00.  Its first three arguments are the insertion
// position, the value, and the false-type tag; the final two are count/flag.
struct BfmeFalseType
{
};

struct BfmeKeyboardEventVector
{
	KeyboardIO *begin;    // this+0x0c
	KeyboardIO *end;      // this+0x10
	KeyboardIO *capacity; // this+0x14

	void Rva005A3C00InsertOverflow( KeyboardIO *where,
		const KeyboardIO &value,
		const BfmeFalseType &tag,
		UnsignedInt count,
		bool one );

    void push_back(const KeyboardIO &value)
    {
        if (end != capacity)
        {
            if (end != 0)
                *end = value;
            ++end;
        }
        else
        {
            BfmeFalseType tag;
            Rva005A3C00InsertOverflow(end, value, tag, 1, true);
        }
    }
};

struct BfmeKeyboardKeyName
{
	UnsignedShort standard;
	UnsignedShort shifted;
	UnsignedShort shifted2;
};

// The address-qualified owner matches the caller at RVA0x005A3EF0.
// Raw offsets retain the established Keyboard layout.  The eight-byte prefix includes
// the inherited vptr/name pair; the rest is the proven BFME object layout.
class Rva005A3EF0Keyboard
{
public:
	void processKeyEvents(void);
	UnsignedShort Rva005A3460TranslateKey(UnsignedShort keyCode);
	Bool Rva005A3E00CheckRepeat(void);

	UnsignedByte m_basePrefix[ 8 ];
	UnsignedShort m_modifiers; // +0x08
	UnsignedByte m_shift2Key;  // +0x0a
	UnsignedByte m_pad0b;
	BfmeKeyboardEventVector m_events; // +0x0c
	KeyboardIO m_keyStatus[ 256 ];  // +0x18 .. +0x818
	BfmeKeyboardKeyName m_keyNames[ 256 ]; // +0x818 .. +0xe18
	UnsignedInt m_inputFrame; // +0xe18
};

// Preserve the original nested loop and return-value structure, with the
// BFME vector replacing the older inline event array. No volatile or assembly.
Bool Rva005A3EF0Keyboard::Rva005A3E00CheckRepeat(void)
{
    Bool retVal = false;
    int key;
    for (key = 0; key < 256; ++key)
    {
        if ((m_keyStatus[key].state & 2) != 0)
        {
            if ((m_inputFrame - m_keyStatus[key].sequence) > 10)
            {
                KeyboardIO repeat;
                repeat.key = (UnsignedByte)key;
                repeat.state = 0x0102;
                repeat.status = 0;
                m_events.push_back(repeat);
                for (int index = 0; index < 256; ++index)
                    m_keyStatus[index].sequence = m_inputFrame;
                m_keyStatus[key].sequence = m_inputFrame - 12;
                retVal = true;
                break;
            }
        }
    }
    return retVal;
}

// @?processKeyEvents@Rva005A3EF0Keyboard@@QAEXXZ 0x005A3EF0
void Rva005A3EF0Keyboard::processKeyEvents( void )
{
	KeyboardIO *event = m_events.begin;
	KeyboardIO *end = m_events.end;

	while( event != end )
	{
		m_keyStatus[ event->key ].state = event->state;
		m_keyStatus[ event->key ].status = event->status;
		m_keyStatus[ event->key ].sequence = m_inputFrame;

		// Prevent ALT-TAB from creating a TAB event.
		if( event->key == KEY_TAB )
		{
			if( (m_keyStatus[ KEY_LALT ].state & KEY_STATE_DOWN) != 0 ||
				(m_keyStatus[ KEY_RALT ].state & KEY_STATE_DOWN) != 0 )
			{
				event->status = 1;
			}
		}
		else if( event->key == KEY_CAPS || event->key == KEY_LCTRL ||
			event->key == KEY_RCTRL || event->key == KEY_LSHIFT ||
			event->key == KEY_RSHIFT || event->key == KEY_LALT ||
			event->key == KEY_RALT )
		{
			// Retail ignores the return value; the call updates modifier state.
			Rva005A3460TranslateKey( (UnsignedShort)event->key );
		}

		++event;
	}

	Rva005A3E00CheckRepeat();

	if( m_modifiers != 0 )
	{
		KeyboardIO *modifier_end = m_events.end;
		event = m_events.begin;
		while( event != modifier_end )
		{
			event->state = (UnsignedShort)(event->state | m_modifiers);
			++event;
		}
	}
}
