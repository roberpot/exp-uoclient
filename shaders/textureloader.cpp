//
// Created by rot on 18/10/16.
//

const char * TEXTURE_FRAGMENT_SHADER = ""
        "#version 330 core\n"
        "in vec2 vtexcoord;\n"
        "uniform sampler2D tex;\n"
        "uniform vec4 color;\n"
        "out vec4 outcolor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    if (color.a > 0.0) {\n"
        "        outcolor = color;\n"
        "    } else {\n"
        "        outcolor = texture2D(tex, vtexcoord);\n"
        "        if(outcolor.a < 1.0)\n"
        "            discard;\n"
        "    }\n"
        "}";

const char * TEXTURE_VERTEX_SHADER = ""
        "varying vec2 vtexcoord;\n"
        "in vec4 input_position;\n"
        "\n"
        ""
        "void main(void)\n"
        "{\n"
        "   vtexcoord = gl_MultiTexCoord0.xy;\n"
        "   gl_Position = gl_ModelViewProjectionMatrix * input_position;\n"
        "}";
