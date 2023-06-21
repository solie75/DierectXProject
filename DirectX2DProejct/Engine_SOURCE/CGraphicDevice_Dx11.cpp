#include "CGraphicDevice_Dx11.h"
#include "CApplication.h"
#include "CRenderer.h"

extern sh::CApplication application;

namespace sh::graphics
{
	CGraphicDevice_Dx11::CGraphicDevice_Dx11()
	{
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf());

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
		{
			return;
		}

		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf())))
		{
			return;
		}

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

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		
		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&mViewPort);

		//mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
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
		return true;
	}

	bool CGraphicDevice_Dx11::CreateVertexShader(const void* pShaderByteCode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader)
	{
		if (!FAILED(mDevice->CreateVertexShader(pShaderByteCode, BytecodeLength, nullptr, ppVertexShader)))
		{
			return false;
		}
		return true;
	}
	bool CGraphicDevice_Dx11::CreatePixelShader(const void* pShaderByteCode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader)
	{
		if (!FAILED(mDevice->CreatePixelShader(pShaderByteCode, BytecodeLength, nullptr, ppPixelShader)))
		{
			return false;
		}
		return true;
	}
	bool CGraphicDevice_Dx11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDesc
		, UINT NumElement, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout)
	{
		if (!FAILED(mDevice->CreateInputLayout(pInputElementDesc, NumElement, byteCode->GetBufferPointer(), byteCode->GetBufferSize(), ppInputLayout)))
		{
			return false;
		}
		return true;
	}

	bool CGraphicDevice_Dx11::CreateSampler(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
		{
			return false;
		}

		return true;
	}

	void CGraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}

	void CGraphicDevice_Dx11::BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, 1, ppVertexBuffers, pStrides, pOffsets);
	}

	void CGraphicDevice_Dx11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	void CGraphicDevice_Dx11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}

	void CGraphicDevice_Dx11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
	{
		mContext->IASetPrimitiveTopology(Topology);
	}

	void CGraphicDevice_Dx11::SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		mContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, _data, size);
		mContext->Unmap(_buffer, 0);
	}
	void CGraphicDevice_Dx11::BindConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer)
	{
		switch (_stage)
		{
		case eShaderStage::VS :
			mContext->VSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)_type, 1, &_buffer);
		case eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)_type, 1, &_buffer);
			break;
		case eShaderStage::End:
			break;
		}
	}
	void CGraphicDevice_Dx11::BindsConstantBuffer(eShaderStage _stage, eCBType _type, ID3D11Buffer* _buffer)
	{
		mContext->VSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->HSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->DSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->GSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->PSSetConstantBuffers((UINT)_type, 1, &_buffer);
		mContext->CSSetConstantBuffers((UINT)_type, 1, &_buffer);
	}
	bool CGraphicDevice_Dx11::CompileFromFile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode)
	{
		ID3DBlob* errorBlob = nullptr;
		D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, funcName.c_str(), version.c_str(), 0, 0, ppCode, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)(errorBlob->GetBufferPointer()));
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return false;
	}
	

	void CGraphicDevice_Dx11::BindVertexShader(ID3D11VertexShader* pVertexShader)
	{
		mContext->VSSetShader(pVertexShader, 0, 0);
	}
	void CGraphicDevice_Dx11::BindPixelShader(ID3D11PixelShader* pPixelShader)
	{
		mContext->PSSetShader(pPixelShader, 0, 0);
	}

	void CGraphicDevice_Dx11::BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}

	void CGraphicDevice_Dx11::BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplerState)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetSamplers(StartSlot, 1, ppSamplerState);
			break;
		case eShaderStage::HS:
			mContext->HSSetSamplers(StartSlot, 1, ppSamplerState);
			break;
		case eShaderStage::DS:
			mContext->DSSetSamplers(StartSlot, 1, ppSamplerState);
			break;
		case eShaderStage::GS:
			mContext->GSSetSamplers(StartSlot, 1, ppSamplerState);
			break;
		case eShaderStage::PS:
			mContext->PSSetSamplers(StartSlot, 1, ppSamplerState);
			break;
		case eShaderStage::CS:
			mContext->CSSetSamplers(StartSlot, 1, ppSamplerState);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}

	void CGraphicDevice_Dx11::Draw()
	{
		//// rendertarget clear
		//FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		//mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		//mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

		//// viewport update
		//HWND hWnd = application.GetHwnd();
		//RECT winRect = {};
		//GetClientRect(hWnd, &winRect);
		//mViewPort = {
		//	0.0f, 0.0f
		//	, (float)(winRect.right - winRect.left)
		//	, (float)(winRect.bottom - winRect.top)
		//	, 0.0f, 1.0f
		//};

		//BindViewPort(&mViewPort);

		//mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		//render::RectangleMesh->BindBuffer();
		//render::shader->Binds();
		//graphics::GetDevice()->DrawIndexed(render::RectangleMesh->GetIndexCount(), 0, 0);
	}
	void CGraphicDevice_Dx11::Present()
	{
		mSwapChain->Present(0, 0);
	}
	void CGraphicDevice_Dx11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, int BaseVertexLocation)
	{
		mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}
	void CGraphicDevice_Dx11::ClearTarget()
	{
		// rendertarget clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}
	void CGraphicDevice_Dx11::UpdateViewPort()
	{
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
	}
}

