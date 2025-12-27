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

uniform vec2 u_Dimensions;

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
    float distance = length(posFrag) - 1.0; 
    if (distance > 0.00f)
        discard;
    FragColor = drawColor;
}

void fillRectangle() {
   FragColor = drawColor;
}

void outlineRectangle() {
    // Calculate distance from edge SDF
    vec2 d = abs(posFrag * (u_Dimensions * 0.5)) - (u_Dimensions * 0.5);
    float dist = length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);

    if (dist > 0.0 || dist < -thickness) {
        discard;
    }

    FragColor = drawColor;
}

void outlineOval() {
    // Get position in world space
    vec2 posWorld = posFrag * (u_Dimensions * 0.5);
    float d = length(posWorld);

    // Calculate thets
    float theta = atan(posWorld.y, posWorld.x);
    
    // Polar equation of an ellipse: 
    // r = (a * b) / sqrt((b*cos(theta))^2 + (a*sin(theta))^2)
    float a = u_Dimensions.x * 0.5; // semi-major axis
    float b = u_Dimensions.y * 0.5; // semi-minor axis
    
    float denominator = sqrt(pow(b * cos(theta), 2.0) + pow(a * sin(theta), 2.0));
    float r = (a * b) / denominator;

    // 4. Calculate the distance from the edge
    float sdf = d - r;

    // 5. Draw the outline
    if (sdf > 0.0 || sdf < -thickness) {
        discard;
    }

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
