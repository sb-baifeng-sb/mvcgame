
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

#include <algorithm>

namespace mvcgame {

    SpriteFrame::SpriteFrame(std::shared_ptr<Texture> texture) :
    _texture(texture), _region(*texture)
    {
    }    

    SpriteFrame::SpriteFrame(std::shared_ptr<Texture> texture, const TextureRegion& region) :
    _texture(texture), _region(region)
    {
    }

    const Texture& SpriteFrame::getTexture() const
    {
        return *_texture;
    }

    Texture& SpriteFrame::getTexture()
    {
        return *_texture;
    }

    const TextureRegion& SpriteFrame::getRegion() const
    {
        return _region;
    }

    TextureRegion& SpriteFrame::getRegion()
    {
        return _region;
    }

    SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture)
    {
        _frames.push_back(Frame(texture));
    }

    SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, const TextureRegions& regions)
    {
        setRegions(texture, regions);
    }

    SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, const TextureAtlas& atlas)
    {
        TextureRegions regions(atlas.getRegions());
        std::sort(regions.begin(), regions.end());
        setRegions(texture, regions);
    }

    SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, const TextureAtlas& atlas, const std::string& name)
    {
        TextureRegions regions(atlas.getRegions(name));
        std::sort(regions.begin(), regions.end());
        setRegions(texture, regions);
    }

    void SpriteSheet::setRegions(std::shared_ptr<Texture> texture, const TextureRegions& regions)
    {
        for(const TextureRegion& region : regions)
        {
            _frames.push_back(Frame(texture, region));
        }
    }

    const SpriteSheet::Frames& SpriteSheet::getFrames() const
    {
        return _frames;
    }

    SpriteSheet::Frames& SpriteSheet::getFrames()
    {
        return _frames;
    }

    const SpriteSheet::Frame& SpriteSheet::getFrame(unsigned i) const
    {
        return _frames.at(i);
    }

    SpriteSheet::Frame& SpriteSheet::getFrame(unsigned i)
    {
        return _frames.at(i);
    }

    unsigned SpriteSheet::getLength() const
    {
        return _frames.size();
    }

    Size SpriteSheet::getSize() const
    {
        Size size;
        for(const Frame& frame : _frames)
        {
            float w = frame.getRegion().originalWidth;
            float h = frame.getRegion().originalHeight;
            size.width = std::max(w, size.width);
            size.height = std::max(h, size.height);
        }
        return size;
    }
}