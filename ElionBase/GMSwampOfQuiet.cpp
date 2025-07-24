#include "stdafx.h"
#include "GMSwampOfQuiet.h"

mu_boolean GMSwampOfQuiet::MoveObject(OBJECT* pObject)
{
	mu_float Luminosity;
	EVector3 Light;

	switch(pObject->Type)
	{
	case 57:
		pObject->HiddenMesh = -2;
		Luminosity = (mu_float)(GetLargeRand(4)+3)*0.1f;
		Vector(Luminosity,Luminosity*0.6f,Luminosity*0.2f,Light);
		AddTerrainLight(pObject->Position[0], pObject->Position[1],Light,3,PrimaryTerrainLight);
		break;
	case 71:
		pObject->HiddenMesh = -2;
		break;
	case 72:
		pObject->HiddenMesh = -2;
		break;
	case 73:
		pObject->HiddenMesh = -2;
		break;
	case 74:
		pObject->HiddenMesh = -2;
		break;
	case 77:
		pObject->HiddenMesh = -2;
		break;
	case 78:
		pObject->HiddenMesh = -2;
		break;
	}
	return true;
}

mu_boolean GMSwampOfQuiet::RenderObjectVisual(const mu_uint32 ThreadIndex, OBJECT* pObject, MUModel* pModel)
{
	EVector3 Light;

	switch (pObject->Type)
	{
	case 57:
		{
			if (GetLargeRand(3) == 0)
			{
				Vector(1.0f, 1.0f, 1.0f, Light);
				CreateParticle(ThreadIndex, BITMAP_TRUE_FIRE, pObject->Position, pObject->Angle, Light, 5, pObject->Scale);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, pObject->Position, pObject->Angle, Light, 21, pObject->Scale);
			}
		}
		break;
	case 71:
		{
			if (GetLargeRand(3) == 0)
			{
				Vector(1.0f, 1.0f, 1.0f, Light);
				CreateParticle(ThreadIndex, BITMAP_TRUE_FIRE, pObject->Position, pObject->Angle, Light, 5, pObject->Scale);
			}
		}
		break;
	case 72:
		{
			if (GetLargeRand(6) == 0)
			{
				EVector3 Position;
				VectorCopy(pObject->Position, Position);
				Position[2] += 50.0f;

				Vector(0.03f, 0.03f, 0.03f, Light);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, Position, pObject->Angle, Light, 49, pObject->Scale);
			}
		}
		break;
	case 73:
		break;
	case 74:
		{
			if (GetLargeRand(3) == 0)
			{
				Vector(1.0f, 1.0f, 1.0f, Light);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, pObject->Position, pObject->Angle, Light, 21, pObject->Scale*2.0f);
			}
		}
		break;
	case 77:
		{
			if (GetLargeRand(6) == 0)
			{
				Vector(0.04f, 0.06f, 0.03f, Light);
				CreateParticle(ThreadIndex, BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 20, pObject->Scale, pObject);
			}
		}
		break;
	case 78:
		{
			if (GetLargeRand(6) == 0)
			{
				Vector(0.03f, 0.03f, 0.05f, Light);
				CreateParticle(ThreadIndex, BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 20, pObject->Scale, pObject);
			}
		}
		break;
	}

	return true;
}

mu_boolean GMSwampOfQuiet::RenderObject(const mu_uint32 ThreadIndex, OBJECT* pObject, MUModel* pModel, mu_boolean ExtraMon)
{
	if (pObject->Type >= MODEL_MONSTER01 + 139 && pObject->Type <= MODEL_MONSTER01 + 141)
	{
		if (pObject->CurrentAction == MONSTER01_DIE)
		{
			mu_float fLumi = 1.0f;
			if (pObject->AnimationFrame > 9.0f)
			{
				fLumi = (12.0f - pObject->AnimationFrame) / 3.0f;
			}

			switch (pObject->Type)
			{
			case MODEL_MONSTER01 + 139:
				Vector(1.0f, 0.2f, 0.2f, pModel->BodyLight(ThreadIndex));
				pModel->RenderMesh(ThreadIndex, 3, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 3, fLumi);
				break;
			case MODEL_MONSTER01 + 140:
				Vector(0.5f, 0.8f, 1.0f, pModel->BodyLight(ThreadIndex));
				pModel->RenderMesh(ThreadIndex, 3, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 3, fLumi);
				break;
			case MODEL_MONSTER01 + 141:
				Vector(0.5f, 1.0f, 0.5f, pModel->BodyLight(ThreadIndex));
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 4, fLumi);
				break;
			}
		}
		else
		{
			mu_float fLumi = (EMath::Sin(FWorldTime*0.002f) + 1.2f) * 0.5f * 1.0f;
			switch (pObject->Type)
			{
			case MODEL_MONSTER01 + 139:
				pModel->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 2, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 3, RENDER_TEXTURE, 0.7f, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 4, fLumi, 0, 0, BITMAP_SHADOW_PAWN_RED);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 4, fLumi, 0, 0, BITMAP_SHADOW_PAWN_RED);
				break;
			case MODEL_MONSTER01 + 140:
				pModel->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 2, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 3, RENDER_TEXTURE, 0.7f, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 4, fLumi, 0, 0, BITMAP_SHADOW_KINGHT_BLUE);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 4, fLumi, 0, 0, BITMAP_SHADOW_KINGHT_BLUE);
				break;
			case MODEL_MONSTER01 + 141:
				pModel->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 2, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 3, RENDER_TEXTURE, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 4, RENDER_TEXTURE, 0.7f, pObject->BlendMesh, pObject->BlendMeshLight);
				pModel->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 0, fLumi, 0, 0, BITMAP_SHADOW_ROOK_GREEN);
				pModel->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, pObject->Alpha, 0, fLumi, 0, 0, BITMAP_SHADOW_ROOK_GREEN);
				break;
			}
		}
	}
	else
		return false;

	return true;
}

CHARACTER* GMSwampOfQuiet::CreateSwampOfQuietMonster(mu_int32 iType, mu_int32 PosX, mu_int32 PosY, mu_int32 Key)
{
	CHARACTER* pCharacter = nullptr;

	switch (iType)
	{
	case 441:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 136, PosX, PosY);
		pCharacter->Object.Scale = 1.0f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 442:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 137, PosX, PosY);
		pCharacter->Object.Scale = 1.0f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 443:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 138, PosX, PosY);
		pCharacter->Object.Scale = 1.0f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 444:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 139, PosX, PosY);
		pCharacter->Object.Scale = 1.1f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		pCharacter->Object.LifeTime = 100;
		break;
	case 445:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 140, PosX, PosY);
		pCharacter->Object.Scale = 1.1f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		pCharacter->Object.LifeTime = 100;
		break;
	case 446:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 141, PosX, PosY);
		pCharacter->Object.Scale = 1.3f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		pCharacter->Object.LifeTime = 100;
		break;
	case 447:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 142, PosX, PosY);
		pCharacter->Object.Scale = 0.95f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 448:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 143, PosX, PosY);
		pCharacter->Object.Scale = 0.95f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 449:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 144, PosX, PosY);
		pCharacter->Object.Scale = 0.95f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 561:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 192, PosX, PosY);
		pCharacter->Object.Scale = 1.5f;
		pCharacter->Object.LifeTime = 100;
		break;
	case 557:
	case 560:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 201, PosX, PosY);
		pCharacter->Object.Scale = 1.5f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 558:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 202, PosX, PosY);
		pCharacter->Object.Scale = 1.1f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
	case 559:
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01 + 203, PosX, PosY);
		pCharacter->Object.Scale = 1.56f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		pCharacter->Object.LifeTime = 100;
		break;
	}

	return pCharacter;
}

mu_boolean GMSwampOfQuiet::MoveMonsterVisual(const mu_uint32 ThreadIndex, OBJECT* pObject, MUModel* pModel)
{
	switch (pObject->Type)
	{
	case MODEL_MONSTER01 + 142:
		if (pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			MUModel* pModel = &MODELS::Data[pObject->Type];
			mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
			mu_float Start_Frame = 7.2f;
			mu_float End_Frame = Start_Frame + fActionSpeed;
			if (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame < End_Frame)
			{
				EVector3 vLook, vPosition, vLight;
				EBone matRotate;
				Vector(1.0f, 1.0f, 1.0f, vLight);
				Vector(0.0f, -250.0f, 0.0f, vPosition);
				AngleMatrix(pObject->Angle, matRotate);
				VectorRotate(vPosition, matRotate, vLook);
				VectorAdd(pObject->Position, vLook, vPosition);

				CreateEffect(ThreadIndex, BITMAP_CRATER, vPosition, pObject->Angle, vLight, 2, nullptr, -1, 0, 0, 0, 1.5f);
				for (mu_int32 iu = 0; iu < 20; ++iu)
				{
					CreateEffect(ThreadIndex, MODEL_STONE2, vPosition, pObject->Angle, pObject->Light);
				}

				Vector(0.7f, 0.7f, 1.0f, vLight);
				CreateParticle(ThreadIndex, BITMAP_CLUD64, vPosition, pObject->Angle, vLight, 7, 2.0f);
				CreateParticle(ThreadIndex, BITMAP_CLUD64, vPosition, pObject->Angle, vLight, 7, 2.0f);

				Vector(0.3f, 0.2f, 1.0f, vLight);
				CreateEffect(ThreadIndex, BITMAP_SHOCK_WAVE, vPosition, pObject->Angle, vLight, 11);
				CreateEffect(ThreadIndex, BITMAP_SHOCK_WAVE, vPosition, pObject->Angle, vLight, 11);

				vPosition[2] += 100.0f;
				Vector(0.0f, 0.2f, 1.0f, vLight);
				CreateEffect(ThreadIndex, MODEL_EFFECT_THUNDER_NAPIN_ATTACK_1, vPosition, pObject->Angle, vLight, 0);
			}
		}
		break;
	case MODEL_MONSTER01 + 143:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			mu_float Start_Frame = 7.0f;
			mu_float End_Frame = Start_Frame + 0.8f;
			if (pObject->AnimationFrame >= Start_Frame)
			{
				EVector3 vLook, vPosition, vLight;
				EBone matRotate;
				Vector(0.4f, 1.0f, 0.4f, vLight);
				Vector(0.0f, -150.0f, 100.0f, vPosition);
				AngleMatrix(pObject->Angle, matRotate);
				VectorRotate(vPosition, matRotate, vLook);
				VectorAdd(pObject->Position, vLook, vPosition);

				EVector3 vSmokePosition;
				for (mu_int32 i = 0; i < 2; ++i)
				{
					Vector(vPosition[0] + (GetLargeRand(20) - 10)*1.0f,
						vPosition[1] + (GetLargeRand(20) - 10)*1.0f, vPosition[2] + (GetLargeRand(20) - 10)*1.0f, vSmokePosition);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vSmokePosition, pObject->Angle, vLight, 51);
				}
				if (pObject->AnimationFrame < End_Frame)
				{
					Vector(4.0f, 10.0f, 4.0f, vLight);
					CreateParticle(ThreadIndex, BITMAP_SHOCK_WAVE, vPosition, pObject->Angle, vLight, 3, 0.5f);
					CreateParticle(ThreadIndex, BITMAP_SHOCK_WAVE, vPosition, pObject->Angle, vLight, 3, 0.8f);
				}

				Vector(0.0f, -100.0f, 100.0f, vPosition);
				AngleMatrix(pObject->Angle, matRotate);
				VectorRotate(vPosition, matRotate, vLook);
				VectorAdd(pObject->Position, vLook, vPosition);
				CreateJoint(ThreadIndex, BITMAP_JOINT_ENERGY, vPosition, pObject->Position, pObject->Angle, 46, pObject, 20.0f);
			}
		}
		break;
	case MODEL_MONSTER01 + 144:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			MUModel* pModel = &MODELS::Data[pObject->Type];
			mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
			mu_float Start_Frame = 5.5f;
			mu_float End_Frame = Start_Frame + fActionSpeed;
			if (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame < End_Frame)
			{
				EVector3 vLook, vPosition, vLight, vLightFire;
				EBone matRotate;
				Vector(1.0f, 1.0f, 1.0f, vLight);
				Vector(1.0f, 0.2f, 0.0f, vLightFire);
				Vector(0.0f, -150.0f, 0.0f, vPosition);
				AngleMatrix(pObject->Angle, matRotate);
				VectorRotate(vPosition, matRotate, vLook);
				VectorAdd(pObject->Position, vLook, vPosition);

				CreateEffect(ThreadIndex, BITMAP_FIRE_CURSEDLICH, vPosition, pObject->Angle, vLight, 1, pObject);

				CreateEffect(ThreadIndex, BITMAP_CRATER, vPosition, pObject->Angle, vLight, 2, nullptr, -1, 0, 0, 0, 1.5f);
				for (mu_int32 iu = 0; iu < 20; ++iu)
				{
					CreateEffect(ThreadIndex, MODEL_STONE2, vPosition, pObject->Angle, pObject->Light);
				}

				Vector(0.5f, 0.1f, 0.0f, vLight);
				CreateEffect(ThreadIndex, BITMAP_SHOCK_WAVE, vPosition, pObject->Angle, vLight, 12, nullptr, -1, 0, 0, 0, 0.1f);
			}
		}
		break;
	case MODEL_MONSTER01 + 192:
		{
			EVector3 vPos, vColor;

			switch (pObject->CurrentAction)
			{
			case MONSTER01_WALK:
				Vector(pObject->Position[0] + GetLargeRand(200) - 100, pObject->Position[1] + GetLargeRand(200) - 100, pObject->Position[2], vPos);
				CreateParticle(ThreadIndex, BITMAP_SMOKE + 1, vPos, pObject->Angle, pObject->Light);
				break;

			case MONSTER01_ATTACK1:
			case MONSTER01_ATTACK2:
				if (2 < pModel->CurrentAnimationFrame(ThreadIndex))
				{
					EVector3 vAngle, vRel;
					VectorCopy(pObject->Angle, vAngle);
					Vector(10.0f, 5.0f, 0.0f, vRel);

					mu_int32 temp[] = { 19, 31 };
					for (mu_int32 i = 0; i < 2; ++i)
					{
						pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, temp[i], &vRel);

						Vector(0.0f, 1.0f, 0.5f, vColor);
						for (mu_int32 i = 0; i < 2; ++i)
						{
							if (i == 1 && GetLargeRand(2) == 0) continue;

							switch (GetLargeRand(3))
							{
							case 0:
								CreateParticle(ThreadIndex, BITMAP_FIRE_HIK1_MONO, vPos, vAngle, vColor, 4, pObject->Scale, pObject);
								break;
							case 1:
								CreateParticle(ThreadIndex, BITMAP_FIRE_HIK2_MONO, vPos, vAngle, vColor, 8, pObject->Scale, pObject);
								break;
							case 2:
								CreateParticle(ThreadIndex, BITMAP_FIRE_HIK3_MONO, vPos, vAngle, vColor, 5, pObject->Scale, pObject);
								break;
							}
						}

						Vector(1.0f, 1.0f, 1.0f, vColor);
						CreateSprite(BITMAP_HOLE, vPos, (EMath::Sin(FWorldTime*0.005f) + 1.0f)*0.1f + 0.1f, vColor, pObject);
					}
				}
				break;
			}
		}
		break;
	case MODEL_MONSTER01 + 202:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			MUModel* pModel = &MODELS::Data[pObject->Type];
			mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
			mu_float Start_Frame = 5.5f;
			mu_float End_Frame = Start_Frame + fActionSpeed;
			if (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame < End_Frame)
			{
				EVector3 vLook, vPosition, vLight, vLightFire;
				EBone matRotate;
				Vector(0.25f, 0.6f, 0.7f, vLight);
				Vector(1.0f, 1.0f, 1.0f, vLightFire);
				Vector(0.0f, -150.0f, 0.0f, vPosition);
				AngleMatrix(pObject->Angle, matRotate);
				VectorRotate(vPosition, matRotate, vLook);
				VectorAdd(pObject->Position, vLook, vPosition);

				CreateEffect(ThreadIndex, BITMAP_FIRE_CURSEDLICH, vPosition, pObject->Angle, vLight, 1, pObject);

				CreateEffect(ThreadIndex, BITMAP_CRATER, vPosition, pObject->Angle, vLight, 2, nullptr, -1, 0, 0, 0, 1.5f);
				for (mu_int32 iu = 0; iu < 20; ++iu)
				{
					CreateEffect(ThreadIndex, MODEL_STONE2, vPosition, pObject->Angle, pObject->Light);
				}

				Vector(0.5f, 0.1f, 0.0f, vLight);
				CreateEffect(ThreadIndex, BITMAP_SHOCK_WAVE, vPosition, pObject->Angle, vLight, 12, nullptr, -1, 0, 0, 0, 0.1f);
			}
		}
		break;
	}
	return false;
}

void GMSwampOfQuiet::MoveBlurEffect(const mu_uint32 ThreadIndex, CHARACTER* pCharacter, OBJECT* pObject, MUModel* pModel)
{
	MUThreadInfo &ThreadInfo = g_ThreadInfo[ThreadIndex];

	switch (pObject->Type)
	{
	case MODEL_MONSTER01 + 136:
		{
			mu_float Start_Frame = 6.0f;
			mu_float End_Frame = 7.6f;
			if ((pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK1)
				|| (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK2))
			{
				EVector3  vLight;
				Vector(1.0f, 0.6f, 0.1f, vLight);

				EVector3 StartPos, StartRelative;
				EVector3 EndPos, EndRelative;

				mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
				mu_float fSpeedPerFrame = fActionSpeed / 10.0;
				mu_float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
				for (mu_int32 i = 0; i < 10; ++i)
				{
					pModel->Animation(ThreadIndex, ThreadInfo.BoneTransform, fAnimationFrame, pObject->PriorAnimationFrame, pObject->PriorAction, pObject->Angle, pObject->HeadAngle);

					Vector(0.0f, 0.0f, 0.0f, StartRelative);
					Vector(0.0f, 0.0f, 0.0f, EndRelative);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(42)], StartRelative, StartPos, false);

					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(34)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 0);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(35)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 1);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(38)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 2);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(39)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 3);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(43)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 4);

					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
		break;
	case MODEL_MONSTER01 + 137:
		{
			mu_float Start_Frame = 6.0f;
			mu_float End_Frame = 7.0f;
			if ((pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK1)
				|| (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK2))
			{
				EVector3  vLight;
				Vector(2.0f, 0.0f, 0.0f, vLight);

				EVector3 StartPos, StartRelative;
				EVector3 EndPos, EndRelative;

				mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
				mu_float fSpeedPerFrame = fActionSpeed / 10.0;
				mu_float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
				for (mu_int32 i = 0; i < 10; ++i)
				{
					pModel->Animation(ThreadIndex, ThreadInfo.BoneTransform, fAnimationFrame, pObject->PriorAnimationFrame, pObject->PriorAction, pObject->Angle, pObject->HeadAngle);

					Vector(0.0f, 0.0f, 0.0f, StartRelative);
					Vector(0.0f, 0.0f, 0.0f, EndRelative);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(42)], StartRelative, StartPos, false);

					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(34)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 0);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(35)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 1);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(38)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 2);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(39)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 3);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(43)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 4);

					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
		break;
	case MODEL_MONSTER01 + 138:
		{
			mu_float Start_Frame = 5.0f;
			mu_float End_Frame = 10.0f;
			if ((pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK1)
				|| (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK2))
			{
				EVector3  vLight;
				Vector(0.3f, 0.7f, 1.0f, vLight);

				EVector3 StartPos, StartRelative;
				EVector3 EndPos, EndRelative;

				mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
				mu_float fSpeedPerFrame = fActionSpeed / 10.0;
				mu_float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
				for (mu_int32 i = 0; i < 10; ++i)
				{
					pModel->Animation(ThreadIndex, ThreadInfo.BoneTransform, fAnimationFrame, pObject->PriorAnimationFrame, pObject->PriorAction, pObject->Angle, pObject->HeadAngle);
					Vector(0.0f, 0.0f, 0.0f, StartRelative);
					Vector(0.0f, 0.0f, 0.0f, EndRelative);

					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(42)], StartRelative, StartPos, false);

					pModel->TransformByBoneMatrix(ThreadIndex, EndPos, ThreadInfo.BoneTransform[pModel->GetBoneIndex(34)]);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 0);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(35)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 1);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(38)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 2);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(39)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 3);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(43)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 4);

					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(75)], StartRelative, StartPos, false);

					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(76)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 5);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(79)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 6);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(80)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 7);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(83)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 8);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(84)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 9);

					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
		break;
	case MODEL_MONSTER01 + 142:
		break;
	case MODEL_MONSTER01 + 201:
	case MODEL_MONSTER01 + 204:
		{
			mu_float Start_Frame = 6.0f;
			mu_float End_Frame = 7.6f;
			if ((pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK1)
				|| (pObject->AnimationFrame >= Start_Frame && pObject->AnimationFrame <= End_Frame && pObject->CurrentAction == MONSTER01_ATTACK2))
			{
				EVector3  vLight;
				Vector(1.0f, 0.6f, 0.1f, vLight);

				EVector3 StartPos, StartRelative;
				EVector3 EndPos, EndRelative;

				mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
				mu_float fSpeedPerFrame = fActionSpeed / 10.0;
				mu_float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
				for (mu_int32 i = 0; i < 10; ++i)
				{
					pModel->Animation(ThreadIndex, ThreadInfo.BoneTransform, fAnimationFrame, pObject->PriorAnimationFrame, pObject->PriorAction, pObject->Angle, pObject->HeadAngle);

					Vector(0.0f, 0.0f, 0.0f, StartRelative);
					Vector(0.0f, 0.0f, 0.0f, EndRelative);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(42)], StartRelative, StartPos, false);

					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(34)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 0);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(35)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 1);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(38)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 2);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(39)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 3);
					pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(43)], EndRelative, EndPos, false);
					CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 4);

					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
		break;
	}
}		

mu_boolean GMSwampOfQuiet::RenderMonsterVisual(const mu_uint32 ThreadIndex, CHARACTER* pCharacter, OBJECT* pObject, MUModel* pModel)
{
	EVector3 vPos, vRelative, vLight;

	switch (pObject->Type)
	{
	case MODEL_MONSTER01 + 136:
		{
			Vector(1.0f, 0.6f, 0.1f, vLight);
			Vector(0.0f, 0.0f, 0.0f, vRelative);
			pModel->TransformPosition(ThreadIndex, pObject->BoneTransform[pModel->GetBoneIndex(15)], vRelative, vPos, true);

			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
		}
		break;
	case MODEL_MONSTER01 + 137:
		{
			Vector(1.0f, 0.0f, 0.0f, vLight);
			Vector(0.0f, 0.0f, 0.0f, vRelative);
			pModel->TransformPosition(ThreadIndex, pObject->BoneTransform[pModel->GetBoneIndex(15)], vRelative, vPos, true);

			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
		}
		break;
	case MODEL_MONSTER01 + 138:
		{
			Vector(0.2f, 0.7f, 1.0f, vLight);
			Vector(0.0f, 0.0f, 0.0f, vRelative);
			pModel->TransformPosition(ThreadIndex, pObject->BoneTransform[pModel->GetBoneIndex(15)], vRelative, vPos, true);

			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
		}
		break;
	case MODEL_MONSTER01 + 139:
		{
			mu_int32 iBones[] = { 11, 15, 34, 21, 25, 39 };
			Vector(1.0f, 0.1f, 0.1f, vLight);
			for (mu_int32 i = 0; i < 6; ++i)
			{
				if (GetLargeRand(6) > 0) continue;
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vLight, 50, 1.0f);
				CreateParticle(ThreadIndex, BITMAP_SMOKELINE1 + GetLargeRand(3), vPos, pObject->Angle, vLight, 0, 1.0f);
			}
		}
		if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (pObject->LifeTime == 100)
			{
				pObject->LifeTime = 90;

				EVector3 vWorldPos, Light;
				Vector(1.0f, 1.0f, 1.0f, Light);

				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 34);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_ANKLE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 39);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_ANKLE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 0);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_BELT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 4);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_CHEST, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 6);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_HELMET, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 33);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_KNEE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 38);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_KNEE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 13);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_WRIST_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 23);
				CreateEffect(ThreadIndex, MODEL_SHADOW_PAWN_WRIST_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
			}
		}
		break;
	case MODEL_MONSTER01 + 140:
		{
			mu_int32 iBones[] = { 11, 15, 34, 21, 25, 39 };
			Vector(0.3f, 0.6f, 1.0f, vLight);
			for (mu_int32 i = 0; i < 6; ++i)
			{
				if (GetLargeRand(6) > 0) continue;
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vLight, 50, 1.0f);
				CreateParticle(ThreadIndex, BITMAP_SMOKELINE1 + GetLargeRand(3), vPos, pObject->Angle, vLight, 0, 1.0f);
			}
		}
		if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (pObject->LifeTime == 100)
			{
				pObject->LifeTime = 90;

				EVector3 vWorldPos, Light;
				Vector(1.0f, 1.0f, 1.0f, Light);

				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 34);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_ANKLE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 39);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_ANKLE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 0);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_BELT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 4);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_CHEST, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 6);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_HELMET, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 33);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_KNEE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 38);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_KNEE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 13);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_WRIST_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 23);
				CreateEffect(ThreadIndex, MODEL_SHADOW_KNIGHT_WRIST_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
			}
		}
		break;
	case MODEL_MONSTER01 + 141:
		{
			mu_int32 iBones[] = { 11, 15, 34, 21, 25, 39 };
			Vector(0.5f, 1.0f, 0.5f, vLight);
			for (mu_int32 i = 0; i < 6; ++i)
			{
				if (GetLargeRand(6) > 0) continue;
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vLight, 50, 1.5f);
				CreateParticle(ThreadIndex, BITMAP_SMOKELINE1 + GetLargeRand(3), vPos, pObject->Angle, vLight, 0, 1.1f);
			}
		}
		if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (pObject->LifeTime == 100)
			{
				pObject->LifeTime = 90;

				EVector3 vWorldPos, Light;
				Vector(1.0f, 1.0f, 1.0f, Light);

				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 34);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_ANKLE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 39);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_ANKLE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 0);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_BELT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 4);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_CHEST, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 6);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_HELMET, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 33);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_KNEE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 38);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_KNEE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 12);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_WRIST_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 23);
				CreateEffect(ThreadIndex, MODEL_SHADOW_ROOK_WRIST_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
			}
		}
		break;
	case MODEL_MONSTER01 + 142:
		{
			mu_int32 iBones[] = { 7, 4, 5, 10, 22, 11, 23, 12, 24, 34, 39 };
			EVector3 vLightFlare;
			mu_float fScale;
			Vector(0.4f, 0.7f, 1.0f, vLight);
			Vector(0.1f, 0.2f, 1.0f, vLightFlare);
			for (mu_int32 i = 0; i < 11; ++i)
			{
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
				CreateSprite(BITMAP_LIGHT, vPos, 2.2f, vLightFlare, pObject);
				if (GetLargeRand(3) > 0) continue;
				Vector((GetLargeRand(30) - 15)*1.0f, (GetLargeRand(30) - 15)*1.0f, (GetLargeRand(30) - 15)*1.0f, vRelative);
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i], &vRelative);
				fScale = (mu_float)(GetLargeRand(80) + 32)*0.01f*1.0f;
				CreateParticle(ThreadIndex, BITMAP_LIGHTNING_MEGA1 + GetLargeRand(3), vPos, pObject->Angle, vLight, 0, fScale);
			}
		}
		break;
	case MODEL_MONSTER01 + 143:
		{
			mu_int32 iBones[] = { 21, 37, 65, 66, 77, 78, 79 };
			Vector(0.4f, 1.0f, 0.4f, vLight);
			for (mu_int32 i = 0; i < 7; ++i)
			{
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
				CreateParticle(ThreadIndex, BITMAP_SMOKELINE1 + GetLargeRand(3), vPos, pObject->Angle, vLight, 1, 1.0f, pObject);
				CreateParticle(ThreadIndex, BITMAP_CLUD64, vPos, pObject->Angle, vLight, 6, 1.0f, pObject);
			}
		}
		break;
	case MODEL_MONSTER01 + 144:
		{
			mu_int32 iBones[] = { 10, 61, 72, 21, 122, 116 };
			Vector(1.0f, 1.0f, 1.0f, vLight);
			EVector3 vLightFire;
			Vector(1.0f, 0.2f, 0.0f, vLightFire);
			for (mu_int32 i = 0; i < 6; ++i)
			{
				mu_float fScale = 1.2f;
				if (i >= 4)
				{
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
					CreateSprite(BITMAP_LIGHT, vPos, 1.0f, vLightFire, pObject);

					fScale = 0.7f;
					Vector((GetLargeRand(10) - 5)*1.0f, (GetLargeRand(10) - 5)*1.0f, (GetLargeRand(10) - 5)*1.0f, vRelative);
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i], &vRelative);

				}
				else
				{
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
					CreateSprite(BITMAP_LIGHT, vPos, 4.0f, vLightFire, pObject);

					Vector((GetLargeRand(20) - 10)*1.0f, (GetLargeRand(20) - 10)*1.0f, (GetLargeRand(20) - 10)*1.0f, vRelative);
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i], &vRelative);
				}

				switch (GetLargeRand(3))
				{
				case 0:
					CreateParticle(ThreadIndex, BITMAP_FIRE_HIK1, vPos, pObject->Angle, vLight, 0, fScale);
					break;
				case 1:
					CreateParticle(ThreadIndex, BITMAP_FIRE_CURSEDLICH, vPos, pObject->Angle, vLight, 4, fScale);
					break;
				case 2:
					CreateParticle(ThreadIndex, BITMAP_FIRE_HIK3, vPos, pObject->Angle, vLight, 0, fScale);
					break;
				}
			}
		}
		break;

	case MODEL_MONSTER01 + 192:
		{
			EVector3 vColor;
			Vector(1.0f, 1.0f, 1.0f, vColor);

			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 5);
			Vector(0.9f, 0.8f, 0.3f, vColor);
			CreateSprite(BITMAP_LIGHTMARKS, vPos, 2.0f, vColor, pObject);
			Vector(0.1f, 1.0f, 0.0f, vColor);
			CreateSprite(BITMAP_LIGHT, vPos, 2.4f, vColor, pObject);

			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 33);
			Vector(0.9f, 0.8f, 0.3f, vColor);
			CreateSprite(BITMAP_LIGHTMARKS, vPos, 1.2f, vColor, pObject);
			Vector(0.1f, 1.0f, 0.0f, vColor);
			CreateSprite(BITMAP_LIGHT, vPos, 1.4f, vColor, pObject);

			MoveEye(ThreadIndex, pObject, pModel, 34, 35);
			Vector(1.0f, 0.0f, 0.0f, vColor);
			CreateJoint(ThreadIndex, BITMAP_JOINT_ENERGY, vPos, pObject->Position, pObject->Angle, 55, pObject, 6.0f, -1, 0, 0, -1, &vColor);
			CreateJoint(ThreadIndex, BITMAP_JOINT_ENERGY, vPos, pObject->Position, pObject->Angle, 56, pObject, 6.0f, -1, 0, 0, -1, &vColor);

			Vector(1.0f, 1.0f, 1.0f, vColor);
			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 34);
			vPos[1] -= 0.8f;
			CreateSprite(BITMAP_LIGHT_RED, vPos, 0.4f, vColor, pObject);
			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 35);
			vPos[1] -= 0.8f;
			CreateSprite(BITMAP_LIGHT_RED, vPos, 0.4f, vColor, pObject);

			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 68);
			Vector(0.1f, 1.0f, 0.0f, vColor);
			CreateSprite(BITMAP_LIGHT, vPos, 4.0f, vColor, pObject);
			Vector(0.9f, 1.0f, 0.1f, vColor);
			CreateSprite(BITMAP_SHOCK_WAVE, vPos, 0.35f, vColor, pObject);
			Vector(0.9f, 1.0f, 0.1f, vColor);
			CreateSprite(BITMAP_SHOCK_WAVE, vPos, 0.22f, vColor, pObject);
			Vector(0.9f, 1.0f, 0.9f, vColor);
			CreateSprite(BITMAP_SHINY + 1, vPos, 1.2f, vColor, pObject);
			
			if (GetLargeRand(2) == 0)
			{
				CreateEffect(ThreadIndex, BITMAP_WATERFALL_4, vPos, pObject->Angle, vColor, 0, pObject, 68);
			}

			Vector(0.1f, 0.6f, 0.3f, vColor);
			CreateJoint(ThreadIndex, BITMAP_JOINT_ENERGY, vPos, pObject->Position, pObject->Angle, 57, pObject, 10.0f, 67, 0, 0, 15, &vColor);
			CreateJoint(ThreadIndex, BITMAP_JOINT_ENERGY, vPos, pObject->Position, pObject->Angle, 57, pObject, 10.0f, 70, 0, 0, 15, &vColor);
			
			Vector(1.0f, 1.0f, 1.0f, vColor);
			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 66);
			CreateSprite(BITMAP_LIGHT_RED, vPos, 0.4f, vColor, pObject);
			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 67);
			CreateSprite(BITMAP_LIGHT_RED, vPos, 0.4f, vColor, pObject);
			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 69);
			CreateSprite(BITMAP_LIGHT_RED, vPos, 0.4f, vColor, pObject);
			pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 70);
			CreateSprite(BITMAP_LIGHT_RED, vPos, 0.4f, vColor, pObject);

			mu_int32 temp[] = { 5, 37, 52 };
			Vector(0.25f, 1.0f, 0.0f, vColor);
			for (mu_int32 i = 0; i < 3; ++i)
			{
				if (GetLargeRand(6) > 0) continue;
				if (i % 5 == 0)
				{
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, temp[i]);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 50, 1.0f);
					CreateParticle(ThreadIndex, BITMAP_SMOKELINE1 + GetLargeRand(3), vPos, pObject->Angle, vColor, 0, 1.0f);
				}
			}

			if (pObject->CurrentAction == MONSTER01_DIE)
			{
				if (GetLargeRand(3) == 0)
				{
					Vector(0.4f, 0.9f, 0.6f, vColor);
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 0);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 1);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 1);

					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 5);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 1);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 1);

					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, 124);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 1);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vColor, 1);
				}
			}
		}
		break;

	case MODEL_MONSTER01 + 201:
	case MODEL_MONSTER01 + 204:
		{
			Vector(1.0f, 0.6f, 0.1f, vLight);
			Vector(0.0f, 0.0f, 0.0f, vRelative);
			pModel->TransformPosition(ThreadIndex, pObject->BoneTransform[pModel->GetBoneIndex(15)], vRelative, vPos, true);

			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
			CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLight, pObject);
		}
		break;
	case MODEL_MONSTER01 + 202:
		{
			mu_int32 iBones[] = { 10, 61, 72, 21, 122, 116 };
			Vector(1.0f, 1.0f, 1.0f, vLight);
			EVector3 vLightFire;
			Vector(1.0f, 1.0f, 1.0f, vLightFire);
			for (mu_int32 i = 0; i < 6; ++i)
			{
				mu_float fScale = 1.2f;
				if (i >= 4)
				{
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
					CreateSprite(BITMAP_LIGHT, vPos, 1.0f, vLightFire, pObject);

					fScale = 0.7f;
					Vector((GetLargeRand(10) - 5)*1.0f, (GetLargeRand(10) - 5)*1.0f, (GetLargeRand(10) - 5)*1.0f, vRelative);
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i], &vRelative);

				}
				else
				{
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
					CreateSprite(BITMAP_LIGHT, vPos, 4.0f, vLightFire, pObject);

					Vector((GetLargeRand(20) - 10)*1.0f, (GetLargeRand(20) - 10)*1.0f, (GetLargeRand(20) - 10)*1.0f, vRelative);
					pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i], &vRelative);
				}

				Vector(0.25f, 0.6f, 0.7f, vLight);

				switch (GetLargeRand(3))
				{
				case 0:
					CreateParticle(ThreadIndex, BITMAP_FIRE_HIK1, vPos, pObject->Angle, vLight, 0, fScale);
					break;
				case 1:
					CreateParticle(ThreadIndex, BITMAP_FIRE_CURSEDLICH, vPos, pObject->Angle, vLight, 4, fScale);
					break;
				case 2:
					CreateParticle(ThreadIndex, BITMAP_FIRE_HIK3, vPos, pObject->Angle, vLight, 0, fScale);
					break;
				}
			}
		}
		break;
	case MODEL_MONSTER01 + 203:
		{
			mu_int32 iBones[] = { 11, 15, 34, 21, 25, 39 };
			Vector(1.0f, 1.0f, 1.0f, vLight);
			for (mu_int32 i = 0; i < 6; ++i)
			{
				if (GetLargeRand(6) > 0) continue;
				pModel->TransformByObjectBone(ThreadIndex, vPos, pObject, iBones[i]);
				CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, pObject->Angle, vLight, 50, 1.5f);
				CreateParticle(ThreadIndex, BITMAP_SMOKELINE1 + GetLargeRand(3), vPos, pObject->Angle, vLight, 0, 1.1f);
			}
		}
		if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (pObject->LifeTime == 100)
			{
				pObject->LifeTime = 90;

				EVector3 vWorldPos, Light;
				Vector(1.0f, 1.0f, 1.0f, Light);

				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 34);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_ANKLE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 39);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_ANKLE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 0);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_BELT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 4);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_CHEST, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 6);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_HELMET, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 33);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_KNEE_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 38);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_KNEE_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 12);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_WRIST_LEFT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
				pModel->TransformByObjectBone(ThreadIndex, vWorldPos, pObject, 23);
				CreateEffect(ThreadIndex, MODEL_EX01_SHADOW_MASTER_WRIST_RIGHT, vWorldPos, pObject->Angle, Light, 0, pObject, 0, 0);
			}
		}
		break;
	}

	return false;
}

mu_boolean GMSwampOfQuiet::PlayMonsterSound(OBJECT* pObject)
{
	mu_float fDis_x, fDis_y;
	fDis_x = pObject->Position[0] - Hero->Object.Position[0];
	fDis_y = pObject->Position[1] - Hero->Object.Position[1];
	mu_float fDistance = EMath::Sqrt(fDis_x*fDis_x + fDis_y*fDis_y);

	if (fDistance > 500.0f) return true;

	switch (pObject->Type)
	{
	case MODEL_MONSTER01 + 136:
	case MODEL_MONSTER01 + 137:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			if (GetLargeRand(3) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_SAPI_UNUS_ATTACK01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (GetLargeRand(3) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_SAPI_DEATH01);
			}
		}
		return true;
	case MODEL_MONSTER01 + 138:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			if (GetLargeRand(3) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_SAPI_TRES_ATTACK01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (GetLargeRand(3) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_SAPI_DEATH01);
			}
		}
		return true;
	case MODEL_MONSTER01 + 139:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_PAWN_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 140:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_KNIGHT_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 141:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_ROOK_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 142:
		if (pObject->CurrentAction == MONSTER01_WALK)
		{
			if (GetLargeRand(100) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_THUNDER_NAIPIN_BREATH01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 143:
		if (pObject->CurrentAction == MONSTER01_WALK)
		{
			if (GetLargeRand(100) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_GHOST_NAIPIN_BREATH01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 144:
		if (pObject->CurrentAction == MONSTER01_WALK)
		{
			if (GetLargeRand(100) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_BLAZE_NAIPIN_BREATH01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 192:
		{

		}
		return true;
	case MODEL_MONSTER01 + 201:
	case MODEL_MONSTER01 + 204:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			if (GetLargeRand(3) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_SAPI_UNUS_ATTACK01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			if (GetLargeRand(3) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_SAPI_DEATH01);
			}
		}
		return true;
	case MODEL_MONSTER01 + 202:
		if (pObject->CurrentAction == MONSTER01_WALK)
		{
			if (GetLargeRand(100) == 0)
			{
				PlayBackground(SOUND_SWAMPOFQUIET_BLAZE_NAIPIN_BREATH01);
			}
		}
		else if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_NAIPIN_DEATH01);
		}
		return true;
	case MODEL_MONSTER01 + 203:
		if (pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_ROOK_ATTACK01);
		}
		else if (pObject->CurrentAction == MONSTER01_DIE)
		{
			PlayBackground(SOUND_SWAMPOFQUIET_SHADOW_DEATH01);
		}
		return true;
	}

	return false;
}

mu_boolean GMSwampOfQuiet::SetCurrentActionMonster(CHARACTER* pCharacter, OBJECT* pObject)
{
	switch (pObject->Type)
	{
	case MODEL_MONSTER01 + 192:
		{
			switch (pCharacter->Skill)
			{
			case AT_SKILL_BLAST_POISON:
				{
					SetAction(pObject, MONSTER01_ATTACK2);
					pCharacter->MonsterSkill = -1;
				}
				break;
			case AT_SKILL_GAOTIC:
				{
					SetAction(pObject, MONSTER01_ATTACK2);
					pCharacter->MonsterSkill = -1;
				}
				break;
			case AT_SKILL_GIGANTIC_STORM:
				{
					SetAction(pObject, MONSTER01_ATTACK3);
					pCharacter->MonsterSkill = -1;
				}
				break;
			case AT_SKILL_EVIL:
				{
					SetAction(pObject, MONSTER01_ATTACK1);
					pCharacter->MonsterSkill = -1;
				}
				break;
			default:
				{
					SetAction(pObject, MONSTER01_ATTACK1);
					pCharacter->MonsterSkill = -1;
				}
				break;
			}
		}
		return true;
	case MODEL_MONSTER01 + 201:
	case MODEL_MONSTER01 + 204:
		{
			if (pCharacter->MonsterSkill == ATMON_SKILL_EX_SAPIQUEEN_ATTACKSKILL)
			{
				SetAction(pObject, MONSTER01_ATTACK2);
				pCharacter->MonsterSkill = -1;
			}
			else
			{
				SetAction(pObject, MONSTER01_ATTACK1);
				pCharacter->MonsterSkill = -1;
			}
			return true;
		}
		return true;
	case MODEL_MONSTER01 + 202:
		{
			if (pCharacter->MonsterSkill == ATMON_SKILL_EX_ICENAPIN_ATTACKSKILL)
			{
				SetAction(pObject, MONSTER01_ATTACK2);
				pCharacter->MonsterSkill = -1;
			}
			else
			{
				SetAction(pObject, MONSTER01_ATTACK1);
				pCharacter->MonsterSkill = -1;
			}
			return true;
		}
		return true;
	case MODEL_MONSTER01 + 203:
		{
			if (pCharacter->MonsterSkill == ATMON_SKILL_EX_SHADOWMASTER_ATTACKSKILL)
			{
				SetAction(pObject, MONSTER01_ATTACK2);
				pCharacter->MonsterSkill = -1;
			}
			else
			{
				SetAction(pObject, MONSTER01_ATTACK1);
				pCharacter->MonsterSkill = -1;
			}
			return true;
		}
		return true;
	}

	return false;
}