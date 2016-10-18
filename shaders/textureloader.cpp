//
// Created by rot on 18/10/16.
//

const char * TEXTURE_FRAGMENT_SHADER = ""
        "#version 330 core\n"
        "varying vec2 vTexCoord;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "    vec4 texColor = texture2D(tex, vTexCoord);\n"
        "    if(texColor.a < 0.1)\n"
        "        discard;\n"
        "    gl_FragColor = texColor;\n"
        "}";

const char * TEXTURE_VERTEX_SHADER = "varying vec2 vTexCoord;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "   vTexCoord = gl_MultiTexCoord0.xy;\n"
        "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
        "}";
