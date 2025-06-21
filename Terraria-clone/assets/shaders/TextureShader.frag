#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D u_Texture;

void main()
{
    if(TexCoords == vec2(0.0)){
        FragColor = vec4(1.0,0.0,1.0,1.0); //Magenta
    } else {
        FragColor = texture(u_Texture, TexCoords);
    }
}
