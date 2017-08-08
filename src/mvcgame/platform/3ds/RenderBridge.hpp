#ifndef mvcgame_dx_RenderBridge_hpp
#define mvcgame_dx_RenderBridge_hpp

#include <mvcgame/platform/IRenderBridge.hpp>

namespace mvcgame {

    class RenderBridge : public IRenderBridge
    {
    public:
        void beforeDraw();
        void afterDraw();
        void setTransform(const Transform& transform);
        void drawPolygon(const Points& points, const Color& color);
        void drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices);
    };

}

#endif