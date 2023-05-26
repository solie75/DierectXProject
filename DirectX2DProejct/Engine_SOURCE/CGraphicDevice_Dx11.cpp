#include "CGraphicDevice_Dx11.h"
#include "CApplication.h"
#include "CRenderer.h"

extern sh::CApplication application;

namespace sh::graphics
{
	CGraphicDevice_Dx11::CGraphicDevice_Dx11()
	{
		// Device, context ������
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0, D3D11_SDK_VERSION, mDevice.GetAddressOf(), &featureLevel, mContext.GetAddressOf());

		//  SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
		{
			return;
		}

		// SwapChian ���� ���� Rendertarget �� �����´�.
		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf())))
		{
			return;
		}

		// Rendertarget view ����
		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MiscFlags = 0;
		depthStencilDesc.MipLevels = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
		{
			return;
		}

		// ȭ�� ����
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		
		//mViewPort = {}
		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&mViewPort);

		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());


	}

	CGraphicDevice_Dx11::~CGraphicDevice_Dx11()
	{
	}

	bool CGraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hWnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = _hWnd;
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = _desc->BufferCount;
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = _desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = _desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1; 
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
		{
			return false;
		}
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
		{
			return false;
		}
		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
		{
			return false;
		}
		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
		{
			return false;
		}

		return true;
	}

	bool CGraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;
		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;
		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels;
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
		{
			return false;
		}
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
		{
			return false;
		}

		return true;
	}

	void CGraphicDevice_Dx11::Draw()
	{
		// rendertarget clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		
		// viewport update
		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		mViewPort = {
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};
		
		BindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		// ���� ������ ���� ����
		UINT vertexsize = sizeof(render::Vertex);
		UINT offset = 0;

		mContext->IASetVertexBuffers(0, 1, &render::triangleBuffer, &vertexsize, &offset);
		mContext->IASetIndexBuffer(render::indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		mContext->IASetInputLayout(render::triangleLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// Bind VS, PS
		mContext->VSSetShader(render::triangleVSShader, 0, 0);
		mContext->PSSetShader(render::trianglePSShader, 0, 0);

		// Draw Render target
		//mContext->DrawIndexed(6, 0, 0);
		mContext->DrawIndexed(1080, 0, 0);
		mSwapChain->Present(0, 0);
	}

	bool CGraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data)
	{
		if (FAILED(mDevice->CreateBuffer(_desc, _data, _buffer)))
		{
			return false;
		}

		return true;
	}
	bool CGraphicDevice_Dx11::CreateShader()
	{
		// VS shader ���

		ID3DBlob* vsBlob = nullptr;
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		// VS shader �������Ͽ� �������Ϸ� �����
		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0",
			0, 0, &sh::render::triangleVSBlob, &sh::render::errorBlob);

		// ���� ���� ������ VS shader �� ������ �ִ� ���
		if (sh::render::errorBlob)
		{
			OutputDebugStringA((char*)sh::render::errorBlob->GetBufferPointer());
			sh::render::errorBlob->Release();
		}

		// VS shader ����
		mDevice->CreateVertexShader(sh::render::triangleVSBlob->GetBufferPointer()
			, sh::render::triangleVSBlob->GetBufferSize(), nullptr, &sh::render::triangleVSShader);

		// PS shader ���
		//shaderPath = std::filesystem::current_path().parent_path();
		//shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path psPath(shaderPath.c_str());
		psPath += L"TrianglePS.hlsl";

		// PS shader �������Ͽ� �������Ϸ� �����
		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0",
			0, 0, &sh::render::trianglePSBlob, &sh::render::errorBlob);

		// ���� ���� ������ PS shader �� ������ �ִ� ���
		if (sh::render::errorBlob)
		{
			OutputDebugStringA((char*)sh::render::errorBlob->GetBufferPointer());
			sh::render::errorBlob->Release();
		}

		// PS shader ����
		mDevice->CreatePixelShader(sh::render::trianglePSBlob->GetBufferPointer(),
			sh::render::trianglePSBlob->GetBufferSize(), nullptr, &sh::render::trianglePSShader);

		// Input Layout �迭 ���� (���� ���� ������ �Ѱ��ֱ� ����)
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "Position";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "Color";
		arrLayout[1].SemanticIndex = 0;

		mDevice->CreateInputLayout(arrLayout, 2, render::triangleVSBlob->GetBufferPointer()
			, render::triangleVSBlob->GetBufferSize(), &render::triangleLayout);

		return true;
	}
	void CGraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}
}

