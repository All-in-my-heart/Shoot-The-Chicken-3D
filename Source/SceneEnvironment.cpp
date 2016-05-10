#include "Game.h"

using namespace GamePlay;

void ISceneModelManager::Init(SCENE_MODEL_ID model)
{

	//------------------Init Art Resources------------------
	mDefaultMaterial.ambient = { 0.5f,0.5f,0.5f };
	mDefaultMaterial.diffuse = { 1.0f,1.0f,1.0f };
	mDefaultMaterial.specular = { 1.0f,1.0f,1.0f };
	mDefaultMaterial.specularSmoothLevel = 20;


	//-----------SKY-DOME---------------------------
	switch (UINT(model))
	{
	case SCENE_MODEL_ID::SCENEMODEL_COSMOS1:
		//sky texture
		mSkyTexture.LoadPPM("Media/universe.ppm");

		//sky dome
		mSkyModel.CreateSphere(2000.0f,20,20,TRUE);
	
		for (UINT i = 0;i < c_asteroidCount;++i)
		{
			mAsteroid[i].Init((i % 3));
		}
		break;

	default:
		DEBUG_MSG1("Scene Model ID Invalid!!");
		break;
	};

	mSkyModel.SetPosition(0, 0, 0);
	mSkyModel.SetMaterial(mDefaultMaterial);
	mSkyModel.SetTexture(&mSkyTexture);

	//-----------------Lights----------------------
	mSceneLight.mAmbientColor = { 1.0f,1.0f,1.0f };
	mSceneLight.mDiffuseColor = { 1.0f,1.0f,1.0f };
	mSceneLight.mDiffuseIntensity = 1.0f;
	mSceneLight.mDirection = { -1.0f,-1.0f,-1.0f };
	mSceneLight.mIsEnabled = TRUE;
	mSceneLight.mSpecularColor = { 1.0f,1.0f,1.0f };
	mSceneLight.mSpecularIntensity = 1.2f;
	
	gRenderer.SetLight(0, mSceneLight);

	//-----------------Init Cursor--------------------
	::SetCursorPos(0, 0);
}

void ISceneModelManager::Update()
{
	VECTOR3 pos = gCamera.GetPosition();
	mSkyModel.SetPosition(pos.x, pos.y, pos.z);
	for (UINT i = 0;i < c_asteroidCount;i++)mAsteroid[i].Update();
}

void ISceneModelManager::Render()
{
	gRenderer.RenderMesh(mSkyModel);
	for (UINT i = 0;i < c_asteroidCount;i++)mAsteroid[i].Render();
}