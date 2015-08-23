///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/copy.inl
/// @date 2013-01-23 / 2013-02-03
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline image copy(image const & Image)
	{
		image Result(Image.format(), Image.dimensions());

		memcpy(Result.data<glm::byte>(), Image.data<glm::byte>(), Image.size());
		
		return Result;
	}

	inline texture copy(texture2D const & Texture, texture2D::format_type Format)
	{
		texture2D Copy(
			Format,
			Texture.levels(),
			Texture.dimensions());

		memcpy(
			Copy.data<glm::byte>(),
			Texture.data<glm::byte>(),
			Copy.size<glm::byte>());
		
		return Copy;
	}

	template <>
	inline texture copy<texture1D>(texture1D const & Texture)
	{
		texture1D Copy(
			Texture.format(),
			Texture.dimensions(),
			Texture.levels());

		memcpy(
			Copy.data<glm::byte>(),
			Texture.data<glm::byte>(),
			Copy.size<glm::byte>());
		
		return Copy;
	}

	template <>
	inline texture copy(texture1DArray const & Texture)
	{
		texture1DArray Copy(
			Texture.format(),
			Texture.dimensions(),
			Texture.layers(),
			Texture.levels());

		for(texture1DArray::size_type Layer = 0; Layer < Copy.layers(); ++Layer)
		{
			memcpy(
				Copy[Layer].data<glm::byte>(),
				Texture[Layer].data<glm::byte>(),
				Copy[Layer].size<glm::byte>());
		}
		
		return Copy;
	}

	template <>
	inline texture copy(texture2D const & Texture)
	{
		texture2D Copy(
			Texture.format(),
			Texture.levels(),
			Texture.dimensions());

		memcpy(
			Copy.data<glm::byte>(),
			Texture.data<glm::byte>(),
			Copy.size<glm::byte>());
		
		return Copy;
	}

	template <>
	inline texture copy(texture2DArray const & Texture)
	{
		texture2DArray Copy(Texture.format(), Texture.layers(), Texture.levels(), Texture.dimensions());

		for(texture2DArray::size_type Layer = 0; Layer < Copy.layers(); ++Layer)
			memcpy(Copy[Layer].data<glm::byte>(), Texture[Layer].data<glm::byte>(), Copy[Layer].size<glm::byte>());
		
		return Copy;
	}

	template <>
	inline texture copy(texture3D const & Texture)
	{
		texture3D Copy(
			Texture.format(),
			Texture.dimensions(),
			Texture.levels());

		memcpy(
			Copy.data<glm::byte>(),
			Texture.data<glm::byte>(),
			Texture.size<glm::byte>());
		
		return Copy;
	}

	template <>
	inline texture copy(textureCube const & Texture)
	{
		textureCube Copy(
			Texture.format(),
			Texture.levels(),
			Texture.dimensions());

		for(textureCube::size_type Face = 0; Face < Copy.faces(); ++Face)
		{
			memcpy(
				Copy[Face].data<glm::byte>(),
				Texture[Face].data<glm::byte>(),
				Texture[Face].size<glm::byte>());
		}
		
		return Copy;
	}

	template <>
	inline texture copy(textureCubeArray const & Texture)
	{
		textureCubeArray Copy(
			Texture.format(),
			Texture.dimensions(),
			Texture.layers(),
			Texture.levels());

		for(textureCubeArray::size_type Layer = 0; Layer < Copy.layers(); ++Layer)
		for(textureCubeArray::size_type Face = 0; Face < Copy[Layer].faces(); ++Face)
		{
			memcpy(
				Copy[Layer][Face].data<glm::byte>(),
				Texture[Layer][Face].data<glm::byte>(),
				Copy[Layer][Face].size<glm::byte>());
		}

		return Copy;
	}

	inline texture copy
	(
		texture1D const & Texture,
		texture1D::size_type BaseLevel, texture1D::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
	
		texture1D Copy(
			Texture.format(),
			texture1D::dim_type(Texture[BaseLevel].dimensions().x), 
			MaxLevel - BaseLevel + 1);

		memcpy(
			Copy.data<glm::byte>(),
			Texture[BaseLevel].data<glm::byte>(),
			Copy.size<glm::byte>());
		
		return Copy;
	}

	inline texture copy
	(
		texture1DArray const & Texture,
		texture1DArray::size_type BaseLayer, texture1DArray::size_type MaxMayer,
		texture1DArray::size_type BaseLevel, texture1DArray::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
		assert(BaseLayer <= MaxMayer);
		assert(BaseLayer < Texture.layers());
		assert(MaxMayer < Texture.layers());

		texture1DArray Copy(
			Texture.format(),
			texture1DArray::dim_type(Texture[BaseLayer][BaseLevel].dimensions().x), 
			MaxMayer - BaseLayer + 1,
			MaxLevel - BaseLevel + 1);

		for(texture1DArray::size_type Layer = 0; Layer < Copy.layers(); ++Layer)
		{
			memcpy(
				Copy[Layer].data<glm::byte>(),
				Texture[Layer + BaseLayer][BaseLevel].data<glm::byte>(),
				Copy[Layer].size<glm::byte>());
		}

		return Copy;
	}

	inline texture copy
	(
		texture2D const & Texture,
		texture2D::size_type BaseLevel, texture2D::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
	
		texture2D Copy(
			Texture.format(),
			MaxLevel - BaseLevel + 1,
			texture2D::dim_type(Texture[BaseLevel].dimensions().x));

		memcpy(
			Copy.data<glm::byte>(),
			Texture[BaseLevel].data<glm::byte>(),
			Copy.size<glm::byte>());
		
		return Copy;
	}

	inline texture copy
	(
		texture2DArray const & Texture,
		texture2DArray::size_type BaseLayer, texture2DArray::size_type MaxMayer,
		texture2DArray::size_type BaseLevel, texture2DArray::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
		assert(BaseLayer <= MaxMayer);
		assert(BaseLayer < Texture.layers());
		assert(MaxMayer < Texture.layers());

		texture2DArray Copy(
			Texture.format(), 
			MaxMayer - BaseLayer + 1,
			MaxLevel - BaseLevel + 1,
			texture2DArray::dim_type(Texture[BaseLayer][BaseLevel].dimensions()));

		for(texture2DArray::size_type Layer = 0; Layer < Copy.layers(); ++Layer)
		{
			memcpy(
				Copy[Layer].data<glm::byte>(),
				Texture[Layer + BaseLayer][BaseLevel].data<glm::byte>(),
				Copy[Layer].size<glm::byte>());
		}
		
		return Copy;
	}

	inline texture copy
	(
		texture3D const & Texture,
		texture3D::size_type BaseLevel, texture3D::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
	
		texture3D Copy(
			Texture.format(),
			texture3D::dim_type(Texture[BaseLevel].dimensions()),
			MaxLevel - BaseLevel + 1);

		memcpy(
			Copy.data<glm::byte>(),
			Texture[BaseLevel].data<glm::byte>(),
			Copy.size<glm::byte>());
		
		return Copy;
	}

	inline texture copy
	(
		textureCube const & Texture,
		textureCube::size_type BaseFace, textureCube::size_type MaxFace,
		textureCube::size_type BaseLevel, textureCube::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
		assert(BaseFace <= MaxFace);
		assert(BaseFace < Texture.faces());
		assert(MaxFace < Texture.faces());

		textureCube Copy(
			Texture.format(), 
			MaxLevel - BaseLevel + 1,
			textureCube::dim_type(Texture[BaseFace][BaseLevel].dimensions()));

		for(textureCube::size_type Face = 0; Face < Copy.faces(); ++Face)
		{
			memcpy(
				Copy[Face].data<glm::byte>(), 
				Texture[Face + BaseFace][BaseLevel].data<glm::byte>(), 
				Copy[Face].size<glm::byte>());
		}
		
		return Copy;
	}

	inline texture copy
	(
		textureCubeArray const & Texture,
		textureCubeArray::size_type BaseLayer, textureCubeArray::size_type MaxLayer,
		textureCubeArray::size_type BaseFace, textureCubeArray::size_type MaxFace,
		textureCubeArray::size_type BaseLevel, textureCubeArray::size_type MaxLevel
	)
	{
		assert(BaseLevel <= MaxLevel);
		assert(BaseLevel < Texture.levels());
		assert(MaxLevel < Texture.levels());
		assert(BaseFace <= MaxFace);
		assert(BaseFace < Texture.faces());
		assert(MaxFace < Texture.faces());
		assert(BaseLayer <= MaxLayer);
		assert(BaseLayer < Texture.layers());
		assert(MaxLayer < Texture.layers());

		textureCubeArray Copy(
			Texture.format(),
			textureCubeArray::dim_type(Texture[BaseLayer][BaseFace][BaseLevel].dimensions()),
			MaxLayer - BaseLayer + 1,
			MaxLevel - BaseLevel + 1);

		for(textureCubeArray::size_type Layer = 0; Layer < Copy.layers(); ++Layer)
		for(textureCubeArray::size_type Face = 0; Face < Copy[Layer].faces(); ++Face)
		{
			memcpy(
				Copy[Layer][Face].data<glm::byte>(),
				Texture[Layer + BaseLayer][Face + BaseFace][BaseLevel].data<glm::byte>(),
				Copy[Layer][Face].size<glm::byte>());
		}

		return Copy;
	}
}//namespace gli
