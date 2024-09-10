#include "Material.h"
#include "KeyReader.h"

#include <iostream>
#include <fstream>

Material::Material()
	: SubMaterial(), Submaterials()
{
}

Material::~Material()
{
}

void Material::Save(Shared::BinaryWriter &bw)
{
	SubMaterial::Save(bw);

	size_t offset = bw.GetOffset();

	bw.InsertAt(offset, SubMaterialCount);
	offset = bw.GetOffset();

	for (auto &sub : Submaterials)
	{
		sub.Save(bw);
	}
}

void Material::SetKey(const char *lpKey, KeyReader *reader)
{
	SubMaterial::SetKey(lpKey, reader);

	if (strcmpi(lpKey, "*NUMSUBMTLS") == 0)
	{
		SubMaterialCount = reader->GetInteger();
	}
	else if (strcmpi(lpKey, "*SUBMATERIAL") == 0)
	{
		if (Submaterials.size() < SubMaterialCount)
		{
			SubMaterial material;
			material.Index = reader->GetInteger();

			material.Load(reader->GetBlock());

			Add(material);
		}
	}
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
	size_t length = sizeof(int);
	bw.Reserve(length);

	size_t offset = bw.GetOffset();

	bw.InsertAt(offset, Count);
	offset = bw.GetOffset();

	for (auto &material : Materials)
	{
		material.Save(bw);
	}
}

void MaterialList::Load(KeyReader *reader)
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

		if (strcmpi(pKey, "*MATERIAL_COUNT") == 0)
		{
			Count = reader->GetInteger();
		}
		else if (strcmpi(pKey, "*MATERIAL") == 0)
		{
			if (Materials.size() < Count)
			{
				Material material;
				material.Index = reader->GetInteger();

				material.Load(reader->GetBlock());

				Add(material);
			}
		}

		delete[] pKey;
		pKey = nullptr;
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
