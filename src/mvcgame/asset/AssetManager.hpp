#ifndef mvcgame_AssetManager_hpp
#define mvcgame_AssetManager_hpp

#include <mvcgame/asset/AssetStreamManager.hpp>
#include <mvcgame/asset/IAssetLoader.hpp>

#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
#include <cassert>

namespace mvcgame {

    /**
     * This class loads assets of a given type. It maintains a list of 
     * loaders of the asset type and a reference to the main assets manager.
     *
     * To load an asset it will ask the asset stream loaders of the main manager
     * for possible streams, then it will ask the list of asset loaders if they can
     * load the given streams.
     *
     * The tag value can be set by the IStreamLoader
     * and similar to a file extension
     */
    template<typename Asset>
    class AssetManager
    {
    private:
        typedef IAssetLoader<Asset> Loader;
        typedef std::vector<std::unique_ptr<Loader>> Loaders;
        typedef std::map<std::string, Loaders> LoaderMap;

        LoaderMap _loaders;
        AssetStreamManager* _streams;

		bool doLoadStream(AssetStreamParam& param, const Loaders& loaders, std::shared_ptr<Asset>& asset)
		{
			std::istream& in = param.input;
			for (const std::unique_ptr<Loader>& loader : loaders)
			{
				in.seekg(0, std::ios::beg);
				if (loader->validate(param))
				{
					in.seekg(0, std::ios::beg);
					asset = loader->load(param);
					if (asset)
					{
						return true;
					}
				}
			}
			return false;
		}

		bool loadStream(AssetStreamParam& param, std::shared_ptr<Asset>& asset)
		{
			std::istream& in = param.input;
			std::string& tag = param.args["tag"];
			typename LoaderMap::const_iterator itr = _loaders.find(tag);
			if (itr != _loaders.end() && doLoadStream(param, itr->second, asset))
			{
				return true;
			}
			itr = _loaders.find("");
			if (itr != _loaders.end() && doLoadStream(param, itr->second, asset))
			{
				return true;
			}
			return false;
		}

    public:
        AssetManager() :
        _streams(nullptr)
        {
        }

        void add(std::unique_ptr<Loader> loader, const std::string& tag="")
        {
            _loaders[tag].push_back(std::move(loader));
        }

        void setStreamManager(AssetStreamManager& mng)
        {
            _streams = &mng;
        }

        std::shared_ptr<Asset> load(const std::string& name)
        {
            std::shared_ptr<Asset> asset = nullptr;
            bool success = false;
            assert(_streams);
            if(_streams && !_loaders.empty())
            {
                success = _streams->load(name, std::bind(&AssetManager<Asset>::loadStream,
                    this, std::placeholders::_1, std::ref(asset)));
            }
			if(!success)
			{
				throw std::runtime_error("Could not load asset");
			}
            return asset;
        }

    };
}

#endif