#include "CCamera.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CApplication.h"
#include "CSceneManager.h"
#include "CMeshRenderer.h"

extern sh::CApplication application;

namespace sh
{
    bool  CompareZSort(CGameObject* a, CGameObject* b)
    {
        if (a->GetComponent<CTransform>()->GetPosition().z < b->GetComponent<CTransform>()->GetPosition().z)
        {
            return false;
        }
        return true;
    }

    Matrix CCamera::View = Matrix::Identity;
    Matrix CCamera::Projection = Matrix::Identity;

    CCamera::CCamera()
        : Component(eComponentType::Camera)
        , mType(eProjectionType::OrthoGraphic)
        //, mType(eProjectionType::Perspective)
        , mAspectRatio(1.0f)
        , mNear(1.0f)
        , mFar(1000.0f)
        , mSize(5.0f)
        , mLayerMask{}
        , mOpaqueGameObjects{}
        , mCutOutGameObjects{}
        , mTransparentGameObjects{}
        , mView(Matrix::Identity)
        , mProjection(Matrix::Identity)
    {
        EnableLayerMasks();
    }
    CCamera::~CCamera()
    {
    }
    void CCamera::Initialize()
    {

    }
    void CCamera::Update()
    {
    }
    void CCamera::LateUpdate()
    {
        CreateViewMatrix();
        CreateProjectionMatrix(mType);
        RegisterCameraInRenderer();
    }
    void CCamera::Render()
    {
        View = mView;
        Projection = mProjection;

        AlphaSortGameObjects();
        ZSortTransparencyGameObjects();

        RenderOpaque();

        DisableDepthStencilState();
        RenderCutOut();
        RenderTransparent();

        EnableDepthStencilState();
    }
    bool CCamera::CreateViewMatrix()
    {
        CTransform* tr = GetOwner()->GetComponent<CTransform>();
        Vector3 pos = tr->GetPosition();

        // View Translate Matrix
        mView = Matrix::Identity;
        mView *= Matrix::CreateTranslation(-pos);

        // View Rotation Matrix
        Vector3 up = tr->Up();
        Vector3 right = tr->Right();
        Vector3 forward = tr->Forward();

        Matrix viewRotate;
        viewRotate._11 = right.x;   viewRotate._12 = up.x;  viewRotate._13 = forward.x;
        viewRotate._21 = right.y;   viewRotate._22 = up.y;  viewRotate._23 = forward.y;
        viewRotate._31 = right.z;   viewRotate._32 = up.z;  viewRotate._33 = forward.z;

        mView *= viewRotate;

        return true;
    }
    bool CCamera::CreateProjectionMatrix(eProjectionType type)
    {
        RECT rect = {};
        GetClientRect(application.GetHwnd(), &rect);
        float width = float(rect.right - rect.left);
        float  height = float(rect.bottom - rect.top);
        mAspectRatio = (float)(width / height);

        if (type == eProjectionType::OrthoGraphic)
        {
            float OrthorGraphicRatio = mSize / 1000.0f;
            width *= OrthorGraphicRatio;
            height *= OrthorGraphicRatio;

            mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
        }
        else
        {
            mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
        }
    

        return true;
    }
    void CCamera::TurnLayerMask(eLayerType type, bool enable)
    {
        mLayerMask.set((UINT)type, enable);
    }
    void CCamera::RenderOpaque()
    {
        for (CGameObject* gameObj : mOpaqueGameObjects)
        {
            if (gameObj == nullptr)
            {
                continue;
            }
            gameObj->Render();
        }
    }
    void CCamera::RenderCutOut()
    {
        for (CGameObject* gameObj : mCutOutGameObjects)
        {
            if (gameObj == nullptr)
            {
                continue;
            }
            gameObj->Render();
        }
    }
    void CCamera::RenderTransparent()
    {
        for (CGameObject* gameObj : mTransparentGameObjects)
        {
            if (gameObj == nullptr)
            {
                continue;
            }
            gameObj->Render();
        }
    }
    void CCamera::RegisterCameraInRenderer()
    {
        render::cameras.push_back(this); // 여기에서 this 는 무엇인가
    }
   
    void CCamera::AlphaSortGameObjects()
    {
        mOpaqueGameObjects.clear();
        mCutOutGameObjects.clear();
        mTransparentGameObjects.clear();

        // alpha sorting
        CScene* scene = CSceneManager::GetActiveScene();
        for (size_t i = 0; i < (UINT)eLayerType::End; i++)
        {
            if (mLayerMask[i] == true)
            {
                CLayer& layer = scene->GetLayer((eLayerType)i);
                const std::vector<CGameObject*> gameObjs = layer.GetGameObjects();

                DivideAlphaBlendGameObjects(gameObjs);
            }
        }
    }
    void CCamera::ZSortTransparencyGameObjects()
    {
        std::sort(mCutOutGameObjects.begin(), mCutOutGameObjects.end(), CompareZSort);
        std::sort(mTransparentGameObjects.begin(), mTransparentGameObjects.end(), CompareZSort);
    }
    void CCamera::DivideAlphaBlendGameObjects(const std::vector<CGameObject*> gameObjs)
    {
        for (CGameObject* obj : gameObjs)
        {
            CMeshRenderer* mr = obj->GetComponent<CMeshRenderer>();
            if (mr == nullptr)
            {
                continue;
            }
            std::shared_ptr<CMaterial> mt = mr->GetMaterial();
            eRenderingMode mode = mt->GetRenderingMode();
            switch (mode)
            {
            case graphics::eRenderingMode::Opaque :
                mOpaqueGameObjects.push_back(obj);
                break;
            case graphics::eRenderingMode::CutOut :
                mCutOutGameObjects.push_back(obj);
                break;
            case graphics::eRenderingMode::Transparent :
                mTransparentGameObjects.push_back(obj);
                break;
            default:
                break;
            }
        }
    }
    void CCamera::EnableDepthStencilState()
    {
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState 
            = render::depthStencilStates[(UINT)eDSType::Less];
        GetDevice()->BindDepthStencilState(dsState.Get());
    }
    void CCamera::DisableDepthStencilState()
    {
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
            = render::depthStencilStates[(UINT)eDSType::None];
        GetDevice()->BindDepthStencilState(dsState.Get());
    }
}