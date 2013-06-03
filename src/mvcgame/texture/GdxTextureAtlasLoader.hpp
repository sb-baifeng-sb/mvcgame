
#ifndef mvcgame_GdxTextureAtlasLoader_hpp
#define mvcgame_GdxTextureAtlasLoader_hpp

#include <mvcgame/texture/ITextureAtlasLoader.hpp>

namespace mvcgame {

    class GdxTextureAtlasLoader : public ITextureAtlasLoader
    {
    public:
        bool validate(std::istream& input) const;
        std::unique_ptr<TextureAtlas> load(std::istream& input) const;
    };
}

#endif