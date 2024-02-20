#pragma once

#include "GameComponent.h"

class TriangleComponent :
    public GameComponent
{
public:
    TriangleComponent();

    void Initialize() ;
    void DestroyResources() ;
    void Update() ;
    void Draw() ;
    
    ID3D11Buffer* vb;
    ID3D11Buffer* ib;
    ID3D11RasterizerState* rastState;
    DirectX::XMFLOAT4 points[6];


private:
    void InitVertex();
    void InitPixel();
    void InitLayout();

private:
    ID3DBlob* vertexBC;
    ID3DBlob* pixelBC;

    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;

    ID3D11InputLayout* layout;

};

