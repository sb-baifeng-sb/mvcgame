
#ifndef mvcgame_GdxTextureAtlasLoader_hpp
#define mvcgame_GdxTextureAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;
    class Texture;
    template<typename Asset>
    class AssetManager;

    class GdxTextureAtlasLoader : public IAssetLoader<TextureAtlas>
    {
    private:
        AssetManager<Texture>* _textureManager;        
    public:
        GdxTextureAtlasLoader();

        bool validate(AssetStreamParam& param) const;
        std::shared_ptr<TextureAtlas> load(AssetStreamParam& param) const;

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureManager(AssetManager<Texture>& mng);         
    };
}

#endif