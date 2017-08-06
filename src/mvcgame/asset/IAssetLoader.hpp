

#ifndef mvcgame_IAssetLoader_hpp
#define mvcgame_IAssetLoader_hpp

#include <memory>
#include <iostream>
#include "AssetStreamParam.hpp"

namespace mvcgame {

    template<typename Asset>
    class IAssetLoader
    {
    public:
        virtual ~IAssetLoader(){};

        /**
         * The stream should be at the start
         *
         * @return true if the asset can be loaded
         */
		virtual bool validate(AssetStreamParam& param) const
        {
            return true;
        }

        /**
         * The stream should be at the start
         * @return the new asset
         */
		virtual std::shared_ptr<Asset> load(AssetStreamParam& param) const = 0;
    };

}

#endif