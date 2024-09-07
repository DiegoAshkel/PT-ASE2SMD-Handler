#ifndef ASE_H
#define ASE_H

#include <string>
#include <vector>

#include "BinaryWriter.h"

struct RGB
{
	float R, G, B;
};

struct ARGB
{
	float A, R, G, B;
};

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

/// Tipo de sombreamento (shading) que será aplicado ao material.
enum ShadingType : unsigned int
{
	/// Sombreamento desconhecido ou não informado.
	SHADING_UNKNOWN,

	/// Um sombreamento extremamente básico que aplica uma cor uniforme ao material sem considerar a iluminação.
	/// Não há sombreamento real, o que pode dar uma aparência de "desenho" ou de "cartoon".
	/// Utilizado em aplicações onde o estilo gráfico exige uma aparência plana e simplificada, como em alguns estilos de arte digital ou animação.
	SHADING_FLAT,

	/// Um modelo de sombreamento amplamente utilizado que calcula os reflexos especulares usando um método aprimorado sobre o modelo Phong.
	/// Usado para materiais que precisam de reflexos suaves e naturais, como plásticos e metais polidos.
	SHADING_BLINN,

	/// Um modelo de sombreamento que calcula reflexos especulares com base na posição da câmera.
	/// Produz reflexos especulares mais brilhantes e nítidos que o modelo Blinn.
	/// Usado para superfícies lisas e brilhantes, como vidro ou superfícies metálicas.
	SHADING_PHONG,

	/// Simula o sombreamento de superfícies metálicas.
	/// Este modelo de sombreamento ajusta as propriedades de brilho e reflexo para imitar o comportamento da luz em metais.
	/// Ideal para criar materiais metálicos realistas, como aço, ouro, ou alumínio.
	SHADING_METAL,

	/// Este modelo é usado para superfícies que dispersam luz de maneira complexa.
	/// Perfeito para materiais como tecido, areia, ou superfícies ásperas e granuladas.
	SHADING_ORENNAYARBLINN,

	/// Um modelo simplificado para criar superfícies metálicas.
	/// Ele oferece menos controles, mas é útil para criar metais genéricos de maneira rápida.
	/// Usado quando uma rápida simulação de materiais metálicos é necessária sem a complexidade de ajustes detalhados.
	SHADING_STRAUSS,

	/// Simula superfícies que refletem luz de forma anisotrópica, ou seja, de maneira diferente dependendo do ângulo de visão.
	/// Usado para materiais que exibem padrões de reflexo alongados, como cabelo, seda, ou superfícies escovadas.
	/// Ideal para criar efeitos de superfície escovada em metais ou materiais que têm direcionalidade em seus reflexos.
	SHADING_ANISOTROPIC,

	/// Este modelo de sombreamento é utilizado para simular superfícies com múltiplas camadas de reflexão,
	/// como pintura automotiva, onde há uma camada base com reflexo e uma camada superior que também reflete luz.
	/// Excelente para materiais complexos como tintas automotivas, onde há necessidade de múltiplas camadas de brilho e reflexo.
	SHADING_MULTILAYER,

	/// Um modelo de sombreamento básico que calcula apenas a difusão, sem reflexos especulares. É ideal para superfícies mate.
	/// Usado em materiais como borracha, papel, ou qualquer superfície que precise parecer completamente sem brilho.
	SHADING_LAMBERT,

	/// Simula materiais translúcidos que permitem a passagem da luz, mas de maneira difusa.
	/// Este sombreamento é usado para materiais que têm uma aparência suave e levemente transparente.
	/// Ideal para materiais como pele, cera, papel vegetal ou outros que requerem uma simulação de transmissão de luz difusa.
	SHADING_TRANSLUCENT,
};

/// Tipo de efeito de queda, que afeta como a intensidade da iluminação diminui com a distância.
enum FallOffType : unsigned int
{
	/// Fallof desconhecido ou não informado.
	FALLOFF_UNKNOWN,

	/// Define um falloff onde a intensidade da propriedade diminui em direção ao centro do objeto.
	/// Isso significa que a borda do objeto terá mais intensidade da propriedade, como mais brilho ou reflexo, enquanto o centro terá menos.
	FALLOFF_IN,

	/// Define um falloff onde a intensidade da propriedade aumenta em direção ao centro do objeto e diminui nas bordas. O efeito é o oposto do falloff "In".
	FALLOFF_OUT,

	/// Controla o falloff com base no ângulo entre a superfície do material e a câmera.
	/// Faz com que a propriedade seja mais intensa quando a superfície é vista diretamente de frente (ângulo reto).
	FALLOFF_PERPENDICULAR,

	/// Controla o falloff com base no ângulo entre a superfície do material e a câmera.
	/// Aumenta a intensidade quando a superfície é vista em um ângulo raso.
	/// Comumente usado para criar reflexos que são mais visíveis em ângulos rasos, como em superfícies de água ou vidro.
	FALLOFF_PARALLEL,

	/// Este falloff é baseado na orientação do objeto em relação à câmera.
	/// Aumenta a intensidade à medida que a superfície se orienta em direção à câmera.
	FALLOFF_TOWARDS,

	/// Este falloff é baseado na orientação do objeto em relação à câmera.
	/// Aumenta a intensidade à medida que a superfície se orienta contra à câmera.
	FALLOFF_AWAY,

	/// Um tipo especial de falloff que simula o efeito Fresnel, onde o ângulo de visão afeta a intensidade do reflexo.
	/// Quanto mais raso o ângulo de visão, maior o reflexo, o que é comum em materiais como água e vidro.
	FALLOFF_FRESNEL,
};

/// Especifica o tipo de transição para os mapas de "falloff" baseados em uma curva de gradiente.
enum FallOffTransition : unsigned int
{
	/// Fallof desconhecido ou não informado.
	XPTYPE_UNKNOWN,

	/// Suaviza a curva de falloff, tornando a transição entre as regiões de alta e baixa intensidade mais gradual.
	XPTYPE_FILTER,

	/// Usado para simular reflexões que dependem do ângulo de visão.
	/// Este tipo de falloff é útil para materiais como espelhos ou superfícies metálicas altamente refletivas,
	/// onde a intensidade da reflexão varia significativamente com a orientação da superfície em relação à câmera.
	XPTYPE_REFLECT,

	/// Controla a intensidade da refração com base no ângulo de visão.
	/// É utilizado para materiais transparentes ou semitransparentes, como vidro ou água, onde a refração da luz varia com o ângulo.
	XPTYPE_REFRACT,

	/// Ajusta o comportamento das sombras projetadas pelo material.
	/// Este tipo de falloff pode ser utilizado para controlar a suavidade ou intensidade das sombras com base em determinadas condições geométricas ou de iluminação.
	XPTYPE_SHADOW,
};

class SubMaterial
{
public:
	void Save(Shared::BinaryWriter &bw);

public:
	/// Índice do sub-material na lista. Onde `*SUBMATERIAL 0` é o material de índice 0 na lista de materiais.
	int Index;

	/// *MATERIAL_NAME
	/// Nome do material principal.
	char Name[64];

	/// *MATERIAL_CLASS
	/// Classe do material. Onde:
	/// *MATERIAL_CLASS "Standard":  O material é do tipo "Standard", que é um tipo básico de material no 3ds Max.
	/// *MATERIAL_CLASS "Multi/Sub-Object": O é um material composto por vários submateriais.
	char Class[64];

	/// *MATERIAL_AMBIENT
	/// Cor ambiental do material em formato RGB. É a cor que aparece na sombra ou na ausência de luz direta.
	RGB Ambient;

	/// *MATERIAL_DIFFUSE
	/// Cor difusa do material em formato RGB. É a cor principal que o objeto exibe sob luz branca.
	RGB Diffuse;

	/// *MATERIAL_SPECULAR
	/// Cor especular do material em formato RGB. É a cor da luz refletida em superfícies brilhantes.
	RGB Specular;

	/// *MATERIAL_SHINE
	/// O brilho do material. `*MATERIAL_SHINE 0.250` Um valor de 0.250 indica um brilho moderado.
	float Shine;

	/// *MATERIAL_SHINESTRENGTH
	/// Força do brilho, afetando a intensidade do reflexo especular.
	float ShineStrength;

	/// *MATERIAL_TRANSPARENCY
	/// Transparência do material. Um valor de 0.000 indica que o material é completamente opaco.
	float Transparency; // Opacity?

	/// *MATERIAL_WIRESIZE
	/// Tamanho da grade de visualização de malha (se aplicável).
	float WireSize;

	/// *MATERIAL_SHADING
	/// Tipo de sombreamento usado.
	/// Cada tipo de *MATERIAL_SHADING oferece uma maneira diferente de simular a interação da luz com a superfície do material.
	/// A escolha do tipo de sombreamento depende do efeito visual desejado e das propriedades do material que você está tentando simular.
	ShadingType Shading;

	/// *MATERIAL_SELFILLUM
	/// Autoiluminação do material. Um valor de 0.000 significa que o material não emite luz própria.
	float SelfIllum;

	/// *MATERIAL_FALLOFF
	/// Tipo de efeito de queda, que afeta como a intensidade da iluminação diminui com a distância.
	FallOffType FallOff;

	/// *MATERIAL_XP_FALLOFF
	/// Ajuste a intensidade efeito de queda, se aplicável.
	float XPFallOff;

	/// *MATERIAL_XP_TYPE
	/// Especifica o tipo de transição para os mapas de "falloff" baseados em uma curva de gradiente.
	FallOffTransition FallOffTransition;

	/// Mapa de Texturas
	std::vector<TextureMap> TextureMaps;
};

/// *MATERIAL
/// Início da definição de um material específico.
class Material
{
public:
	void Save(Shared::BinaryWriter &bw);

	void Add(const TextureMap &texture);
	void Add(const SubMaterial &material);

public:
	/// Índice do material na lista de Materiais. Onde `*MATERIAL 0` é o material de índice 0 na lista de materiais.
	int Index;

	/// *MATERIAL_NAME
	/// Nome do material principal.
	char Name[64];

	/// *MATERIAL_CLASS
	/// Classe do material. Onde:
	/// *MATERIAL_CLASS "Standard":  O material é do tipo "Standard", que é um tipo básico de material no 3ds Max.
	/// *MATERIAL_CLASS "Multi/Sub-Object": O é um material composto por vários submateriais.
	char Class[64];

	/// *MATERIAL_AMBIENT
	/// Cor ambiental do material em formato RGB. É a cor que aparece na sombra ou na ausência de luz direta.
	RGB Ambient;

	/// *MATERIAL_DIFFUSE
	/// Cor difusa do material em formato RGB. É a cor principal que o objeto exibe sob luz branca.
	RGB Diffuse;

	/// *MATERIAL_SPECULAR
	/// Cor especular do material em formato RGB. É a cor da luz refletida em superfícies brilhantes.
	RGB Specular;

	/// *MATERIAL_SHINE
	/// O brilho do material. `*MATERIAL_SHINE 0.250` Um valor de 0.250 indica um brilho moderado.
	float Shine;

	/// *MATERIAL_SHINESTRENGTH
	/// Força do brilho, afetando a intensidade do reflexo especular.
	float ShineStrength;

	/// *MATERIAL_TRANSPARENCY
	/// Transparência do material. Um valor de 0.000 indica que o material é completamente opaco.
	float Transparency; // Opacity?

	/// *MATERIAL_WIRESIZE
	/// Tamanho da grade de visualização de malha (se aplicável).
	float WireSize;

	/// *MATERIAL_SHADING
	/// Tipo de sombreamento usado.
	/// Cada tipo de *MATERIAL_SHADING oferece uma maneira diferente de simular a interação da luz com a superfície do material.
	/// A escolha do tipo de sombreamento depende do efeito visual desejado e das propriedades do material que você está tentando simular.
	ShadingType Shading;

	/// *MATERIAL_SELFILLUM
	/// Autoiluminação do material. Um valor de 0.000 significa que o material não emite luz própria.
	float SelfIllum;

	/// *MATERIAL_FALLOFF
	/// Tipo de efeito de queda, que afeta como a intensidade da iluminação diminui com a distância.
	FallOffType FallOff;

	/// *MATERIAL_XP_FALLOFF
	/// Ajuste a intensidade efeito de queda, se aplicável.
	float XPFallOff;

	/// *MATERIAL_XP_TYPE
	/// Especifica o tipo de transição para os mapas de "falloff" baseados em uma curva de gradiente.
	FallOffTransition FallOffTransition;

	/// Mapa de Texturas
	std::vector<TextureMap> TextureMaps;

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

	void Add(const Material &material);

public:
	/// *MATERIAL_COUNT
	/// Número total de materiais.
	int Count;

	/// *MATERIAL
	/// Materiais disponíveis na cena.
	std::vector<Material> Materials;
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

#endif // ASE_H
