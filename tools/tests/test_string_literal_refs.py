"""Literal equality includes embedded NULs and the complete terminator."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


@pytest.mark.parametrize('symbol,raw,expected', [
    ('??_C@_07HASH@Default?$AA@', b'Default\0', b'Default\0'),
    ('??_C@_08HASH@Default?5?$AA@', b'Default \0\0\0\0', b'Default \0'),
    ('??_C@_0M@HASH@', b'hello world\0' + b'padding', b'hello world\0'),
    ('??_C@_00HASH@', b'\0\0\0\0', b'\0'),
    ('??_C@_02HASH@', b'a\0\0', b'a\0\0'),
    ('??_C@_03HASH@', b'a\0b\0', b'a\0b\0'),
    ('??_C@_13HASH@', b'a\0\0\0\0\0', b'a\0\0\0'),
    ('??_C@_11HASH@', b'\0\0\0\0', b'\0\0'),
    ('??_C@_1M@HASH@', '%d/%d\0'.encode('utf-16le'), '%d/%d\0'.encode('utf-16le')),
])
def test_encoded_length_preserves_literal_not_padding(symbol, raw, expected):
    assert build.string_literal_bytes(symbol, raw) == expected


@pytest.mark.parametrize('symbol,raw', [
    ('??_C@bad', b'a\0'), ('??_C@_07HASH@', b'Default'),
    ('??_C@_07HASH@', b'Default '), ('??_C@_13HASH@', b'a\0\0x'),
    ('??_C@_12HASH@', b'a\0\0'), ('??_C@_0A@HASH@', b'\0'),
])
def test_malformed_or_truncated_literals_fail(symbol, raw):
    with pytest.raises(ValueError):
        build.string_literal_bytes(symbol, raw)


def check(monkeypatch, tmp_path, source, retail, *, symbol='??_C@_07HASH@', addend=0):
    exe = tmp_path / 'retail.exe'
    exe.write_bytes(retail)
    monkeypatch.setattr(build, 'EXE', exe)
    monkeypatch.setattr(build, 'pe_sections', lambda _: [])
    monkeypatch.setattr(build, 'rva_to_file_offset', lambda pe, rva: 0)
    monkeypatch.setattr(build, 'require_row_object', lambda _: tmp_path / 'one.obj')
    monkeypatch.setattr(build, 'read_target_bytes', lambda *args: struct.pack('<I', 0x402000))
    def read(obj, name, *args):
        return (source, []) if name == symbol else (struct.pack('<i', addend), [(0, 6, symbol)])
    monkeypatch.setattr(build, 'read_object_symbol_bytes', read)
    build.verify_string_refs([{'name': '_body', 'target_rva': '0x1000', 'target_size': '4'}])


def test_same_prefix_with_extra_retail_character_fails(monkeypatch, tmp_path, capsys):
    with pytest.raises(SystemExit):
        check(monkeypatch, tmp_path, b'Default\0', b'Default \0')
    out = capsys.readouterr().out
    assert "source=b'Default\\x00'" in out and "binary=b'Default '" in out


def test_exact_literal_with_unrelated_following_bytes_passes(monkeypatch, tmp_path):
    check(monkeypatch, tmp_path, b'Default\0\0\0', b'Default\0other')


def test_suffix_addend_preserves_terminator(monkeypatch, tmp_path):
    check(monkeypatch, tmp_path, b'Default\0', b'fault\0', addend=2)
    with pytest.raises(SystemExit):
        check(monkeypatch, tmp_path, b'Default\0', b'faulty\0', addend=2)


def test_terminator_suffix_is_an_empty_string(monkeypatch, tmp_path, capsys):
    check(monkeypatch, tmp_path, b'Default\0', b'\0', addend=7)
    assert '0 literals + 1 empty-string refs' in capsys.readouterr().out


@pytest.mark.parametrize('addend', [-1, 8, 100])
def test_addend_outside_literal_fails(monkeypatch, tmp_path, addend):
    with pytest.raises(SystemExit):
        check(monkeypatch, tmp_path, b'Default\0', b'Default\0', addend=addend)


def test_empty_wide_string_checks_both_terminator_bytes(monkeypatch, tmp_path):
    with pytest.raises(SystemExit):
        check(monkeypatch, tmp_path, b'\0\0', b'\0x', symbol='??_C@_11HASH@')
    check(monkeypatch, tmp_path, b'\0\0', b'\0\0', symbol='??_C@_11HASH@')


def test_embedded_null_is_not_the_end_of_literal_verification(monkeypatch, tmp_path):
    with pytest.raises(SystemExit):
        check(monkeypatch, tmp_path, b'a\0b\0', b'a\0c\0', symbol='??_C@_03HASH@')
