#pragma once
#include "CEngine.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace sh::graphics
{
	class CGraphicDevice_Dx11
	{
	public:
		CGraphicDevice_Dx11();
		~CGraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hWnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* _desc, void* _data);
		void Draw();
		bool CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data);
		bool CreateShader();
		void BindViewPort(D3D11_VIEWPORT* viewPort);

	private:
		// 실제 그래픽카드 하드웨어 객체
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		//  dx11에서 직접적으로 디바이스객체 접근하지않고
		// 이객체를 이용하여 명령을 내린다.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// 최종적으로 그려질 텍스처(도화지)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// 렌더타겟에 직접접근하지 않고 레더타겟뷰를 통해서 접근한다.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// 깊이버퍼
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// 깊이버퍼에 접근할수 있는 뷰
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// 더블버퍼링 작업을 진행해주는 swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;

	//public:
	//	ID3D11Device* GetDevice() { return mDevice.Get(); }
	};

	inline CGraphicDevice_Dx11*& GetDevice()
	{
		static CGraphicDevice_Dx11* device = nullptr;
		return device;
	}
}


