import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eh_info


def image():
    data = bytearray(0x1000)
    data[0x100:0x107] = b"\x6a\xff\x68" + struct.pack("<I", 0x400200)
    data[0x200:0x20a] = b"\xb8" + struct.pack("<I", 0x400300) + b"\xe9\x00\x00\x00\x00"
    data[0x300:0x30c] = struct.pack("<IiI", eh_info.MAGIC, 3, 0x400400)
    data[0x400:0x418] = struct.pack("<iIiIiI", -1, 0x400500, 0, 0, 1, 0x400600)
    return data


def test_states_and_null_action():
    data = image()
    assert eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100) == (
        0x200, 0x300, [(0, -1, 0x500), (1, 0, None), (2, 1, 0x600)])


def test_registration_load_before_state_push():
    data = image()
    data[0x100:0x10d] = b"\x64\xa1\x00\x00\x00\x00" + data[0x100:0x107]
    assert eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100) == (
        0x200, 0x300, [(0, -1, 0x500), (1, 0, None), (2, 1, 0x600)])


def test_state_push_before_registration_load():
    data = image()
    data[0x100:0x115] = (
        b"\x6a\xff\x64\xa1\x00\x00\x00\x00\x68"
        + struct.pack("<I", 0x400200)
        + b"\x50\x64\x89\x25\x00\x00\x00\x00"
    )
    assert eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100) == (
        0x200, 0x300, [(0, -1, 0x500), (1, 0, None), (2, 1, 0x600)])


def test_alternate_prologue_requires_full_registration_store():
    data = image()
    data[0x100:0x115] = (
        b"\x6a\xff\x64\xa1\x00\x00\x00\x00\x68"
        + struct.pack("<I", 0x400200)
        + b"\x50\x64\x89\x25\x00\x00\x00\x00"
    )
    data[0x10d] = 0x51
    with pytest.raises(ValueError, match="unsupported EH prologue"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


@pytest.mark.parametrize("prefix", [b"\x64\xa1\x04\x00\x00\x00", b"\x90" * 6])
def test_unrecognized_prefix_is_not_scanned(prefix):
    data = image()
    data[0x100:0x10d] = prefix + data[0x100:0x107]
    with pytest.raises(ValueError, match="unsupported EH prologue"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


def test_truncated_prefixed_prologue_rejected():
    data = image()
    data[0x100:0x10d] = b"\x64\xa1\x00\x00\x00\x00" + data[0x100:0x107]
    data = data[:0x10b]
    with pytest.raises(ValueError, match="unsupported EH prologue"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


@pytest.mark.parametrize("offset,value", [(0x100, 0x90), (0x200, 0x90), (0x300, 0), (0x400, 1)])
def test_bad_metadata_rejected(offset, value):
    data = image()
    data[offset] = value
    with pytest.raises(ValueError):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


def test_truncated_map_rejected():
    data = image()[:0x410]
    with pytest.raises(ValueError, match="truncated unwind map"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


def test_cleanup_adjustment_and_ilt_resolution():
    pytest.importorskip("capstone")
    data = image()
    data[0x500:0x50b] = b"\x8b\x4d\xe4\x83\xc1\x08\xe9" + struct.pack("<i", 0x700 - 0x50b)
    data[0x700:0x705] = b"\xe9" + struct.pack("<i", 0x800 - 0x705)
    lines = list(eh_info.action_instructions(lambda r, n: data[r:r+n], 0x500))
    assert len(lines) == 3
    assert "add ecx, 8" in lines[1]
    assert "ILT -> RVA 0x00000800" in lines[2]


def catch_image(blocks, state_count=10):
    data = image()
    data[0x300:0x314] = struct.pack("<IiIII", eh_info.MAGIC, state_count, 0x400400,
                                  len(blocks), 0x400700 if blocks else 0)
    for index, (low, high, catch_high, handlers) in enumerate(blocks):
        address = 0x800 + index * 0x40
        struct.pack_into("<iiiiI", data, 0x700 + index * 20,
                         low, high, catch_high, len(handlers), 0x400000 + address)
        for handler_index, record in enumerate(handlers):
            struct.pack_into("<IIiI", data, address + handler_index * 16, *record)
    return data


def test_catch_info_zero_try_blocks_and_states():
    data = catch_image([], state_count=0)
    assert eh_info.catch_info(lambda r, n: data[r:r+n], 0x300) == ()


def test_catch_info_nested_and_multiple_typed_handlers():
    data = catch_image([
        (0, 6, 9, [(0, 0, 0, 0x400a00)]),
        (1, 2, 3, [(8, 0x400900, -12, 0x400a10), (0, 0, 0, 0x400a20)]),
        (4, 4, 5, [(1, 0x400920, 4, 0x400a30)]),
    ])
    blocks = eh_info.catch_info(lambda r, n: data[r:r+n], 0x300)
    assert [(b.try_low, b.try_high, b.catch_high) for b in blocks] == [(0, 6, 9), (1, 2, 3), (4, 4, 5)]
    assert blocks[1].handlers == (
        eh_info.CatchHandler(8, 0x900, -12, 0xa10),
        eh_info.CatchHandler(0, None, 0, 0xa20))
    assert blocks[2].handlers == (eh_info.CatchHandler(1, 0x920, 4, 0xa30),)


def winmain_metadata():
    actions = [None, 0xbf2730, 0xbf2738, 0xbf2743, 0xbf274e,
               0xbf2759, 0xbf2764, 0xbf276c, 0xbf2774, None]
    previous = [-1, 0, 1, 2, 3, 0, 0, 6, 7, -1]
    blobs = {
        0x600f3: b"\x6a\xff\x68" + struct.pack("<I", 0xff277c) + b"\x64",
        0xbf277c: b"\xb8" + struct.pack("<I", 0x11dfbdc) + b"\xe9\0\0\0\0",
        0xddfbdc: struct.pack("<IiIII", eh_info.MAGIC, 10, 0x11dfb68, 1, 0x11dfbc8),
        0xddfb68: b"".join(struct.pack("<iI", p, 0x400000 + a if a else 0)
                             for p, a in zip(previous, actions)),
        0xddfbc8: struct.pack("<iiiiI", 0, 8, 9, 1, 0x11dfbb8),
        0xddfbb8: struct.pack("<IIiI", 0, 0, 0, 0x46063c),
        0x6063c: b"\xb8\xd3\x04\x46\x00\xc3",
    }

    def read(rva, size):
        for start, blob in blobs.items():
            if start <= rva < start + len(blob):
                return blob[rva-start:rva-start+size]
        raise ValueError(f"unmapped synthetic WinMain RVA 0x{rva:X}")

    return read


def test_winmain_catch_is_owned_by_its_funcinfo_not_a_constant_getter():
    read = winmain_metadata()
    handler, info, states = eh_info.unwind_info(read, 0x600f3)
    assert (handler, info, len(states)) == (0xbf277c, 0xddfbdc, 10)
    assert eh_info.catch_info(read, info) == (
        eh_info.TryBlock(0, 8, 9, (eh_info.CatchHandler(0, None, 0, 0x6063c),)),)
    assert read(0x6063c, 6) == b"\xb8\xd3\x04\x46\x00\xc3"


@pytest.mark.parametrize("low,high,catch_high", [(-1, 1, 2), (2, 1, 3), (0, 10, 10), (0, 2, 1), (0, 1, 10)])
def test_catch_info_rejects_invalid_state_ranges(low, high, catch_high):
    data = catch_image([(low, high, catch_high, [(0, 0, 0, 0x400a00)])])
    with pytest.raises(ValueError, match="try block 0: invalid state range"):
        eh_info.catch_info(lambda r, n: data[r:r+n], 0x300)


@pytest.mark.parametrize("offset,value,message", [
    (0x300, 0, "unsupported magic"),
    (0x304, 0xffffffff, "unwind-state count"),
    (0x304, 4097, "unwind-state count"),
    (0x30c, 4097, "try-block count"),
    (0x310, 0, "try-block map: invalid VA"),
    (0x310, 0xffffffff, "try-block map: RVA range"),
    (0x70c, 0, "invalid handler count"),
    (0x70c, 0xffffffff, "invalid handler count"),
    (0x70c, 4097, "invalid handler count"),
    (0x710, 0x3fffff, "handlers: invalid VA"),
    (0x710, 0xffffffff, "handlers: RVA range"),
    (0x804, 1, "TypeDescriptor: invalid VA"),
    (0x804, 0x400ffc, "TypeDescriptor: truncated"),
    (0x804, 0xffffffff, "TypeDescriptor: RVA range"),
    (0x80c, 0, "handler 0: invalid VA"),
    (0x80c, 0x401000, "handler 0: truncated"),
])
def test_catch_info_rejects_bad_counts_and_pointers(offset, value, message):
    data = catch_image([(0, 1, 2, [(0, 0, 0, 0x400a00)])])
    struct.pack_into("<I", data, offset, value)
    with pytest.raises(ValueError, match=message):
        eh_info.catch_info(lambda r, n: data[r:r+n], 0x300)


@pytest.mark.parametrize("end,message", [
    (0x313, "FuncInfo catch header: truncated"),
    (0x713, "try-block map: truncated"),
    (0x80f, "try block 0 handlers: truncated"),
])
def test_catch_info_requires_exact_reads(end, message):
    data = catch_image([(0, 1, 2, [(0, 0, 0, 0x400a00)])])[:end]
    with pytest.raises(ValueError, match=message):
        eh_info.catch_info(lambda r, n: data[r:r+n], 0x300)


@pytest.mark.parametrize("error_type", [OSError, ValueError, SystemExit])
def test_catch_info_contextualizes_reader_failure(error_type):
    def read(rva, size):
        raise error_type("synthetic unmapped metadata")
    with pytest.raises(ValueError, match="FuncInfo catch header: cannot read RVA 0x00000300.*synthetic unmapped"):
        eh_info.catch_info(read, 0x300)


def test_cli_winmain_catch_with_known_prologue_offset(monkeypatch, capsys):
    from types import SimpleNamespace
    monkeypatch.setitem(sys.modules, "build", SimpleNamespace(read_target_bytes=winmain_metadata()))
    monkeypatch.setattr(eh_info, "action_instructions", lambda read, rva: ())
    monkeypatch.setattr(sys, "argv", ["eh_info.py", "0x600F0", "--prologue-offset", "3"])
    eh_info.main()
    out = capsys.readouterr().out
    assert "EH prologue RVA 0x000600F3 (input +0x3)" in out
    assert "handler RVA 0x00BF277C; FuncInfo RVA 0x00DDFBDC; 10 unwind states" in out
    assert "try 0: states 0..8; catch-high 9" in out
    assert "catch-all; handler RVA 0x0006063C" in out
    assert "do not prove source identity, boundaries or exception equivalence" in out


def test_cli_typed_metadata(monkeypatch, capsys):
    from types import SimpleNamespace
    data = catch_image([(0, 1, 2, [(8, 0x400900, -12, 0x400a00)])], state_count=3)
    monkeypatch.setitem(sys.modules, "build", SimpleNamespace(read_target_bytes=lambda r, n: data[r:r+n]))
    monkeypatch.setattr(eh_info, "action_instructions", lambda read, rva: ())
    monkeypatch.setattr(sys, "argv", ["eh_info.py", "0x100"])
    eh_info.main()
    out = capsys.readouterr().out
    assert "typed (TypeDescriptor RVA 0x00000900)" in out
    assert "adjectives 0x00000008; object displacement -0xc" in out


def test_cli_rejects_truncated_catch_map_without_partial_success(monkeypatch, capsys):
    from types import SimpleNamespace
    data = catch_image([(0, 1, 2, [(0, 0, 0, 0x400a00)])], state_count=3)[:0x713]
    monkeypatch.setitem(sys.modules, "build", SimpleNamespace(read_target_bytes=lambda r, n: data[r:r+n]))
    monkeypatch.setattr(sys, "argv", ["eh_info.py", "0x100"])
    with pytest.raises(SystemExit) as error:
        eh_info.main()
    assert error.value.code == 1
    output = capsys.readouterr()
    assert output.out == ""
    assert "try-block map: truncated" in output.err


@pytest.mark.parametrize("args", [["0x100", "--prologue-offset", "-1"], ["0xffffffff"]])
def test_cli_rejects_invalid_prologue_offset(args, monkeypatch):
    monkeypatch.setattr(sys, "argv", ["eh_info.py"] + args)
    with pytest.raises(SystemExit) as error:
        eh_info.main()
    assert error.value.code == 2
