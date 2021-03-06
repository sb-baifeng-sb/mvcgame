
#include <mvcgame/tile/TileSet.hpp>
#include <mvcgame/texture/TextureRegion.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>

#include <stdexcept>

namespace mvcgame {

    TileSet::TileSet() :
    _tileWidth(0),
    _tileHeight(0),
    _spacing(0),
    _margin(0),
    _offsetX(0),
    _offsetY(0)
    {
    }

    std::shared_ptr<const Texture> TileSet::getTexture() const
    {
        return _texture;
    }

    void TileSet::setTexture(std::shared_ptr<const Texture> texture)
    {
        _texture = texture;
    }

    const std::string& TileSet::getName() const
    {
        return _name;
    }

    void TileSet::setName(const std::string& name)
    {
        _name = name;
    }

    unsigned TileSet::getTileWidth() const
    {
        return _tileWidth;
    }

    void TileSet::setTileWidth(unsigned w)
    {
        _tileWidth = w;
    }

    unsigned TileSet::getTileHeight() const
    {
        return _tileHeight;
    }

    void TileSet::setTileHeight(unsigned h)
    {
        _tileHeight = h;
    }

    unsigned TileSet::getTileOffsetX() const
    {
        return _offsetX;
    }

    void TileSet::setTileOffsetX(unsigned x)
    {
        _offsetX = x;
    }

    unsigned TileSet::getTileOffsetY() const
    {
        return _offsetY;
    }

    void TileSet::setTileOffsetY(unsigned y)
    {
        _offsetY = y;
    }

    unsigned TileSet::getSpacing() const
    {
        return _spacing;
    }

    void TileSet::setSpacing(unsigned spacing)
    {
        _spacing = spacing;
    }

    unsigned TileSet::getMargin() const
    {
        return _margin;
    }
    
    void TileSet::setMargin(unsigned margin)
    {
        _margin = margin;
    }

    unsigned TileSet::getFirstTypeId() const
    {
        return _firstTypeId;
    }

    void TileSet::setFirstTypeId(unsigned typeId)
    {
        _firstTypeId = typeId;
    }

    bool TileSet::hasTypeId(unsigned typeId) const
    {
        unsigned nx = _texture->getWidth() / _tileWidth;
        unsigned ny = _texture->getHeight() / _tileHeight;
        unsigned p = typeId - _firstTypeId;
        return typeId >= _firstTypeId && p <= nx*ny;
    }

    TextureRegion TileSet::getRegionForTypeId(unsigned typeId) const
    {
        unsigned th = _texture->getHeight();
        unsigned nx = _texture->getWidth() / _tileWidth;
        unsigned ny = th / _tileHeight;
        unsigned p = typeId - _firstTypeId;
        if(typeId < _firstTypeId || p > nx*ny)
        {
            throw std::runtime_error("Tile type id does not fit inside the tileset texture.");
        }
        unsigned x = p % nx;
        unsigned y = ny - 1 - (p - x) / nx;
        TextureRegion r;
        r.x = _margin + x*(_tileWidth + _spacing);
        r.y = _margin + y*(_tileHeight + _spacing);
        r.width = _tileWidth;
        r.height = _tileHeight;
        r.offsetX = _offsetX;
        r.offsetY = _offsetY;
        r.originalWidth = r.width;
        r.originalHeight = r.height;

        return r;
    }

    SpriteSheet TileSet::getSheetForTypeId(unsigned typeId) const
    {
        return SpriteSheet(getTexture(), getRegionForTypeId(typeId));
    }
    
    std::ostream& operator<<(std::ostream& os, const TileSet& s)
    {
        os << "TileSet(" << s.getTileWidth() << "x" << s.getTileHeight() << std::endl;
        os << " spacing=" << s.getSpacing() << " margin=" << s.getMargin();
        os << " firstTypeId=" << s.getFirstTypeId() << std::endl;
        os << " offset=" << s.getTileOffsetX() << "x" << s.getTileOffsetY() << std::endl;
        if(s.getTexture())
        {
            os << *s.getTexture() << std::endl;
        }
        os << ")";
        return os;
    }
}
