#include "pch.h"
#include "TestTextureMap.h"

test::TestTextureMap::TestTextureMap()
{
	std::cout << "TextureName:\n";
	for (int i = 0; i < 5; i++)
	{
		std::cout << i <<"  "<< LM::TextureTypeMap::TextureType2Str((LM::TextureType)i) << std::endl;
	}
	std::cout << "TextureType2UniformName:\n";
	for(int i = 1;i<5;i++)
		for (int j = 1; j <= 8; j++)
		{
			std::cout << i << "  "<< LM::TextureTypeMap::TextureType2UniformName((LM::TextureType)i, j) << std::endl;
		}
}

test::TestTextureMap::~TestTextureMap()
{
	if (LM::TextureTypeMap::s_Instance)
		delete LM::TextureTypeMap::s_Instance;
}
