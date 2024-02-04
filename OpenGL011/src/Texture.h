#pragma once

namespace LM
{
	class Texture
	{
	protected:
		unsigned int m_uTextureID;
		unsigned char m_ubTextureIndex;
		int m_nHeight;
		int m_nWidth;

		/// <summary>
		/// 纹理类型 可选texture_diffuse texture_specular texture_normal texture_height
		/// </summary>
		std::string m_strType;
		aiString m_aistrPath;		// 纹理路径

		/// <summary>
		/// 加载纹理
		/// </summary>
		/// <param name="texture">纹理对象id</param>
		/// <param name="path">纹理图片源文件</param>
		/// <param name="index">纹理索引</param>
		/// <param name= "texColorMode">纹理颜色模式</param>
		/// <param name= "resColorMode">源图片颜色模式</param>
		/// <param name="bGenerateMipmap">是否自动生成多级渐远纹理</param>
		/// <returns></returns>
		virtual bool LoadTexture(unsigned int* texture, const std::string& path, unsigned char index,
			int texColorMode, int resColorMode, bool bGenerateMipmap);
	public:
		

		/// <summary>
		/// 构造函数
		/// </summary>
		/// <param name="imgPath">纹理图片路径</param>
		/// <param name="index">纹理索引 从0开始，最大15</param>
		/// <param name="texColorMode">纹理的颜色模式，一般为GL_RGB或GL_RGBA。</param>
		/// <param name="imgColorMode">图片资源的颜色模式，同上</param>
		/// <param name="bGenerateMipmap">是否生成多级渐远纹理，默认为true</param>
		Texture(const std::string& imgPath, unsigned char index, int texColorMode,
			int imgColorMode, bool bGenerateMipmap = true);
		~Texture();
		Texture() {};

		virtual void Bind();
		virtual unsigned char GetIndex()const;
		unsigned int GetTexID()const;
		void InitFromModelFile(const char* filename, const std::string& directory, const std::string& type);
	
		const std::string& GetTexType();
		const aiString& GetTexPath();

		int GetHeight() const;
		int GetWidth() const;
	};
}

