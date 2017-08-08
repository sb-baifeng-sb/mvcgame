
#include <mvcgame/platform/vita/RenderBridge.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureRegion.hpp>
#include <map>

namespace mvcgame {

    void RenderBridge::beforeDraw()
    {
        
    }

    void RenderBridge::afterDraw()
    {

    }

    void RenderBridge::setTransform(const Transform& transform)
    {

    }

	void RenderBridge::drawPolygon(const Points& points, const Color& color)
	{

	}

    void RenderBridge::drawTexture(std::shared_ptr<const Texture> texture, const Vertices& vertices)
    {

    }

}