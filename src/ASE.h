#pragma once

#include "TextureMap.h"
#include "Material.h"

class KeyReader;

/// *SCENE
/// Início da descrição geral da cena.
struct Scene
{
	/// *SCENE_FILENAME
	/// Nome do arquivo de origem da cena.
	char FileName[64];

	/// *SCENE_FIRSTFRAME
	/// Primeiro quadro da animação.
	int FirstFrame;

	/// *SCENE_LASTFRAME
	/// Último quadro da animação.
	int LastFrame;

	/// *SCENE_FRAMESPEED
	/// Velocidade dos quadros por segundo.
	int FrameSpeed;

	/// *SCENE_TICKSPERFRAME
	/// Ticks por quadro, usado para sincronização.
	int TicksPerFrame;

	/// *SCENE_BACKGROUND_STATIC
	/// Cor de fundo estática da cena (RGB).
	RGB BackgroundColor;

	/// *SCENE_AMBIENT_STATIC
	/// Cor ambiente estática da cena (RGB).
	RGB AmbientColor;
};

class ASE_RawData
{
public:
	ASE_RawData() = default;
	virtual ~ASE_RawData() = default;

	void Save(const std::string &fileName);
	void Load(const std::string &fileName);

public:
	///  Versão do formato ASE. Indica que o arquivo está no formato ASCII Export do 3ds Max.
	int Version; // *3DSMAX_ASCIIEXPORT

	/// Podem ser usados para documentar detalhes específicos da cena, instruções para outros usuários, ou informações de contexto que podem ser úteis no futuro.
	char Comment[256]; // *COMMENT

	/// Descrição das propriedades da cena.
	Scene Description; // *SCENE

	/// Lista de materiais presentes na cena.
	MaterialList Materials; // *MATERIAL_LIST
};
