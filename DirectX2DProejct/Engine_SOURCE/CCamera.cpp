#include "CCamera.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CApplication.h"

extern sh::CApplication application;

namespace sh
{
    Matrix CCamera::mView = Matrix::Identity;
    Matrix CCamera::mProjection = Matrix::Identity;

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
    {
    }
    CCamera::~CCamera()
    {
    }
    void CCamera::Initialize()
    {
        EnableLayerMasks();
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
        SortGameObjects();

        RenderOpaque();
        RenderCutOut();
        RenderTransparent();
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
        float width = rect.right - rect.left;
        float height = rect.bottom - rect.top;
        mAspectRatio = width / height;

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
    void CCamera::SortGameObjects()
    {
    }
}