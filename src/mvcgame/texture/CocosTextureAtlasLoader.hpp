
#ifndef mvcgame_CocosTextureAtlasLoader_hpp
#define mvcgame_CocosTextureAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;
    class Texture;
    template<typename Asset>
    class AssetManager;

    class CocosTextureAtlasLoader : public IAssetLoader<TextureAtlas>
    {
    private:
        AssetManager<Texture>* _textureManager;        
    public:
        CocosTextureAtlasLoader();

        bool validate(AssetStreamParam& param) const;
		std::shared_ptr<TextureAtlas> load(AssetStreamParam& param) const;

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureManager(AssetManager<Texture>& mng);
    };
}

#endif