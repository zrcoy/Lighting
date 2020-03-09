#ifndef __VertexFormat_H__
#define __VertexFormat_H__

class VertexFormat
{
public:
    vec3 m_Pos;
    MyColor m_Color;
    vec3 m_Normal;
    vec2 m_UV;

    VertexFormat()
    {
        m_Pos.Set( 0, 0, 0 );
        m_Color = MyColor( 0, 0, 0, 255 );
        m_Normal.Set( 0, 1, 0 );
        m_UV.Set( 0, 0 );
    }

    VertexFormat(vec3 pos, MyColor color, vec2 uv)
    {
        m_Pos = pos;
        m_Color = color;
        m_Normal.Set( 0, 1, 0 );
        m_UV = uv;
    }

    VertexFormat(vec3 pos, MyColor color, vec3 normal, vec2 uv)
    {
        m_Pos = pos;
        m_Color = color;
        m_Normal = normal;
        m_UV = uv;
    }
};

#endif //__VertexFormat_H__
