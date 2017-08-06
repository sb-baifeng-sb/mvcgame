#ifndef mvcgame_SpineSkeletonLoader_hpp
#define mvcgame_SpineSkeletonLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;
    class SpineSkeleton;
    template<typename Asset>
    class AssetManager;

    class SpineSkeletonLoader : public IAssetLoader<SpineSkeleton>
    {
    private:
        AssetManager<TextureAtlas>* _textureAtlasManager;        
    public:
        SpineSkeletonLoader();

        bool validate(AssetStreamParam& param) const;
        std::shared_ptr<SpineSkeleton> load(AssetStreamParam& param) const;

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureAtlasManager(AssetManager<TextureAtlas>& mng);

    };

}

#endif