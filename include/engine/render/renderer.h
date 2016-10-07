#ifndef _ENGINE_RENDER_RENDERER_H_
#define _ENGINE_RENDER_RENDERER_H_

#include <GL/glew.h>
#include <vector>

#include "engine/render/shader.h"
#include "engine/render/vertexarray.h"
#include "engine/render/texture.h"
#include "engine/render/camera.h"

namespace zi
{
    class Renderer
    {
    public:
        Renderer(void);
        virtual ~Renderer(void);
        
        void render(zi::VertexArray &vertexArray,
                    zi::Shader &shader,
                    zi::Texture *texture = nullptr);
        void render(zi::Camera &camera,
                    zi::VertexArray &vertexArray,
                    zi::Shader &shader,
                    zi::Texture *texture = nullptr);
        
    private:
        void render(zi::VertexArray &vertexArray,
                    zi::Shader &shader,
                    zi::Texture *texture,
                    glm::mat4 *transform);          // Override vertexArray transform (use ony for camera!)
    };
}

#endif // _ENGINE_RENDER_RENDERER_H_
