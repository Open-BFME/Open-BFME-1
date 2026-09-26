// cl: /DNDEBUG /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// Owning texture-handle destructor, RVA 0x0005CC00, full 12 bytes.
// MaterialCollector's texture-vector teardown passes the checked jump route
// 0x00030652 -> 0x0005CC00 to the array destructor iterator. The body loads
// the one-pointer handle, returns for null, or tail-calls the independently
// matched TextureClass::Release_Ref at 0x009EB7A0. INT3 begins at 0x0005CC0C.
class TextureClass {
public:
    void Release_Ref();
};
class BfmeHandleCX {
public:
    ~BfmeHandleCX();
private:
    TextureClass *p;
};
BfmeHandleCX::~BfmeHandleCX()
{
    if (p) p->Release_Ref();
}
