#include "ASE.h"
#include "KeyReader.h"

#include <iostream>
#include <fstream>

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

	std::ofstream out(fileName, std::ios::binary);
	if (out.is_open())
	{
		out.write((const char *)bw.Get(), bw.GetSize());

		out.flush();
		out.close();
	}
}

void ASE_RawData::Load(const std::string &fileName)
{
	std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
	if (extension != "ase" &&
		extension != "ASE")
	{
		return;
	}

	KeyReader reader(fileName);

	char *pKey = nullptr;

	bool exiting = false;

	while (!reader.IsEOF() && !exiting)
	{
		pKey = reader.GetKey();

		if (!pKey)
			continue;

		if (strcmpi(pKey, "*3DSMAX_ASCIIEXPORT") == 0)
		{
			Version = reader.GetInteger();
		}
		else if (strcmpi(pKey, "*COMMENT") == 0)
		{
			std::string str = reader.GetString();
			strncpy_s(Comment, str.c_str(), str.length());
		}
		/// Scene description
		else if (strcmpi(pKey, "*SCENE_FILENAME") == 0)
		{
			std::string str = reader.GetString();
			strncpy_s(Description.FileName, str.c_str(), str.length());
		}
		else if (strcmpi(pKey, "*SCENE_FIRSTFRAME") == 0)
		{
			Description.FirstFrame = reader.GetInteger();
		}
		else if (strcmpi(pKey, "*SCENE_LASTFRAME") == 0)
		{
			Description.LastFrame = reader.GetInteger();
		}
		else if (strcmpi(pKey, "*SCENE_FRAMESPEED") == 0)
		{
			Description.FrameSpeed = reader.GetInteger();
		}
		else if (strcmpi(pKey, "*SCENE_FRAMESPEED") == 0)
		{
			Description.FrameSpeed = reader.GetInteger();
		}
		else if (strcmpi(pKey, "*SCENE_TICKSPERFRAME") == 0)
		{
			Description.TicksPerFrame = reader.GetInteger();
		}
		else if (strcmpi(pKey, "*SCENE_BACKGROUND_STATIC") == 0)
		{
			Description.BackgroundColor.R = reader.GetFloat();
			Description.BackgroundColor.G = reader.GetFloat();
			Description.BackgroundColor.B = reader.GetFloat();
		}
		else if (strcmpi(pKey, "*SCENE_AMBIENT_STATIC") == 0)
		{
			Description.AmbientColor.R = reader.GetFloat();
			Description.AmbientColor.G = reader.GetFloat();
			Description.AmbientColor.B = reader.GetFloat();
		}
		/// Materials
		else if (strcmpi(pKey, "*MATERIAL_LIST") == 0)
		{
			Materials.Load(reader.GetBlock());
		}
		else
			// Test
			std::cout << pKey << std::endl;

		delete[] pKey;
		pKey = nullptr;
	}
}
