#include "Material.h"
#include "KeyReader.h"

#include <iostream>
#include <fstream>
#include "SubMaterial.h"

SubMaterial::SubMaterial()
	: TextureMaps()
{
}

SubMaterial::~SubMaterial()
{
}

void SubMaterial::Save(Shared::BinaryWriter &bw)
{
	size_t length = sizeof(SubMaterial) + (sizeof(TextureMap) * TextureMaps.size());
	bw.Reserve(length);

	size_t offset = bw.GetOffset();

	bw.InsertAt(offset, Index);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Name);
	offset += sizeof(Name);

	bw.InsertAt(offset, Class);
	offset += sizeof(Class);

	bw.InsertAt(offset, Ambient.R);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Ambient.G);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Ambient.B);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Diffuse.R);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Diffuse.G);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Diffuse.B);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Specular.R);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Specular.G);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Specular.B);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Shine);
	offset = bw.GetOffset();

	bw.InsertAt(offset, ShineStrength);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Transparency);
	offset = bw.GetOffset();

	bw.InsertAt(offset, WireSize);
	offset = bw.GetOffset();

	bw.InsertAt(offset, static_cast<int>(Shading));
	offset = bw.GetOffset();

	bw.InsertAt(offset, SelfIllum);
	offset = bw.GetOffset();

	bw.InsertAt(offset, static_cast<int>(FallOff));
	offset = bw.GetOffset();

	bw.InsertAt(offset, XPFallOff);
	offset = bw.GetOffset();

	bw.InsertAt(offset, static_cast<int>(XpType));
	offset = bw.GetOffset();

	bw.InsertAt(offset, TextureMaps.size());
	offset = bw.GetOffset();

	for (auto &texture : TextureMaps)
	{
		bw.InsertAt(offset, static_cast<int>(texture.Identifier));
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.Name);
		offset += sizeof(texture.Name);

		bw.InsertAt(offset, texture.Class);
		offset += sizeof(texture.Class);

		bw.InsertAt(offset, texture.SubNo);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.Amount);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.FilePath);
		offset += sizeof(texture.FilePath);

		bw.InsertAt(offset, static_cast<int>(texture.Type));
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.U_Offset);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.V_Offset);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.U_Tiling);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.V_Tiling);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.Angle);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.Blur);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.BlurOffset);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.NoiseAmount);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.NoiseSize);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.NoiseLevel);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.UVW.NoisePhase);
		offset = bw.GetOffset();

		bw.InsertAt(offset, texture.Amount);
		offset = bw.GetOffset();

		bw.InsertAt(offset, static_cast<int>(texture.Filter));
		offset = bw.GetOffset();
	}
}

void SubMaterial::Load(KeyReader *reader)
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

		SetKey(pKey, reader);

		delete[] pKey;
		pKey = nullptr;
	}
}

void SubMaterial::SetKey(const char *lpKey, KeyReader *reader)
{
	if (strcmpi(lpKey, "*MATERIAL_NAME") == 0)
	{
		std::string str = reader->GetString();
		strncpy_s(Name, str.c_str(), str.length());
	}
	else if (strcmpi(lpKey, "*MATERIAL_CLASS") == 0)
	{
		std::string str = reader->GetString();
		strncpy_s(Class, str.c_str(), str.length());
	}
	else if (strcmpi(lpKey, "*MATERIAL_AMBIENT") == 0)
	{
		Ambient.R = reader->GetFloat();
		Ambient.G = reader->GetFloat();
		Ambient.B = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_DIFFUSE") == 0)
	{
		Diffuse.R = reader->GetFloat();
		Diffuse.G = reader->GetFloat();
		Diffuse.B = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_SPECULAR") == 0)
	{
		Specular.R = reader->GetFloat();
		Specular.G = reader->GetFloat();
		Specular.B = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_SHINE") == 0)
	{
		Shine = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_SHINESTRENGTH") == 0)
	{
		ShineStrength = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_TRANSPARENCY") == 0)
	{
		Transparency = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_WIRESIZE") == 0)
	{
		WireSize = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_SHADING") == 0)
	{
		std::string str = reader->GetWord();

		Shading = GetShading(str);
	}
	else if (strcmpi(lpKey, "*MATERIAL_SELFILLUM") == 0)
	{
		SelfIllum = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_FALLOFF") == 0)
	{
		std::string str = reader->GetWord();

		FallOff = GetFallOff(str);
	}
	else if (strcmpi(lpKey, "*MATERIAL_XP_FALLOFF") == 0)
	{
		XPFallOff = reader->GetFloat();
	}
	else if (strcmpi(lpKey, "*MATERIAL_XP_TYPE") == 0)
	{
		std::string str = reader->GetWord();

		XpType = GetXpType(str);
	}
	else if (strcmpi(lpKey, "*MAP_BUMP") == 0 ||
			 strcmpi(lpKey, "*MAP_DIFFUSE") == 0 ||
			 strcmpi(lpKey, "*MAP_SPECULAR") == 0 ||
			 strcmpi(lpKey, "*MAP_OPACITY") == 0 ||
			 strcmpi(lpKey, "*MAP_REFLECT") == 0 ||
			 strcmpi(lpKey, "*MAP_REFRACT") == 0 ||
			 strcmpi(lpKey, "*MAP_ENVIRONMENT") == 0 ||
			 strcmpi(lpKey, "*MAP_DISPLACEMENT") == 0 ||
			 strcmpi(lpKey, "*MAP_LIGHT") == 0 ||
			 strcmpi(lpKey, "*MAP_FOG") == 0 ||
			 strcmpi(lpKey, "*MAP_SELFILLUM") == 0)
	{
		TextureMap texture{};
		memset(&texture, 0, sizeof(TextureMap));

		texture.SetMapType(lpKey);

		if (texture.Identifier != TEXTUREMAP_UNKNOWN)
		{
			texture.Load(reader->GetBlock());

			Add(texture);
		}
	}
}

void SubMaterial::Add(const TextureMap &texture)
{
	for (auto &tex : TextureMaps)
	{
		if (tex.SubNo == texture.SubNo)
		{
			return;
		}
	}

	TextureMaps.push_back(texture);
}

FallOffXpType SubMaterial::GetXpType(std::string &str)
{
	FallOffXpType type = XPTYPE_UNKNOWN;

	if (strcmpi(str.c_str(), "Filter") == 0)
	{
		type = XPTYPE_FILTER;
	}
	else if (strcmpi(str.c_str(), "Reflect") == 0)
	{
		type = XPTYPE_REFLECT;
	}
	else if (strcmpi(str.c_str(), "Refract") == 0)
	{
		type = XPTYPE_REFRACT;
	}
	else if (strcmpi(str.c_str(), "Shadow") == 0)
	{
		type = XPTYPE_SHADOW;
	}

	return type;
}

FallOffType SubMaterial::GetFallOff(std::string &str)
{
	FallOffType type = FALLOFF_UNKNOWN;

	if (strcmpi(str.c_str(), "In") == 0)
	{
		type = FALLOFF_IN;
	}
	else if (strcmpi(str.c_str(), "Out") == 0)
	{
		type = FALLOFF_OUT;
	}
	else if (strcmpi(str.c_str(), "Perpendicular") == 0)
	{
		type = FALLOFF_PERPENDICULAR;
	}
	else if (strcmpi(str.c_str(), "Parallel") == 0)
	{
		type = FALLOFF_PARALLEL;
	}
	else if (strcmpi(str.c_str(), "Towards") == 0)
	{
		type = FALLOFF_TOWARDS;
	}
	else if (strcmpi(str.c_str(), "Away") == 0)
	{
		type = FALLOFF_AWAY;
	}
	else if (strcmpi(str.c_str(), "Fresnel") == 0)
	{
		type = FALLOFF_FRESNEL;
	}

	return type;
}

ShadingType SubMaterial::GetShading(std::string &str)
{
	ShadingType type = SHADING_UNKNOWN;

	if (strcmpi(str.c_str(), "Flat") == 0)
	{
		type = SHADING_FLAT;
	}
	else if (strcmpi(str.c_str(), "Blinn") == 0)
	{
		type = SHADING_BLINN;
	}
	else if (strcmpi(str.c_str(), "Phong") == 0)
	{
		type = SHADING_PHONG;
	}
	else if (strcmpi(str.c_str(), "Metal") == 0)
	{
		type = SHADING_METAL;
	}
	else if (strcmpi(str.c_str(), "Oren-Nayar-Blinn") == 0)
	{
		type = SHADING_ORENNAYARBLINN;
	}
	else if (strcmpi(str.c_str(), "Strauss") == 0)
	{
		type = SHADING_STRAUSS;
	}
	else if (strcmpi(str.c_str(), "Anisotropic") == 0)
	{
		type = SHADING_ANISOTROPIC;
	}
	else if (strcmpi(str.c_str(), "MultiLayer") == 0)
	{
		type = SHADING_MULTILAYER;
	}
	else if (strcmpi(str.c_str(), "Lambert") == 0)
	{
		type = SHADING_LAMBERT;
	}
	else if (strcmpi(str.c_str(), "Translucent") == 0)
	{
		type = SHADING_TRANSLUCENT;
	}

	return type;
}
