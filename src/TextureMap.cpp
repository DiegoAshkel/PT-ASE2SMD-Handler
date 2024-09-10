#include "pch.h"
#include "TextureMap.h"
#include "KeyReader.h"

void TextureMap::Load(KeyReader *reader)
{
	if (!reader)
	{
		return;
	}

	char *pKey = nullptr;

	while (!reader->IsEOF())
	{
		pKey = reader->GetKey();
		if (!pKey)
			continue;

		if (strcmpi(pKey, "*MAP_NAME") == 0)
		{
			std::string str = reader->GetString();
			strncpy_s(Name, str.c_str(), str.length());
		}
		else if (strcmpi(pKey, "*MAP_CLASS") == 0)
		{
			std::string str = reader->GetString();
			strncpy_s(Class, str.c_str(), str.length());
		}
		else if (strcmpi(pKey, "*MAP_SUBNO") == 0)
		{
			SubNo = reader->GetInteger();
		}
		else if (strcmpi(pKey, "*MAP_AMOUNT") == 0)
		{
			Amount = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*BITMAP") == 0)
		{
			std::string str = reader->GetString();
			strncpy_s(FilePath, str.c_str(), str.length());
		}
		else if (strcmpi(pKey, "*MAP_TYPE") == 0)
		{
			std::string str = reader->GetWord();

			SetMapping(str);
		}
		else if (strcmpi(pKey, "*UVW_U_OFFSET") == 0)
		{
			UVW.U_Offset = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_V_OFFSET") == 0)
		{
			UVW.V_Offset = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_U_TILING") == 0)
		{
			UVW.U_Tiling = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_V_TILING") == 0)
		{
			UVW.V_Tiling = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_ANGLE") == 0)
		{
			UVW.Angle = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_BLUR") == 0)
		{
			UVW.Blur = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_BLUR_OFFSET") == 0)
		{
			UVW.BlurOffset = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_NOUSE_AMT") == 0)
		{
			UVW.NoiseAmount = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_NOISE_SIZE") == 0)
		{
			UVW.NoiseSize = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*UVW_NOISE_LEVEL") == 0)
		{
			UVW.NoiseLevel = reader->GetInteger();
		}
		else if (strcmpi(pKey, "*UVW_NOISE_PHASE") == 0)
		{
			UVW.NoisePhase = reader->GetFloat();
		}
		else if (strcmpi(pKey, "*BITMAP_FILTER") == 0)
		{
			std::string str = reader->GetWord();

			SetFilter(str);
		}

		delete[] pKey;
		pKey = nullptr;
	}
}

void TextureMap::SetFilter(std::string &str)
{
	Filter = TEXTUREFILTER_NONE;

	if (strcmpi(str.c_str(), "Pyramidal") == 0)
	{
		Filter = TEXTUREFILTER_PYRAMIDAL;
	}
	else if (strcmpi(str.c_str(), "Sat") == 0)
	{
		Filter = TEXTUREFILTER_SAT;
	}
}

void TextureMap::SetMapping(std::string &str)
{
	Type = MAP_UNKNOWN;

	if (strcmpi(str.c_str(), "Screen") == 0)
	{
		Type = MAP_SCREEN;
	}
	else if (strcmpi(str.c_str(), "Cylindrical") == 0)
	{
		Type = MAP_CYLINDRICAL;
	}
	else if (strcmpi(str.c_str(), "Spherical") == 0)
	{
		Type = MAP_SPHERICAL;
	}
	else if (strcmpi(str.c_str(), "Box") == 0)
	{
		Type = MAP_BOX;
	}
	else if (strcmpi(str.c_str(), "ShrinkWrap") == 0)
	{
		Type = MAP_SHRINKWRAP;
	}
	else if (strcmpi(str.c_str(), "UV-Mapping") == 0)
	{
		Type = MAP_UV;
	}
}

void TextureMap::SetMapType(const char *pKey)
{
	Identifier = TEXTUREMAP_UNKNOWN;

	if (strcmpi(pKey, "*MAP_BUMP") == 0)
	{
		Identifier = TEXTUREMAP_BUMP;
	}
	else if (strcmpi(pKey, "*MAP_DIFFUSE") == 0)
	{
		Identifier = TEXTUREMAP_DIFFUSE;
	}
	else if (strcmpi(pKey, "*MAP_SPECULAR") == 0)
	{
		Identifier = TEXTUREMAP_SPECULAR;
	}
	else if (strcmpi(pKey, "*MAP_OPACITY") == 0)
	{
		Identifier = TEXTUREMAP_OPACITY;
	}
	else if (strcmpi(pKey, "*MAP_REFLECT") == 0)
	{
		Identifier = TEXTUREMAP_REFLECT;
	}
	else if (strcmpi(pKey, "*MAP_REFRACT") == 0)
	{
		Identifier = TEXTUREMAP_REFRACT;
	}
	else if (strcmpi(pKey, "*MAP_ENVIRONMENT") == 0)
	{
		Identifier = TEXTUREMAP_ENVIRONMENT;
	}
	else if (strcmpi(pKey, "*MAP_DISPLACEMENT") == 0)
	{
		Identifier = TEXTUREMAP_DISPLACEMENT;
	}
	else if (strcmpi(pKey, "*MAP_LIGHT") == 0)
	{
		Identifier = TEXTUREMAP_LIGHT;
	}
	else if (strcmpi(pKey, "*MAP_FOG") == 0)
	{
		Identifier = TEXTUREMAP_FOG;
	}
	else if (strcmpi(pKey, "*MAP_SELFILLUM") == 0)
	{
		Identifier = TEXTUREMAP_SELFILLUM;
	}
}
