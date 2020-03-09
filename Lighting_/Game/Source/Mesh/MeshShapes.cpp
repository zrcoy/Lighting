#include "GamePCH.h"

#include "Mesh.h"
#include "OBJLoader.h"
#include "Texture.h"
#include "VertexFormat.h"

void Mesh::CreateBox(vec2 size, vec2 offset)
{
    VertexFormat vertexAttributes[] =
    {
        VertexFormat( vec2( -size.x/2, -size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec3(0,0,-1), vec2( 0.0f, 0.0f ) ),
        VertexFormat( vec2( -size.x/2,  size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec3(0,0,-1), vec2( 0.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2,  size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec3(0,0,-1), vec2( 1.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2, -size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec3(0,0,-1), vec2( 1.0f, 0.0f ) ),
    };

    unsigned int indices[6] = { 0,1,2, 0,2,3 };

    Init( vertexAttributes, 4, indices, 6, GL_TRIANGLES, GL_STATIC_DRAW );
};

void Mesh::CreateBoxWithFlippedHorizontalUVs(vec2 size, vec2 offset)
{
    VertexFormat vertexAttributes[] =
    {
        VertexFormat( vec2( -size.x/2, -size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 1.0f, 0.0f ) ),
        VertexFormat( vec2( -size.x/2,  size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 1.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2,  size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 0.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2, -size.y/2 ) + offset, MyColor( 255, 255, 255, 255 ), vec2( 0.0f, 0.0f ) ),
    };

    unsigned int indices[6] = { 0,1,2, 0,2,3 };

    Init( vertexAttributes, 4, indices, 6, GL_TRIANGLES, GL_STATIC_DRAW );
};

void Mesh::CreateCube(vec3 size)
{
    VertexFormat verts[24];

    //   6--5
    // 1--2 |
    // |  |-4
    // 0--3

    // front
    verts[0] = VertexFormat( vec3( -size.x/2, -size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,-1 ), vec2( 0,0 ) );
    verts[1] = VertexFormat( vec3( -size.x/2,  size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,-1 ), vec2( 0,1 ) );
    verts[2] = VertexFormat( vec3(  size.x/2,  size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,-1 ), vec2( 1,1 ) );
    verts[3] = VertexFormat( vec3(  size.x/2, -size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,-1 ), vec2( 1,0 ) );

    // back
    verts[4] = VertexFormat( vec3(  size.x/2, -size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,1 ), vec2( 0,0 ) );
    verts[5] = VertexFormat( vec3(  size.x/2,  size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,1 ), vec2( 0,1 ) );
    verts[6] = VertexFormat( vec3( -size.x/2,  size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,1 ), vec2( 1,1 ) );
    verts[7] = VertexFormat( vec3( -size.x/2, -size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,0,1 ), vec2( 1,0 ) );

    //   9---14
    // 10--13 |
    // |   |-15
    // 11--12

    // left
    verts[8]  = VertexFormat( vec3( -size.x/2, -size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( -1,0,0 ), vec2( 0,0 ) );
    verts[9]  = VertexFormat( vec3( -size.x/2,  size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( -1,0,0 ), vec2( 0,1 ) );
    verts[10] = VertexFormat( vec3( -size.x/2,  size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( -1,0,0 ), vec2( 1,1 ) );
    verts[11] = VertexFormat( vec3( -size.x/2, -size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( -1,0,0 ), vec2( 1,0 ) );

    // right
    verts[12] = VertexFormat( vec3(  size.x/2, -size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 1,0,0 ), vec2( 0,0 ) );
    verts[13] = VertexFormat( vec3(  size.x/2,  size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 1,0,0 ), vec2( 0,1 ) );
    verts[14] = VertexFormat( vec3(  size.x/2,  size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 1,0,0 ), vec2( 1,1 ) );
    verts[15] = VertexFormat( vec3(  size.x/2, -size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 1,0,0 ), vec2( 1,0 ) );

    //   17--18
    // 16--19 |
    // |   |-21
    // 23--20

    // top
    verts[16] = VertexFormat( vec3( -size.x/2,  size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,1,0 ), vec2( 0,0 ) );
    verts[17] = VertexFormat( vec3( -size.x/2,  size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,1,0 ), vec2( 0,1 ) );
    verts[18] = VertexFormat( vec3(  size.x/2,  size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,1,0 ), vec2( 1,1 ) );
    verts[19] = VertexFormat( vec3(  size.x/2,  size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,1,0 ), vec2( 1,0 ) );

    // bottom
    verts[20] = VertexFormat( vec3(  size.x/2, -size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,-1,0 ), vec2( 0,0 ) );
    verts[21] = VertexFormat( vec3(  size.x/2, -size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,-1,0 ), vec2( 0,1 ) );
    verts[22] = VertexFormat( vec3( -size.x/2, -size.y/2,  size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,-1,0 ), vec2( 1,1 ) );
    verts[23] = VertexFormat( vec3( -size.x/2, -size.y/2, -size.z/2 ), MyColor( 255,255,255,255 ), vec3( 0,-1,0 ), vec2( 1,0 ) );

    unsigned int indices[36] =
    {
        0, 1, 2,  0, 2, 3, // front
        4, 5, 6,  4, 6, 7, // back
        8, 9,10,  8,10,11, // left
        12,13,14, 12,14,15, // right
        16,17,18, 16,18,19, // top
        20,21,22, 20,22,23, // bottom
    };

    Init( verts, 24, indices, 36, GL_TRIANGLES, GL_STATIC_DRAW );
};


void Mesh::CreateTeleporter(vec3 size)
{
    VertexFormat verts[24];

    //   6--5
    // 1--2 |
    // |  |-4
    // 0--3

    // front
    verts[0] = VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, -1), vec2(0, 0));
    verts[1] = VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, -1), vec2(0, 1));
    verts[2] = VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, -1), vec2(1, 1));
    verts[3] = VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, -1), vec2(1, 0));

    // back
    verts[4] = VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, 1), vec2(0, 0));
    verts[5] = VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, 1), vec2(0, 1));
    verts[6] = VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, 1), vec2(1, 1));
    verts[7] = VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 0, 1), vec2(1, 0));

    //   9---14
    // 10--13 |
    // |   |-15
    // 11--12

    // left
    verts[8] = VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(-1, 0, 0), vec2(0, 0));
    verts[9] = VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(-1, 0, 0), vec2(0, 1));
    verts[10] = VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(-1, 0, 0), vec2(1, 1));
    verts[11] = VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(-1, 0, 0), vec2(1, 0));

    // right
    verts[12] = VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(1, 0, 0), vec2(0, 0));
    verts[13] = VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(1, 0, 0), vec2(0, 1));
    verts[14] = VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(1, 0, 0), vec2(1, 1));
    verts[15] = VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(1, 0, 0), vec2(1, 0));

    //   17--18
    // 16--19 |
    // |   |-21
    // 23--20

    // top
    verts[16] = VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 1, 0), vec2(0, 0));
    verts[17] = VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 1, 0), vec2(0, 0));
    verts[18] = VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 1, 0), vec2(0, 0));
    verts[19] = VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, 1, 0), vec2(0, 0));

    // bottom
    verts[20] = VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, -1, 0), vec2(0, 0));
    verts[21] = VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, -1, 0), vec2(0, 0));
    verts[22] = VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2), MyColor(255, 255, 255, 255), vec3(0, -1, 0), vec2(0, 0));
    verts[23] = VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2), MyColor(255, 255, 255, 255), vec3(0, -1, 0), vec2(0, 0));

    unsigned int indices[36] =
    {
        0, 1, 2,  0, 2, 3, // front
        4, 5, 6,  4, 6, 7, // back
        8, 9,10,  8,10,11, // left
        12,13,14, 12,14,15, // right
        16,17,18, 16,18,19, // top
        20,21,22, 20,22,23, // bottom
    };

    Init(verts, 24, indices, 36, GL_TRIANGLES, GL_STATIC_DRAW);
};

void Mesh::CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint, vec2 uvRepeat)
{
    int numVerts = vertexCount.x * vertexCount.y;
    int numIndices = (vertexCount.x - 1) * (vertexCount.y - 1) * 6;

    

    VertexFormat* verts = new VertexFormat[numVerts];
    unsigned int* indices = new unsigned int[numIndices];

    float stepX = worldSize.x / ( vertexCount.y - 1 );
    float stepY = worldSize.y / ( vertexCount.y - 1 );

    float uvStepX = uvRepeat.x / ( vertexCount.y - 1 );
    float uvStepY = uvRepeat.y / ( vertexCount.y - 1 );

    for( int y = 0; y < vertexCount.y; y++ )
    {
        for( int x = 0; x < vertexCount.x; x++ )
        {
            verts[y * vertexCount.x + x].m_Pos.Set( x * stepX - pivotPoint.x, 0, y * stepY - pivotPoint.y );
            verts[y * vertexCount.x + x].m_UV.Set( x * uvStepX, y * uvStepY );
            verts[y * vertexCount.x + x].m_Normal.Set(0,1,0);

        }
    }

    for( int y = 0; y < vertexCount.y - 1; y++ )
    {
        for( int x = 0; x < vertexCount.x - 1; x++ )
        {
            int bottomLeftIndex = y * vertexCount.x + x;
            int elementIndex = ( y * (vertexCount.x-1) + x ) * 6;

            indices[ elementIndex + 0 ] = bottomLeftIndex + 0;
            indices[ elementIndex + 1 ] = bottomLeftIndex + vertexCount.x;
            indices[ elementIndex + 2 ] = bottomLeftIndex + vertexCount.x + 1;

            indices[ elementIndex + 3 ] = bottomLeftIndex + 0;
            indices[ elementIndex + 4 ] = bottomLeftIndex + vertexCount.x + 1;
            indices[ elementIndex + 5 ] = bottomLeftIndex + 1;
        }
    }

    Init( verts, numVerts, indices, numIndices, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateOBJ(const char* objFilename, vec3 scale)
{
    unsigned int numVerts = 0;
    unsigned int numIndices = 0;
    VertexFormat* verts = 0;
    unsigned int* indices = 0;

    LoadBasicOBJFromFile( objFilename, scale, &numVerts, &numIndices, &verts, &indices );

    Init( verts, numVerts, nullptr, 0, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateRing(float innerradius, float outerradius, int numsegments, MyColor color)
{
    int numverts = numsegments * 2;
    int numindices = numsegments * 6;

    VertexFormat* verts = new VertexFormat[numverts];
    unsigned int* indices = new unsigned int[numindices];

    for( int i=0; i<numsegments; i++ )
    {
        float angledeginc = 360.0f/numsegments;
        float angledeg = angledeginc * i;
        float anglerad = angledeg / 180.0f * PI;

        // outer
        verts[ i*2 + 0 ].m_Pos.x = cos( anglerad ) * outerradius;
        verts[ i*2 + 0 ].m_Pos.y = 0;
        verts[ i*2 + 0 ].m_Pos.z = sin( anglerad ) * outerradius;
        verts[ i*2 + 0 ].m_Color = color;

        // inner
        verts[ i*2 + 1 ].m_Pos.x = cos( anglerad ) * innerradius;
        verts[ i*2 + 1 ].m_Pos.y = 0;
        verts[ i*2 + 1 ].m_Pos.z = sin( anglerad ) * innerradius;
        verts[ i*2 + 1 ].m_Color = color;
    }

    for( int i=0; i<numsegments; i++ )
    {
        indices[ i*6 + 0 ] = i*2 + 0;
        indices[ i*6 + 1 ] = i*2 + 1;
        indices[ i*6 + 2 ] = i*2 + 3;

        indices[ i*6 + 3 ] = i*2 + 0;
        indices[ i*6 + 4 ] = i*2 + 3;
        indices[ i*6 + 5 ] = i*2 + 2;
    }

    // fix the last set of indices so they use the original verts.
    indices[ (numsegments-1)*6 + 2 ] = 1;
    indices[ (numsegments-1)*6 + 4 ] = 1;
    indices[ (numsegments-1)*6 + 5 ] = 0;    

    Init( verts, numverts, indices, numindices, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}

void Mesh::CreateArc(float outerradius, int degrees, int numsegments, MyColor color)
{
    int numverts = numsegments + 2;
    int numindices = numsegments * 3;

    VertexFormat* verts = new VertexFormat[numverts];
    unsigned int* indices = new unsigned int[numindices];

    float startdegrees = -(float)degrees/2;
    float degreeinc = (float)degrees / numsegments;

    verts[ 0 ].m_Pos.x = 0;
    verts[ 0 ].m_Pos.y = 0;
    verts[ 0 ].m_Pos.z = 0;
    verts[ 0 ].m_Color = color;

    verts[ 1 ].m_Pos.x = cos( startdegrees / 180.0f * PI ) * outerradius;
    verts[ 1 ].m_Pos.y = 0;
    verts[ 1 ].m_Pos.z = sin( startdegrees / 180.0f * PI ) * outerradius;
    verts[ 1 ].m_Color = color;

    for( int i=0; i<numsegments; i++ )
    {
        float angledeg = startdegrees + degreeinc * (i+1);
        float anglerad = angledeg / 180.0f * PI;

        verts[ 2 + i ].m_Pos.x = cos( anglerad ) * outerradius;
        verts[ 2 + i ].m_Pos.y = 0;
        verts[ 2 + i ].m_Pos.z = sin( anglerad ) * outerradius;
        verts[ 2 + i ].m_Color = color;
    }

    for( int i=0; i<numsegments; i++ )
    {
        indices[ i*3 + 0 ] = 0;
        indices[ i*3 + 1 ] = i+2;
        indices[ i*3 + 2 ] = i+1;
    }

    Init( verts, numverts, indices, numindices, GL_TRIANGLES, GL_STATIC_DRAW );

    delete[] verts;
    delete[] indices;
}
