#ifndef _ENGINE_RENDER_RENDERER_H_
#define _ENGINE_RENDER_RENDERER_H_

#include <GL/glew.h>
#include <vector>

#include "engine/render/shader.h"
#include "engine/render/vertexarray.h"

namespace zi
{
    class Renderer
    {
    public:
        Renderer(void);
        virtual ~Renderer(void);
        
        void render(zi::VertexArray &vertexArray, zi::Shader &shader);
        
    private:
    };
}

#endif // _ENGINE_RENDER_RENDERER_H_
