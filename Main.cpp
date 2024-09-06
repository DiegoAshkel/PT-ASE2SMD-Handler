#include <iostream>
#include <string>
#include <vector>

//#include <Windows.h>

#include "ASE.h"

int main(int argc, char *argv[])
{
	ASE_RawData ase_rd;
	ase_rd.Version = 200;
	strcpy_s(ase_rd.Comment, "AsciiExport Version  2.00 - Thu May 29 15:00:18 2003");
	strcpy_s(ase_rd.Description.FileName, "Hopy.max");
	ase_rd.Description.FirstFrame = 0;
	ase_rd.Description.LastFrame = 311;
	ase_rd.Description.FrameSpeed = 30;
	ase_rd.Description.TicksPerFrame = 160;
	ase_rd.Description.BackgroundColor = {0.000f, 0.000f, 0.000f};
	ase_rd.Description.AmbientColor = {0.043f, 0.043f, 0.043f};

	Material mat;
	mat.Index = 0;
	strcpy_s(mat.Name, "Material #25");
	strcpy_s(mat.Class, "Standard");
	mat.Ambient = {0.179f, 0.065f, 0.065f};
	mat.Diffuse = {0.537f, 0.196f, 0.196f};
	mat.Specular = {0.900f, 0.900f, 0.900f};
	mat.Shine = 0.250f;
	mat.ShineStrength = 0.050f;
	mat.Transparency = 0.000f;
	mat.WireSize = 1.000f;
	mat.Shading = SHADING_BLINN;
	mat.SelfIllum = 0.000f;
	mat.FallOff = FALLOFF_IN;
	mat.XPFallOff = 0.000f;
	mat.FallOffTransition = XPTYPE_FILTER;
	mat.SubMaterialCount = 0;
	mat.Submaterials.clear();

	TextureMap texture;
	texture.Identifier = TEXTUREMAP_DIFFUSE;
	strcpy_s(texture.Name, "Map #0");
	strcpy_s(texture.Class, "Bitmap");
	texture.SubNo = 1;
	texture.Amount = 1.000f;
	strcpy_s(texture.FilePath, ".\\monhopy\\Monhobi.bmp");
	texture.Type = MAP_SCREEN;
	texture.UVW.U_Offset = 0.000f;
	texture.UVW.V_Offset = 0.000f;
	texture.UVW.U_Tiling = 1.000f;
	texture.UVW.V_Tiling = 1.000f;
	texture.UVW.Angle = 0.000f;
	texture.UVW.Blur = 1.000f;
	texture.UVW.BlurOffset = 0.000f;
	texture.UVW.NoiseAmount = 1.000f;
	texture.UVW.NoiseSize = 1.000f;
	texture.UVW.NoiseLevel = 1;
	texture.UVW.NoisePhase = 0.000f;
	texture.Filter = TEXTUREFILTER_PYRAMIDAL;

	mat.Add(texture);

	ase_rd.Materials.Count = 1;
	ase_rd.Materials.Add(mat);

	ase_rd.Save("data.ase.dat");

	system("pause");

	return 0;
}

// struct Material
// {
// 	int Index;
// 	char Name[64];
// 	char FileName[256];

// 	Material()
// 	{
// 		Index = 0;
// 		memset(&Name, 0, sizeof(Name));
// 		memset(&FileName, 0, sizeof(FileName));
// 	}
// };

// struct MaterialList
// {
// 	int Count;
// 	std::vector<Material> Materials;

// 	bool Add(const Material &mat)
// 	{
// 		for (auto it : Materials)
// 		{
// 			if (it.Index == mat.Index)
// 				return false;
// 		}

// 		Materials.push_back(mat);

// 		return true;
// 	}

// 	void Save(const char *fileName)
// 	{
// 		std::string file = fileName;
// 		file += ".dat";

// 		std::cout << "Process: " << file << std::endl;

// 		HANDLE hFile = CreateFileA(
// 			file.c_str(),		   // name of the file to open
// 			GENERIC_WRITE,		   // open for writing
// 			0,					   // do not share
// 			NULL,				   // default security
// 			CREATE_ALWAYS,		   // create new file if not exists, open always
// 			FILE_ATTRIBUTE_NORMAL, // normal file
// 			NULL);				   // no template

// 		if (hFile == INVALID_HANDLE_VALUE)
// 		{
// 			std::cout << "Terminal failure: Unable to open file \"";
// 			std::cout << fileName << "\" for write." << std::endl;

// 			return;
// 		}

// 		DWORD dwBytesWritten = 0;
// 		DWORD dwBytesToWrite = sizeof(Material) * Count;
// 		dwBytesToWrite += sizeof(Count);

// 		Shared::BinaryWriter bw(dwBytesToWrite);

// 		bw << Count;

// 		size_t offset = bw.GetOffset();

// 		for (auto &mat : Materials)
// 		{
// 			bw.InsertAt(offset, mat.Index);
// 			offset = bw.GetOffset();

// 			bw.InsertAt(offset, mat.Name);
// 			offset += sizeof(mat.Name);

// 			bw.InsertAt(offset, mat.FileName);
// 			offset += sizeof(mat.FileName);
// 		}

// 		std::cout << "dwBytesToWrite: " << dwBytesToWrite << std::endl;

// 		BOOL bErrorFlag = WriteFile(
// 			hFile,			 // open file handle
// 			bw.Get(),		 // start of data to write
// 			dwBytesToWrite,	 // number of bytes to write
// 			&dwBytesWritten, // number of bytes that were written
// 			NULL);			 // no overlapped structure

// 		if (FALSE == bErrorFlag)
// 		{
// 			std::cout << "Terminal failure: Unable to write to file." << std::endl;
// 		}

// 		if (dwBytesWritten != dwBytesToWrite)
// 		{
// 			std::cout << "Error: dwBytesWritten != dwBytesToWrite." << std::endl;
// 		}
// 		else
// 		{
// 			std::cout << "Wrote " << dwBytesWritten << " bytes to ";
// 			std::cout << file << " successfully." << std::endl;
// 		}

// 		CloseHandle(hFile);
// 	}
// };

// int main(int argc, char *argv[])
// {
// 	std::cout << "Hello Fuckers!" << std::endl;

// 	MaterialList matList;
// 	std::string name;
// 	std::string fileName;
// 	name.reserve(64);
// 	fileName.reserve(256);

// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		Material mat;
// 		mat.Index = i;

// 		name.clear();
// 		name += "Material_";
// 		name += std::to_string(i);
// 		strncpy_s(mat.Name, name.c_str(), name.length());

// 		fileName.clear();
// 		fileName += name;
// 		fileName += "\\Texture.exe";
// 		strncpy_s(mat.FileName, fileName.c_str(), fileName.length());

// 		matList.Add(mat);
// 	}

// 	matList.Count = static_cast<int>(matList.Materials.size());

// 	matList.Save("MaterialList");

// 	system("pause");

// 	return 0;
// }
