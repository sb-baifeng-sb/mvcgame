
#ifndef mvcgame_Sprite_hpp
#define mvcgame_Sprite_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/base/Color.hpp>
#include <memory>

namespace mvcgame {

    class Sprite : public View
    {
    public:
        typedef SpriteSheet Sheet;
    private:
        bool _paused;
		unsigned _spriteFrame;
		unsigned _spriteFrameDuration;
		unsigned _spriteFrameUpdates;
        Sheet _sheet;
		Color _color;
    public:
        Sprite();
        Sprite(const Sheet& sheet);

        const Sheet& getSheet() const;
        void setSheet(const Sheet& sheet, bool changeSize=true);
        void setSheet(std::shared_ptr<const Texture> texture, bool changeSize=true);

		void setColor(const Color& color);
		Color const& getColor() const;

		void setAlpha(uint8_t a);
		uint8_t getAlpha() const;

        unsigned setSpriteFrame() const;
        void setSpriteFrame(unsigned frame);

        void setPaused(bool paused);
        bool getPaused() const;

        /**
         * the amount of updated needed to change frame
         */
        void setSpriteFrameDuration(unsigned num);
        unsigned getSpriteFrameDuration() const;

        void update();
        void draw();
    };
    
}


#endif
