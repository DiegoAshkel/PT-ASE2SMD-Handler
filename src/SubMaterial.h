#pragma once

#include "BinaryWriter.h"
#include "TextureMap.h"

#include <string>
#include <vector>

class KeyReader;

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
enum FallOffXpType : unsigned int
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
	SubMaterial();
	virtual ~SubMaterial();

	virtual void Save(Shared::BinaryWriter &bw);
	void Load(KeyReader *reader);

	virtual void Add(const TextureMap &texture);

	static FallOffXpType GetXpType(std::string &str);

	static FallOffType GetFallOff(std::string &str);

	static ShadingType GetShading(std::string &str);

protected:
	virtual void SetKey(const char *lpKey, KeyReader *reader);

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
	FallOffXpType XpType;

	/// Mapa de Texturas
	std::vector<TextureMap> TextureMaps;
};
