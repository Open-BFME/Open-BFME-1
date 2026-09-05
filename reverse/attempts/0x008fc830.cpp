// ?clear@W3DRadarResetSurface@@QAEXI@Z
// partial score=0.65 date=2026-09-05

void W3DRadarResetSurface::clear( UnsignedInt color )
{
	if (m_surface)
	{
		SurfaceClass::SurfaceDescription description;
		reinterpret_cast<SurfaceClass *>(this)->Get_Description(description);
		UnsignedInt size = PixelSize(description) * description.Width;
		_ReadWriteBarrier();

		W3DRadarResetLockedRect locked;
		::memset(&locked, 0, sizeof(locked));
		W3DRadarResetErrorCode(m_surface->lockRect(&locked, NULL, 0));

		UnsignedInt fill = static_cast<UnsignedByte>(color) ? 0xff : 0;
		unsigned char *memory = static_cast<unsigned char *>(locked.bits);
		UnsignedInt i;
		if (size == 0 && (description.Format == static_cast<WW3DFormat>(0x31545844) ||
			description.Format == static_cast<WW3DFormat>(0x32545844) ||
			description.Format == static_cast<WW3DFormat>(0x33545844) ||
			description.Format == static_cast<WW3DFormat>(0x34545844) ||
			description.Format == static_cast<WW3DFormat>(0x35545844)))
		{
			size = locked.pitch;
			if (static_cast<UnsignedByte>(color))
			{
				unsigned char pattern[8];
				Int copy_count = size >> 3;
				fill |= 0xff;
				pattern[0] = static_cast<unsigned char>(fill);
				pattern[1] = 0xfe;
				pattern[2] = static_cast<unsigned char>(fill);
				pattern[3] = static_cast<unsigned char>(fill);
				pattern[4] = 0x55;
				pattern[5] = 0x55;
				pattern[6] = 0x55;
				pattern[7] = 0x55;
				for (i = description.Height >> 2; i > 0; --i)
				{
					if (copy_count > 0)
					{
						*reinterpret_cast<UnsignedInt *>(memory) =
							*reinterpret_cast<UnsignedInt *>(pattern);
						*reinterpret_cast<UnsignedInt *>(memory + 4) =
							*reinterpret_cast<UnsignedInt *>(pattern + 4);
						::memcpy(memory + 8, memory, copy_count * 8 - 5);
					}
					memory += locked.pitch;
				}
				goto unlock;
			}
		}
		for (i = description.Height; i > 0; --i)
		{
			::memset(memory, fill, size);
			memory += locked.pitch;
		}

	unlock:
		W3DRadarResetErrorCode(m_surface->unlockRect());
	}
}
