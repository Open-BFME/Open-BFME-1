"""Fail closed when archive framing cannot justify complete member bytes."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import coffar


def member(name, body):
    header = (name.ljust(16) + '0'.ljust(12) + '0'.ljust(6) + '0'.ljust(6)
              + '100644'.ljust(8) + str(len(body)).ljust(10) + '`\n').encode()
    return header + body + (b'\n' if len(body) & 1 else b'')


def test_valid_short_long_and_linker_members_parse_identically():
    payload = (b'!<arch>\n' + member('/', b'index')
               + member('//', b'long\\name.obj\0')
               + member('/0', b'odd') + member('short.obj/', b'even'))
    assert coffar.read_archive_bytes(payload) == [('long\\name.obj', b'odd'),
                                                 ('short.obj', b'even')]


@pytest.mark.parametrize('size', [b'-1        ', b'-60       ', b'+1        ', b'1x        ',
                                  b'          ', b'1\t        '])
def test_rejects_negative_or_malformed_size(size):
    data = bytearray(b'!<arch>\n' + member('native.obj/', b'even'))
    data[56:66] = size
    with pytest.raises(ValueError, match='member size'):
        coffar.read_archive_bytes(data)


@pytest.mark.parametrize('cut', [1, 30, 59])
def test_rejects_truncated_header(cut):
    with pytest.raises(ValueError, match='header'):
        coffar.read_archive_bytes(b'!<arch>\n' + member('native.obj/', b'even')[:cut])


def test_rejects_truncated_body():
    with pytest.raises(ValueError, match='body'):
        coffar.read_archive_bytes((b'!<arch>\n' + member('native.obj/', b'even'))[:-1])


def test_rejects_missing_required_odd_padding():
    with pytest.raises(ValueError, match='padding'):
        coffar.read_archive_bytes((b'!<arch>\n' + member('native.obj/', b'odd'))[:-1])


def test_rejects_invalid_member_terminator():
    data = bytearray(b'!<arch>\n' + member('native.obj/', b'even'))
    data[66:68] = b'xx'
    with pytest.raises(ValueError, match='terminator'):
        coffar.read_archive_bytes(data)


@pytest.mark.parametrize('reference', ['/20', '/-1', '/x', '/+0'])
def test_rejects_invalid_or_out_of_range_long_name(reference):
    with pytest.raises(ValueError, match='long-name'):
        coffar.read_archive_bytes(b'!<arch>\n' + member('//', b'long.obj\0')
                                 + member(reference, b'even'))


def test_rejects_unterminated_long_name():
    with pytest.raises(ValueError, match='unterminated'):
        coffar.read_archive_bytes(b'!<arch>\n' + member('//', b'long.obj')
                                 + member('/0', b'even'))


def test_rejects_long_name_without_name_table():
    with pytest.raises(ValueError, match='out of range'):
        coffar.read_archive_bytes(b'!<arch>\n' + member('/0', b'even'))
