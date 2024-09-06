#include "ASE.h"

#include <iostream>
#include <fstream>

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

	bw.InsertAt(offset, static_cast<int>(FallOffTransition));
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

void Material::Save(Shared::BinaryWriter &bw)
{
	size_t length = sizeof(Material) + (sizeof(TextureMap) * TextureMaps.size());
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

	bw.InsertAt(offset, static_cast<int>(FallOffTransition));
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

	bw.InsertAt(offset, SubMaterialCount);
	offset = bw.GetOffset();

	for (auto &sub : Submaterials)
	{
		sub.Save(bw);
	}
}

void Material::Add(const TextureMap &texture)
{
	for (auto &tex : TextureMaps)
	{
		if (tex.SubNo == tex.SubNo)
		{
			return;
		}
	}

	TextureMaps.push_back(texture);
}

void Material::Add(const SubMaterial &material)
{
	for (auto &mat : Submaterials)
	{
		if (mat.Index == material.Index)
		{
			return;
		}
	}

	Submaterials.push_back(material);
}

void MaterialList::Save(Shared::BinaryWriter &bw)
{
	size_t length = sizeof(MaterialList);
	bw.Reserve(length);

	size_t offset = bw.GetOffset();

	bw.InsertAt(offset, Count);
	offset = bw.GetOffset();

	for (auto &material : Materials)
	{
		material.Save(bw);
	}
}

void MaterialList::Add(const Material &material)
{
	for (auto &mat : Materials)
	{
		if (mat.Index == material.Index)
		{
			return;
		}
	}

	Materials.push_back(material);
}

void ASE_RawData::Save(const std::string &fileName)
{
	size_t length = sizeof(Version) + sizeof(Comment) + sizeof(Description);
	Shared::BinaryWriter bw(length);

	size_t offset = 0ull;

	bw.InsertAt(offset, Version);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Comment);
	offset += sizeof(Comment);

	bw.InsertAt(offset, Description.FileName);
	offset += sizeof(Description.FileName);

	bw.InsertAt(offset, Description.FirstFrame);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Description.LastFrame);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Description.FrameSpeed);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Description.TicksPerFrame);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Description.BackgroundColor.R);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Description.BackgroundColor.G);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Description.BackgroundColor.B);
	offset = bw.GetOffset();

	bw.InsertAt(offset, Description.AmbientColor.R);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Description.AmbientColor.G);
	offset = bw.GetOffset();
	bw.InsertAt(offset, Description.AmbientColor.B);
	offset = bw.GetOffset();

	Materials.Save(bw);

	std::ofstream out(fileName, std::ios::binary | std::ios::out);
	if (out.is_open())
	{
		std::cout << fileName << " is open!" << std::endl;
		std::cout << "Starting to write: " << bw.GetSize() << " Bytes!" << std::endl;

		out.write((const char *)bw.Get(), bw.GetSize());

		out.flush();
		out.close();
	}
}
