#pragma once

#include <string>
#include <vector>

class KeyReader;

struct UVWSettings
{
	/// *UVW_U_OFFSET e *UVW_V_OFFSET
	/// Deslocamentos UVW, que definem a posição da textura em relação à superfície.
	float U_Offset, V_Offset;

	/// *UVW_U_TILING  e *UVW_V_TILING
	/// Fatores de repetição da textura em ambos os eixos UVW.
	float U_Tiling, V_Tiling;

	/// *UVW_ANGLE
	/// Ángulo de rotação da textura. Um valor de 0.0000 indica que a textura não está rotacionada.
	float Angle;

	/// *UVW_BLUR
	/// Desfoque da textura. Um valor de 1.0000 indica o nível total de desfoque aplicado à textura.
	float Blur;

	/// *UVW_BLUR_OFFSET
	/// Deslocamento do desfoque. Um valor de 0.0000 indica que não há deslocamento aplicado ao desfoque.
	float BlurOffset;

	/// *UVW_NOUSE_AMT
	/// Quantidade de ruído aplicado ao mapeamento UVW. Um valor de 1.0000 indica que o máximo de ruído está sendo aplicado.
	float NoiseAmount;

	/// *UVW_NOISE_SIZE
	/// Tamanho do ruído aplicado ao mapeamento UVW. Um valor de 1.0000 indica um tamanho padrão.
	float NoiseSize;

	/// *UVW_NOISE_LEVEL
	/// Nível de ruído. Um valor de 1 indica que o ruído é aplicado em um nível baixo.
	int NoiseLevel;

	/// *UVW_NOISE_PHASE
	/// Fase do ruído, que pode afetar como o ruído é distribuído na textura. Um valor de 0.0000 indica que não há fase aplicada.
	float NoisePhase;
};

/// *MAP_*
/// Tipos de mapas de textura que podem ser usados para definir diferentes propriedades dos materiais.
enum TextureType : unsigned int
{
	/// Mapa desconhecido, ou não informado.
	TEXTUREMAP_UNKNOWN,

	/// *MAP_BUMP
	/// Mapa de bump, que é usado para simular detalhes de superfície e pequenas imperfeições, criando a ilusão de profundidade sem alterar a geometria real do modelo.
	TEXTUREMAP_BUMP,

	/// *MAP_DIFFUSE
	/// Mapa difuso, controla a cor e a textura visível de uma superfície quando iluminada.
	/// Ele é essencialmente a base visual do material e define como a superfície parece sob a iluminação padrão.
	TEXTUREMAP_DIFFUSE,

	/// *MAP_SPECULAR
	/// Mapa especular, que define a intensidade e a cor das reflexões especulares na superfície do material. Ele afeta como a luz reflete na superfície.
	TEXTUREMAP_SPECULAR,

	/// *MAP_OPACITY
	/// Mapa de opacidade, que define a transparência de diferentes partes da superfície. Pode ser usado para criar materiais translúcidos ou com áreas transparentes.
	TEXTUREMAP_OPACITY,

	/// *MAP_REFLECT
	/// Mapa de reflexão, que define como a superfície do material reflete o ambiente ao seu redor.
	TEXTUREMAP_REFLECT,

	/// *MAP_REFRACT
	/// Mapa de refração, usado para materiais que dobram a luz que passa através deles, como vidro ou água.
	TEXTUREMAP_REFRACT,

	/// *MAP_ENVIRONMENT
	/// Mapa de ambiente, que pode ser usado para definir o fundo ou ambiente que é refletido na superfície do material.
	TEXTUREMAP_ENVIRONMENT,

	/// *MAP_DISPLACEMENT
	/// Mapa de deslocamento, que altera a geometria do modelo com base na textura, criando efeitos de relevo mais profundos do que o bump mapping.
	TEXTUREMAP_DISPLACEMENT,

	/// *MAP_LIGHT
	/// Mapa de luz, que pode ser usado para criar efeitos de iluminação específicos, como mapas de iluminação global.
	TEXTUREMAP_LIGHT,

	/// *MAP_FOG
	/// Mapa de neblina, que define a aparência da neblina ou fumaça aplicada ao material.
	TEXTUREMAP_FOG,

	/// *MAP_SELFILLUM
	/// Mapa de auto-iluminação, ou mapa de iluminação própria, define áreas de uma superfície que emitem luz por conta própria,
	/// independentemente da iluminação externa. Ele é usado para simular materiais ou partes de materiais que parecem brilhar ou emitir luz.
	TEXTUREMAP_SELFILLUM,
};

enum MapType : unsigned int
{
	/// Mapeamento desconhecido ou não informado.
	MAP_UNKNOWN,

	/// Este tipo de mapeamento projeta a textura em uma superfície como se fosse uma imagem em um slide projetado diretamente na geometria.
	/// É mais adequado para superfícies planas ou aquelas que não precisam de uma adaptação complexa.
	MAP_SCREEN,

	/// A textura é enrolada em torno do objeto de forma cilíndrica, como se estivesse envolvida ao redor de uma lata.
	/// Este tipo é útil para objetos que têm simetria circular ou seções alongadas e cilíndricas.
	MAP_CYLINDRICAL,

	/// A textura é projetada em um objeto como se estivesse envolta ao redor de uma esfera.
	/// Este tipo de mapeamento é eficaz para objetos com simetria esférica ou que precisam de uma cobertura uniforme em todas as direções.
	MAP_SPHERICAL,

	/// Aplica a textura em seis lados de uma caixa ao redor do objeto, ajustando automaticamente a textura para cada face.
	/// É adequado para objetos que possuem formas retangulares ou cúbicas.
	MAP_BOX,

	/// Este tipo envolve a textura em torno do objeto como um filme plástico, ajustando-se à forma do objeto como uma pele.
	/// É útil para objetos que têm uma forma complexa e precisam de uma cobertura de textura que se adapte intimamente às suas superfícies.
	MAP_SHRINKWRAP,

	/// Usa as coordenadas UV diretamente definidas no objeto 3D para mapear a textura.
	/// Esta é a forma mais versátil e detalhada de aplicar texturas, permitindo controle preciso sobre o posicionamento e a escala da textura.
	MAP_UV,
};

enum TextureFilter : unsigned int
{
	/// Nenhum filtro é aplicado. A textura é mapeada exatamente como está,
	/// o que pode resultar em uma aparência mais nítida, mas também em problemas como aliasing, especialmente em texturas detalhadas.
	TEXTUREFILTER_NONE,

	/// Este filtro aplica uma técnica de mipmapping, onde várias versões da textura são pré-calculadas em diferentes níveis de detalhe (piramidal).
	/// É selecionada a versão mais apropriada da textura com base na distância e no ângulo da câmera em relação ao objeto.
	TEXTUREFILTER_PYRAMIDAL,

	/// Este é um filtro mais sofisticado que usa uma tabela de área somada para calcular a média dos pixels da textura, proporcionando suavização.
	/// SAT é particularmente eficaz para texturas que sofrem de distorções severas ou são mapeadas em superfícies complexas.
	TEXTUREFILTER_SAT,
};

/// Mapa de textura, usado para definir diferentes propriedades do material.
struct TextureMap
{
public:
	void Load(KeyReader *reader);

	void SetFilter(std::string &str);

	void SetMapping(std::string &str);

	void SetMapType(const char *pKey);

public:
	/// Identificada o tipo do mapa de textura.
	/// { *MAP_BUMP, *MAP_DIFFUSE, *MAP_SPECULAR, *MAP_OPACITY, *MAP_REFLECT, *MAP_REFRACT, *MAP_ENVIRONMENT, *MAP_DISPLACEMENT, *MAP_LIGHT, *MAP_FOG, *MAP_SELFILLUM }
	TextureType Identifier;

	/// *MAP_NAME
	/// Nome do mapa de textura. Isso é útil para identificação e organização, especialmente quando há múltiplos mapas.
	char Name[64];

	/// *MAP_CLASS
	/// Tipo de mapa. `*MAP_CLASS "Bitmap"` é um mapa de bitmap, o que significa que ele usa uma imagem para a textura.
	char Class[64];

	/// *MAP_SUBNO
	/// Número da sub-textura. Se houver múltiplos mapas no mesmo material, cada um terá um número único.
	int SubNo;

	/// *MAP_AMOUNT
	/// Intensidade do mapa. Um valor de 1.0000 indica que o mapa está sendo aplicado com total intensidade.
	float Amount;

	/// *BITMAP
	/// Caminho para o arquivo de bitmap que é usado como a textura. Este é o arquivo de imagem que será aplicado à superfície do material.
	char FilePath[256];

	/// *MAP_TYPE
	/// Tipo de mapeamento. "*MAP_TYPE Screen" geralmente refere-se ao modo de projeção da textura na superfície do modelo.
	MapType Type;

	/// *UVW_
	/// Configurações de UVW da textura.
	UVWSettings UVW;

	/// *BITMAP_FILTER
	/// Tipo de filtro aplicado à textura bitmap.
	TextureFilter Filter;
};
