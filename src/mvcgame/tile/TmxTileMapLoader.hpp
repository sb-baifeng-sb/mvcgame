
#ifndef mvcgame_TmxTileMapLoader_hpp
#define mvcgame_TmxTileMapLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

/**
 * @see http://code.google.com/p/tmx-parser/source/browse/trunk/TmxParser/
 * @see https://github.com/bjorn/tiled/wiki/TMX-Map-Format
 */
 namespace mvcgame {

    class TileMap;
    class Texture;
    class AssetStreamManager;
    template<typename Asset>
    class AssetManager;

    class TmxTileMapLoader : public IAssetLoader<TileMap>
    {
    private:
        AssetStreamManager* _streamManager;
        AssetManager<Texture>* _textureManager;
    public:

        TmxTileMapLoader();

        bool validate(AssetStreamParam& param) const;
		std::shared_ptr<TileMap> load(AssetStreamParam& param) const;


        /**
         * Set the assets manager to load related files
         */
        void setStreamManager(AssetStreamManager& mng);

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureManager(AssetManager<Texture>& mng);        
    };
}

#endif