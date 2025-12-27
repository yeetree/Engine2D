#ifndef SOURCE_RENDERER_RENDERER2DPRIMITIVESHADER
#define SOURCE_RENDERER_RENDERER2DPRIMITIVESHADER

const char* k_Renderer2DPrimitiveVertexShader = R"(
#version 330 core
layout (location = 0) in vec2 pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 posFrag;
out vec2 v_TexCoord;

void main() {
    gl_Position = u_ViewProjection * u_Transform * vec4(pos, 0.0, 1.0);
    
    v_TexCoord = pos; 
    
    posFrag = (pos - vec2(0.5)) * 2.0;
}
)";

const char* k_Renderer2DPrimitiveFragmentShader = R"(
#version 330 core
in vec2 posFrag;
in vec2 v_TexCoord;

uniform float thickness;
uniform float sizePixel;
uniform vec4 drawColor;
uniform int shapeType;

uniform sampler2D u_Texture;

out vec4 FragColor;

// For sprites
void drawTexture() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    
    if (texColor.a < 0.01)
        discard;
        
    FragColor = texColor * drawColor;
}

// Functions for drawing each shape
void fillOval() {
   float distance = 1.0 - length(posFrag) + sizePixel / 2.0;
   float alpha = clamp(distance / sizePixel, 0.0, 1.0);
   if (alpha < 0.01f)
      discard;
   FragColor  = vec4(drawColor.xyz, drawColor.w * alpha);
}

void fillRectangle() {
   FragColor = drawColor;
}

void outlineOval() {
    // Calculate how far the fragment is from the edge (1.0).
    float edgeDistance = length(posFrag) - 1.0; 
    

    // Get thickness in NDC
    float thicknessNDC = thickness * sizePixel; 
    
    if (edgeDistance < 0.0 && edgeDistance > -thicknessNDC) {
        FragColor = drawColor;
    } else {
        // The pixel is outside the oval OR too far inside the oval.
        discard;
    }
}

void outlineRectangle() {
   // todo: implement
   FragColor = drawColor;
}


//Draw the shape, default to rectangle
void main()
{
   switch (shapeType) {
      case 1: fillOval();  break;
      case 2: fillRectangle(); break;
      case 3: outlineOval(); break;
      case 4: outlineRectangle(); break;
      case 5: drawTexture(); break;
      default: fillRectangle();  break;
   }
}
)";

#endif // SOURCE_RENDERER_RENDERER2DPRIMITIVESHADER
