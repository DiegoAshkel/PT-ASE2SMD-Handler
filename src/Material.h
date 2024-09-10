#pragma once

#include "pch.h"
#include "SubMaterial.h"

#include <string>
#include <vector>

class KeyReader;

/// *MATERIAL
/// Início da definição de um material específico.
class Material : public SubMaterial
{
public:
	Material();
	virtual ~Material();

	void Save(Shared::BinaryWriter &bw) override;

	void Add(const SubMaterial &material);

protected:
	void SetKey(const char *lpKey, KeyReader *reader) override;

public:
	/// *NUMSUBMTLS
	/// Especifica o número de submateriais contidos em um material.
	int SubMaterialCount;

	/// Lista de sub-materiais;
	std::vector<SubMaterial> Submaterials;
};

/// *MATERIAL_LIST
/// Início da lista de materiais na cena.
class MaterialList
{
public:
	void Save(Shared::BinaryWriter &bw);
	void Load(KeyReader *reader);

	void Add(const Material &material);

public:
	/// *MATERIAL_COUNT
	/// Número total de materiais.
	int Count;

	/// *MATERIAL
	/// Materiais disponíveis na cena.
	std::vector<Material> Materials;
};
