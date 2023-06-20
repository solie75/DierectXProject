#pragma once
#include "CEngine.h"
#include "CGraphics.h"



namespace sh::graphics
{
	class CGraphicDevice_Dx11
	{
	public:
		CGraphicDevice_Dx11();
		~CGraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hWnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* _desc, void* _data);

		bool CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data);
		bool CreateShader();

		bool CreateVertexShader(const void* pShaderByteCode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderByteCode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDesc
			, UINT NumElement, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);
		
		void BindViewPort(D3D11_VIEWPORT* viewPort);
		void BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
		
		void SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT size);
		void BindConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer);
		void BindsConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer);

		bool CompileFromFile(const std::wstring& fileName, const std::string& funcName,
			const std::string& version, ID3DBlob** ppBlob);
		void BindVertexShader(ID3D11VertexShader* pVertexShader);
		void BindPixelShader(ID3D11PixelShader* pPixelShader);
		void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);

		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, int BaseVertexLocation);
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();

		ID3D11Device* GetID3D11Device() { return mDevice.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;
	};

	inline CGraphicDevice_Dx11*& GetDevice()
	{
		static CGraphicDevice_Dx11* device = nullptr;
		return device;
	}
}


