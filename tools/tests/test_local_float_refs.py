"""Masked local data operands must still reproduce the value retail loads."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def fixture(monkeypatch, tmp_path, value, *, symbol_value=0, writable=False,
            section_name='.rdata', storage=3, data_reloc=None, duplicate=False):
    obj = tmp_path / 'one.obj'
    obj.write_bytes(b'object')
    data = bytearray(256)
    struct.pack_into('<I', data, 56, 0x80000000 if writable else 0x40000040)
    data[128:128 + len(value)] = value
    if data_reloc is not None:
        struct.pack_into('<I', data, 100, data_reloc)
    section = {'name': section_name, 'raw_size': len(value), 'raw_pointer': 128,
               'reloc_count': int(data_reloc is not None), 'reloc_pointer': 100}
    symbol = {'name': '_constant', 'section': 1, 'storage': storage, 'value': symbol_value}
    symbols = [symbol, dict(symbol, value=4)] if duplicate else [symbol]
    monkeypatch.setattr(build, '_object_layout', lambda *args: (bytes(data), [section], symbols))
    return obj


def test_array_window_uses_symbol_value_and_addend(monkeypatch, tmp_path):
    obj = fixture(monkeypatch, tmp_path, b'ABCDEFGH' + struct.pack('<f', .75), symbol_value=4)
    body = bytes.fromhex('d90504000000c3')  # fld dword [symbol+4]
    assert list(build.local_float_refs(obj, body, [(2, 6, '_constant')])) == [
        (2, '_constant', struct.pack('<f', .75))]


@pytest.mark.parametrize('opcode,width', [('d905', 4), ('dd05', 8), ('db2d', 10),
                                         ('df05', 2), ('db05', 4), ('df2d', 8)])
def test_decoded_float_and_integer_load_widths(monkeypatch, tmp_path, opcode, width):
    obj = fixture(monkeypatch, tmp_path, bytes(range(16)))
    body = bytes.fromhex(opcode + '00000000c3')
    assert list(build.local_float_refs(obj, body, [(2, 6, '_constant')])) == [
        (2, '_constant', bytes(range(width)))]


@pytest.mark.parametrize('opcode', ['d805', 'd825', 'd82d', 'd80d', 'd835', 'd83d',
                                    'd815', 'd81d', 'da05', 'de05'])
def test_arithmetic_and_comparison_reads(monkeypatch, tmp_path, opcode):
    obj = fixture(monkeypatch, tmp_path, b'abcdefgh')
    body = bytes.fromhex(opcode + '00000000c3')
    found = list(build.local_float_refs(obj, body, [(2, 6, '_constant')]))
    assert len(found) == 1 and found[0][2] == (b'ab' if opcode == 'de05' else b'abcd')


@pytest.mark.parametrize('kwargs', [{'writable': True}, {'section_name': '.data'},
                                    {'storage': 2}, {'data_reloc': 2}, {'duplicate': True}])
def test_nonliteral_or_nonlocal_data_is_outside_scope(monkeypatch, tmp_path, kwargs):
    obj = fixture(monkeypatch, tmp_path, b'abcdefgh', **kwargs)
    assert list(build.local_float_refs(obj, bytes.fromhex('d90500000000c3'),
                                       [(2, 6, '_constant')])) == []


@pytest.mark.parametrize('body,offset', [('d91d00000000c3', 2),  # fstp writes
                                         ('8d0500000000c3', 2),  # address, no load
                                         ('d9048500000000c3', 3),  # indexed array
                                         ('d98000000000c3', 2),  # base-relative
                                         ('64d90500000000c3', 3)])  # segment-relative
def test_only_absolute_numeric_reads_are_checked(monkeypatch, tmp_path, body, offset):
    obj = fixture(monkeypatch, tmp_path, b'abcdefgh')
    assert list(build.local_float_refs(obj, bytes.fromhex(body), [(offset, 6, '_constant')])) == []


@pytest.mark.parametrize('addend', [-1, 1])
def test_out_of_bounds_window_fails(monkeypatch, tmp_path, addend):
    obj = fixture(monkeypatch, tmp_path, b'abcd')
    body = b'\xd9\x05' + struct.pack('<i', addend) + b'\xc3'
    with pytest.raises(ValueError, match='exceeds its data section'):
        list(build.local_float_refs(obj, body, [(2, 6, '_constant')]))


def test_negative_addend_within_section(monkeypatch, tmp_path):
    obj = fixture(monkeypatch, tmp_path, b'abcdefgh', symbol_value=4)
    body = b'\xd9\x05' + struct.pack('<i', -4) + b'\xc3'
    assert list(build.local_float_refs(obj, body, [(2, 6, '_constant')])) == [(2, '_constant', b'abcd')]


def test_each_operand_uses_its_own_array_offset(monkeypatch, tmp_path):
    obj = fixture(monkeypatch, tmp_path, b'abcdefgh')
    body = bytes.fromhex('d90500000000d80d04000000c3')
    assert list(build.local_float_refs(obj, body, [(2, 6, '_constant'), (8, 6, '_constant')])) == [
        (2, '_constant', b'abcd'), (8, '_constant', b'efgh')]


@pytest.mark.parametrize('held,passes', [(b'abcd', True), (b'abce', False), (None, False)])
def test_verifier_compares_referenced_local_window(monkeypatch, tmp_path, capsys, held, passes):
    obj = fixture(monkeypatch, tmp_path, b'----abcd', symbol_value=4)
    body = bytes.fromhex('d90500000000c3')
    retail = bytes.fromhex('d90500204000c3')
    row = {'name': '_body', 'target_rva': '0x1000', 'target_size': '7', 'notes': ''}
    monkeypatch.setattr(build, 'require_row_object', lambda _: obj)
    monkeypatch.setattr(build, 'read_object_symbol_bytes', lambda *args: (body, [(2, 6, '_constant')]))
    def read(rva, size):
        if rva == 0x1000:
            return retail
        assert rva == 0x2000 and size == 4
        if held is None:
            raise ValueError('outside image')
        return held
    monkeypatch.setattr(build, 'read_target_bytes', read)
    if passes:
        build.verify_constant_refs([row])
        assert '1 local readonly loads verified' in capsys.readouterr().out
    else:
        with pytest.raises(SystemExit):
            build.verify_constant_refs([row])
        assert '_constant, but retail 0x00402000' in capsys.readouterr().out
