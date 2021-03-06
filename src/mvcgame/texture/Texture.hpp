

#ifndef mvcgame_Texture_hpp
#define mvcgame_Texture_hpp

#include <memory>
#include <cstdint>
#include <iostream>

namespace mvcgame {

    class Texture : public std::enable_shared_from_this<Texture>
    {
    private:
        std::unique_ptr<uint8_t> _data;
        std::size_t _length;
        unsigned _width;
        unsigned _height;
        bool _alpha;
    public:
        Texture(std::unique_ptr<uint8_t> data, std::size_t length, unsigned width, unsigned height, bool hasAlpha);
        
        const uint8_t* getData() const;
        std::size_t getLength() const;
        unsigned getWidth() const;
        unsigned getHeight() const;
        bool hasAlpha() const;
        unsigned getComponents() const;
    };

    /**
     Stream functions
     */
    std::ostream& operator<<(std::ostream& os, const Texture& t);
}

#endif