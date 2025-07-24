#include "stdafx.h"
#include "GMDoppelGanger4.h"

CGMDoppelGanger4 g_DoppelGanger4;

CGMDoppelGanger4::CGMDoppelGanger4()
{

}

CGMDoppelGanger4::~CGMDoppelGanger4()
{

}

mu_boolean CGMDoppelGanger4::MoveObject(const mu_uint32 ThreadIndex, OBJECT* o)
{
	EVector3 Light;
	mu_float Luminosity;

	switch (o->Type)
	{
	case 47:
	case 48:
	case 59:
	case 62:
	case 81:
	case 82:
	case 83:
	case 107:
	case 108:
		o->HiddenMesh = -2;
		return true;
	case 44:
		o->Velocity = 0.02f;
		return true;
	case 46:
		o->Velocity = 0.01f;
		o->BlendMeshLight = (mu_float)EMath::Sin(FWorldTime*0.0015f)*0.8f + 1.0f;
		return true;
	case 60:
		Luminosity = (mu_float)(GetLargeRand(4) + 3) * 0.1f;
		Vector(Luminosity * 0.9f, Luminosity * 0.2f, Luminosity * 0.1f, Light);
		AddTerrainLight(o->Position[0], o->Position[1], Light, 3, PrimaryTerrainLight);
		o->HiddenMesh = -2;
		return true;
	case 61:
		Luminosity = (mu_float)(GetLargeRand(4) + 3) * 0.1f;
		Vector(Luminosity, Luminosity * 0.6f, Luminosity * 0.2f, Light);
		AddTerrainLight(o->Position[0], o->Position[1], Light, 3, PrimaryTerrainLight);
		o->HiddenMesh = -2;
		return true;
	case 70:
		o->Velocity = 0.04f;
		Luminosity = (mu_float)EMath::Sin(FWorldTime*0.002f)*0.45f + 0.55f;
		Vector(Luminosity*1.4f, Luminosity*0.7f, Luminosity*0.4f, Light);
		AddTerrainLight(o->Position[0], o->Position[1], Light, 4, PrimaryTerrainLight);
		return true;
	case 76:
		o->Alpha = 0.5f;
		return true;
	case 77:
		o->BlendMeshTexCoordV = -IWorldTime % 10000 * 0.0002f;
		return true;
	case 90:
		o->Velocity = 0.04f;
		return true;
	case 96:
		o->Alpha = 0.5f;
		return true;
	case 97:
		o->HiddenMesh = -2;
		o->Timer += 0.1f;
		if (o->Timer > 10.0f)
			o->Timer = 0.0f;
		if (o->Timer > 5.0f)
			CreateParticle(ThreadIndex, BITMAP_BUBBLE, o->Position, o->Angle, o->Light, 5);
		return true;
	case 102:
		o->BlendMeshLight = (mu_float)EMath::Sin(FWorldTime*0.0010f) + 1.0f;
		return true;
	}

	return false;
}

mu_boolean CGMDoppelGanger4::MoveMonsterVisual(const mu_uint32 ThreadIndex, OBJECT* o, MUModel* b)
{
	switch (o->Type)
	{
	case MODEL_MONSTER01 + 145:
		{
			switch (o->CurrentAction)
			{
			case MONSTER01_ATTACK2:
				if (o->AnimationFrame > 4.4f && o->AnimationFrame < 4.7f)
				{
					const mu_float ANG_REVISION = 20.0f;

					EVector3 v3Pos, v3Ang_, v3BasisPos;

					b->TransformByObjectBone(ThreadIndex, v3BasisPos, o, 8);

					VectorCopy(v3BasisPos, v3Pos);

					VectorCopy(o->Angle, v3Ang_);
					v3Ang_[0] = v3Ang_[0] + ANG_REVISION;

					CreateEffect(ThreadIndex, MODEL_STREAMOFICEBREATH, v3Pos, o->Angle, o->Light, 0, 0, -1, 0, 0, 0, 0.2f, -1);
				}
				break;
			case MONSTER01_DIE:
				{
					EVector3 vPos, vRelative;
					Vector(0.0f, 0.0f, 0.0f, vRelative);

					mu_float Scale = 3.5f;
					Vector(1.0f, 1.0f, 1.0f, o->Light);
					b->TransformByObjectBone(ThreadIndex, vPos, o, 6);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
					b->TransformByObjectBone(ThreadIndex, vPos, o, 79);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
				}
				break;
			}
		}
		return true;
	case MODEL_MONSTER01 + 189:
	case MODEL_MONSTER01 + 190:
		{
			if (o->CurrentAction == MONSTER01_STOP1 || o->CurrentAction == MONSTER01_STOP2 || o->CurrentAction == MONSTER01_ATTACK1 || o->CurrentAction == MONSTER01_ATTACK2)
				o->CurrentAction = MONSTER01_WALK;
		}
		return true;
	case MODEL_MONSTER01 + 191:
		if (o->CurrentAction == MONSTER01_APEAR)
		{
			if (o->AnimationFrame > 18.0f)
			{
				if (o->Flags.Get(OBJECT::eOF_ACTIONSTART) == false)
				{
					o->Flags.Set(OBJECT::eOF_ACTIONSTART);

					EVector3 vPos, vLight;
					mu_int32 i;

					for (i = 0; i < 6; ++i)
					{
						VectorCopy(o->Position, vPos);
						vPos[0] += (mu_float)(GetLargeRand(140) - 70);
						vPos[1] += (mu_float)(GetLargeRand(140) - 70);
						Vector(0.2f, 1.0f, 0.3f, vLight);
						CreateEffect(ThreadIndex, BITMAP_CLOUD, vPos, o->Angle, vLight, 0, NULL, -1, 0, 0, 0, 2.0f);
					}

					Vector(0.4f, 1.0f, 0.6f, vLight);
					for (i = 0; i < 3; ++i)
					{
						vPos[0] = o->Position[0] + (GetLargeRand(100) - 50)*1.0f;
						vPos[1] = o->Position[1] + (GetLargeRand(100) - 50)*1.0f;
						vPos[2] = o->Position[2] + 10.0f + (GetLargeRand(20))*10.0f;
						CreateParticle(ThreadIndex, BITMAP_EXPLOTION_MONO, vPos, o->Angle, vLight, 0, (GetLargeRand(8) + 7)*0.1f);
					}

					Vector(0.0f, 0.5f, 0.0f, vLight);
					for (i = 0; i < 15; ++i)
					{
						vPos[0] = o->Position[0] + (GetLargeRand(200) - 100)*1.0f;
						vPos[1] = o->Position[1] + (GetLargeRand(200) - 100)*1.0f;
						vPos[2] = o->Position[2] + (GetLargeRand(10))*10.0f;
						CreateEffect(ThreadIndex, MODEL_DOPPELGANGER_SLIME_CHIP, vPos, o->Angle, vLight, 0, o, 0, 0);
					}

					Vector(0.2f, 0.9f, 0.3f, vLight);
					for (i = 0; i < 30; ++i)
					{
						vPos[0] = o->Position[0] + (GetLargeRand(300) - 150)*1.0f;
						vPos[1] = o->Position[1] + (GetLargeRand(300) - 150)*1.0f;
						vPos[2] = o->Position[2] + 20.0f + (GetLargeRand(10))*10.0f;
						CreateParticle(ThreadIndex, BITMAP_SPARK + 1, vPos, o->Angle, vLight, 31);
					}

					Vector(0.8f, 1.0f, 0.8f, vLight);
					CreateParticle(ThreadIndex, BITMAP_SMOKE, o->Position, o->Angle, vLight, 54, 2.8f);

					SetAction(o, MONSTER01_ATTACK1);
				}
			}
		}
		return true;
	}

	return false;
}

void CGMDoppelGanger4::MoveBlurEffect(const mu_uint32 ThreadIndex, CHARACTER* pCharacter, OBJECT* pObject, MUModel* pModel)
{
	MUThreadInfo &ThreadInfo = g_ThreadInfo[ThreadIndex];

	switch(pObject->Type)
	{
	case MODEL_MONSTER01+189:
	case MODEL_MONSTER01+190:
		{
			if (!(pObject->CurrentAction == MONSTER01_WALK || pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2))
				break;

			EVector3  vLight;
			Vector(0.6f, 0.4f, 0.2f, vLight);

			EVector3 StartPos, StartRelative;
			EVector3 EndPos, EndRelative;
			
			mu_float fActionSpeed = pModel->_AnimationHeader[pObject->CurrentAction].Speed;
			mu_float fSpeedPerFrame = fActionSpeed/10.0;
			mu_float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
			for(mu_int32 i=0; i<10; ++i) 
			{
				pModel->Animation(ThreadIndex, ThreadInfo.BoneTransform, fAnimationFrame, pObject->PriorAnimationFrame, pObject->PriorAction, pObject->Angle, pObject->HeadAngle);

				Vector(0.0f, 0.0f, 0.0f, StartRelative);
				Vector(0.0f, 0.0f, 0.0f, EndRelative);
				pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(33)], StartRelative, StartPos, false);
				pModel->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[pModel->GetBoneIndex(34)], EndRelative, EndPos, false);
				CreateBlur(pCharacter, StartPos, EndPos, vLight, 0, false, 0);
				
				fAnimationFrame += fSpeedPerFrame;
			}
		}
		break;
	}
}

mu_boolean CGMDoppelGanger4::RenderObjectMesh(const mu_uint32 ThreadIndex, OBJECT* o, MUModel* b, mu_boolean ExtraMon)
{
	MUThreadInfo &ThreadInfo = g_ThreadInfo[ThreadIndex];

	mu_float fBlendMeshLight = 0;

	switch (o->Type)
	{
	case 19:
	case 20:
	case 31:
		b->RenderBody(ThreadIndex, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		return true;
	case 33:
		b->StreamMesh(ThreadIndex) = 0;
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, IWorldTime % 10000 * 0.0001f);
		b->StreamMesh(ThreadIndex) = -1;
		return true;
	case 103:
		{
			mu_float fLumi = (EMath::Sin(FWorldTime*0.002f) + 1.0f) * 0.5f;
			o->HiddenMesh = 1;
			b->RenderBody(ThreadIndex, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
			b->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, o->Alpha, 1, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		return true;
	case 76:
		{
			b->BodyLight(ThreadIndex)[0] = 0.52f;
			b->BodyLight(ThreadIndex)[1] = 0.52f;
			b->BodyLight(ThreadIndex)[2] = 0.52f;

			b->StreamMesh(ThreadIndex) = 0;
			b->RenderMesh(ThreadIndex,
				0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, o->BlendMesh,
				o->BlendMeshLight, -IWorldTime % 100000 * 0.00001f,
				o->BlendMeshTexCoordV);
			b->StreamMesh(ThreadIndex) = -1;
		}
		return true;
	case 95:
		{
			b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(ThreadIndex, 0, RENDER_CHROME | RENDER_DARK, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_CHROME);

			if(MU_UPDATECOUNTER > 0)
			{
				EVector3 p, Position, Light;
				for (mu_int32 i = 0; i < 10; ++i)
				{
					Vector(0.0f, 0.0f, 0.0f, p);
					b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(i)], p, Position, false);
					Vector(0.1f, 0.1f, 0.3f, Light);
					CreateSprite(BITMAP_SPARK + 1, Position, 7.5f, Light, o);
				}
			}
		}
		return true;
	case 105:
		{
			b->RenderBody(ThreadIndex, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
			b->RenderMesh(ThreadIndex, 1, RENDER_CHROME | RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_CHROME);
		}
		return true;
	case 77:
	case 91:
	case 92:
		{
			b->RenderBody(ThreadIndex, RENDER_TEXTURE, o->Alpha, o->BlendMesh,
				o->BlendMeshLight, o->BlendMeshTexCoordU,
				o->BlendMeshTexCoordV, o->HiddenMesh);
		}
		return true;
	case 142:
		b->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(ThreadIndex, 0, RENDER_BRIGHT | RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		return true;
	case MODEL_MONSTER01 + 145:
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_DOPPELGANGER_ICEWALKER0);
		b->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_DOPPELGANGER_ICEWALKER1);
		return true;
	case MODEL_MONSTER01 + 6:
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_DOPPELGANGER_SNAKE01);
		b->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		return true;
	case MODEL_MONSTER01 + 189:
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(ThreadIndex, 2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		fBlendMeshLight = (EMath::Sin(FWorldTime*0.003f) + 1.0f)*0.5f*0.8f;
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, 0, fBlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_BUGBEAR_R);
		return true;
	case MODEL_MONSTER01 + 190:
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(ThreadIndex, 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(ThreadIndex, 2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		fBlendMeshLight = (EMath::Sin(FWorldTime*0.003f) + 1.0f)*0.5f*0.8f;
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, 0, fBlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_BUGBEAR_R);
		return true;
	case MODEL_MONSTER01 + 191:
		if (o->Flags.Get(OBJECT::eOF_ACTIONSTART) == false)
		{
			b->RenderBody(ThreadIndex, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		}
		b->RenderMesh(ThreadIndex, 0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(ThreadIndex, 0, RENDER_CHROME | RENDER_BRIGHT, 0.3f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		return true;
	}

	return false;
}

mu_boolean CGMDoppelGanger4::RenderObjectVisual(const mu_uint32 ThreadIndex, OBJECT* o, MUModel* b)
{
	MUThreadInfo &ThreadInfo = g_ThreadInfo[ThreadIndex];

	EVector3 Light, p, Position;
	mu_float Luminosity;

	switch (o->Type)
	{
	case 37:
		{
			mu_int32 time = g_CurrentTime % 1024;
			if (time >= 0 && time < 10)
			{
				EVector3 Light;
				Vector(1.0f, 1.0f, 1.0f, Light);
				CreateEffect(ThreadIndex, MODEL_BUTTERFLY01, o->Position, o->Angle, Light, 3, o);
			}
			o->HiddenMesh = -2;
		}
		return true;
	case 47:
		{
			EVector3 vLight;
			Vector(0.1f, 0.4f, 1.0f, vLight);

			switch (GetLargeRand(3))
			{
			case 0:
				CreateParticle(ThreadIndex, BITMAP_FIRE_HIK1_MONO, o->Position, o->Angle, vLight, 2, o->Scale);
				break;
			case 1:
				CreateParticle(ThreadIndex, BITMAP_FIRE_HIK2_MONO, o->Position, o->Angle, vLight, 6, o->Scale);
				break;
			case 2:
				CreateParticle(ThreadIndex, BITMAP_FIRE_HIK3_MONO, o->Position, o->Angle, vLight, 2, o->Scale);
				break;
			}

			CreateParticle(ThreadIndex, BITMAP_FIRE_HIK1_MONO, o->Position, o->Angle, vLight, 2, o->Scale);
		}
		return true;
	case 48:
		if (GetLargeRand(3) == 0)
		{
			EVector3 Light, vPos;
			Vector(0.6f, 0.8f, 1.0f, Light);
			VectorCopy(o->Position, vPos);
			mu_int32 iScale = o->Scale * 60;
			vPos[0] += GetLargeRand(iScale) - iScale / 2;
			vPos[1] += GetLargeRand(iScale) - iScale / 2;
			CreateParticle(ThreadIndex, BITMAP_LIGHT, vPos, o->Angle, Light, 15, o->Scale, o);
		}
		return true;
	case 59:
		if (GetLargeRand(3) == 0)
		{
			Vector(1.0f, 1.0f, 1.0f, Light);
			CreateParticle(ThreadIndex, BITMAP_SMOKE, o->Position, o->Angle,
				Light, 13, o->Scale);
		}
		return true;
	case 61:
		if (GetLargeRand(3) == 0)
		{
			Vector(1.0f, 1.0f, 1.0f, Light);
			CreateParticle(ThreadIndex, BITMAP_TRUE_FIRE, o->Position, o->Angle,
				Light, 0, o->Scale);
		}
		return true;
	case 62:
		if (o->HiddenMesh != -2)
		{
			EVector3 Light;
			Vector(0.04f, 0.04f, 0.04f, Light);

			for (mu_int32 i = 0; i < 20; ++i)
				CreateParticle(ThreadIndex, BITMAP_CLOUD, o->Position, o->Angle, Light, 0, o->Scale, o);
		}
		o->HiddenMesh = -2;
		return true;
	case 70:
		Vector(0.0f, 0.0f, 0.0f, p);
		b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(6)], p, Position, false);
		Luminosity = (mu_float)EMath::Sin(FWorldTime*0.002f) + 1.8f;
		Vector(0.8f, 0.4f, 0.2f, Light);
		CreateSprite(BITMAP_SPARK + 1, Position, Luminosity * 7.0f, Light, o);
		Vector(0.65f, 0.65f, 0.65f, Light);
		CreateSprite(BITMAP_SPARK + 1, Position, Luminosity * 4.0f, Light, o);
		return true;
	case 81:
		Vector(1.0f, 1.0f, 1.0f, Light);
		if (GetLargeRand(2) == 0)
			CreateParticle(ThreadIndex, BITMAP_WATERFALL_1, o->Position, o->Angle, Light, 2, o->Scale);
		return true;
	case 82:
		Vector(1.0f, 1.0f, 1.0f, Light);
		CreateParticle(ThreadIndex, BITMAP_WATERFALL_3, o->Position, o->Angle, Light, 3, o->Scale);
		return true;
	case 83:
		Vector(1.0f, 1.0f, 1.0f, Light);
		if (GetLargeRand(3) == 0)
			CreateParticle(ThreadIndex, BITMAP_WATERFALL_2, o->Position, o->Angle, Light, 1, o->Scale);
		return true;
	case 85:
		b->RenderMesh(ThreadIndex, 3, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(ThreadIndex, 3, RENDER_CHROME | RENDER_DARK, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_CHROME);
		return true;
	case 92:
		{
			EVector3 EndRelative, StartPos, EndPos;
			Vector(0.0f, 0.0f, 0.0f, EndRelative);
			b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(1)], EndRelative, StartPos, false);
			b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(2)], EndRelative, EndPos, false);
			if (GetLargeRand(30) == 1)
				CreateJoint(ThreadIndex, BITMAP_JOINT_THUNDER, StartPos, EndPos, o->Angle, 8, NULL, 50.0f);
		}
		return true;
	case 98:
		{
			if (GetLargeRand(3) == 0)
			{
				EVector3 vPos;
				Vector(0.0f, 0.0f, 0.0f, vPos);
				b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(1)], vPos, Position, false);
				Vector(0.5f, 0.6f, 0.1f, Light);
				CreateParticle(ThreadIndex, BITMAP_TWINTAIL_WATER, Position, o->Angle, Light, 2);
			}
		}
		return true;
	case 105:
		{
			mu_float fLumi = (EMath::Sin(FWorldTime*0.001f) + 1.0f) * 0.5f;
			EVector3 vPos;
			Vector(0.0f, 0.0f, 0.0f, vPos);
			Vector(fLumi, fLumi, fLumi, Light);
			b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(4)], vPos, Position, false);
			CreateParticle(ThreadIndex, BITMAP_ENERGY, Position, o->Angle, Light, 0, 1.5f);
			CreateSprite(BITMAP_SPARK + 1, Position, 10.0f, Light, o);
			EVector3 StartPos, EndPos;
			VectorCopy(Position, StartPos);
			VectorCopy(Position, EndPos);
			StartPos[0] -= 50.0f;
			StartPos[0] -= GetLargeRand(100);
			EndPos[0] += GetLargeRand(80);
			StartPos[1] -= GetLargeRand(50);
			EndPos[1] += GetLargeRand(50);
			StartPos[2] += 10.0f;
			EndPos[2] += 10.0f;
			if (GetLargeRand(20) == 0)
			{
				CreateJoint(ThreadIndex, BITMAP_JOINT_THUNDER, StartPos, EndPos, o->Angle, 8, NULL, 40.0f);
			}
		}
		return true;
	case 107:
		if (o->HiddenMesh != -2)
		{
			EVector3  Light;
			Vector(0.06f, 0.06f, 0.06f, Light);
			for (mu_int32 i = 0; i < 20; ++i)
				CreateParticle(ThreadIndex, BITMAP_CLOUD, o->Position, o->Angle, Light, 2, o->Scale, o);
		}
		o->HiddenMesh = -2;
		return true;
	case 108:
		if (o->HiddenMesh != -2)
		{
			EVector3  Light;
			Vector(0.2f, 0.2f, 0.2f, Light);
			for (mu_int32 i = 0; i < 20; ++i)
				CreateParticle(ThreadIndex, BITMAP_CLOUD, o->Position, o->Angle, Light, 7, o->Scale, o);
		}
		o->HiddenMesh = -2;
		return true;
	case 110:
		{
			mu_float fLumi = (EMath::Sin(FWorldTime*0.002f) + 1.5f) * 0.5f;
			Vector(fLumi*0.6f, fLumi*1.0f, fLumi*0.8f, Light);
			EVector3 vPos;
			Vector(0.0f, 0.0f, 0.0f, vPos);
			b->TransformPosition(ThreadIndex, ThreadInfo.BoneTransform[b->GetBoneIndex(1)], vPos, Position, false);
			CreateSprite(BITMAP_LIGHT, Position, 1.1f, Light, o);
		}
		return true;
	}

	return false;
}

mu_boolean CGMDoppelGanger4::RenderMonsterVisual(const mu_uint32 ThreadIndex, CHARACTER* c, OBJECT* o, MUModel* b)
{
	EVector3 vPos, vLight;
	
	switch(o->Type)
	{
	case MODEL_MONSTER01+189:
	case MODEL_MONSTER01+190:
		if(GetLargeRand(4) == 0)
		{
			b->TransformByObjectBone(ThreadIndex, vPos, o, 6);
			vPos[1] += 50.0f;
			
			Vector(1.0f,1.0f,1.0f,vLight);
			CreateParticle(ThreadIndex, BITMAP_SMOKE, vPos, o->Angle, vLight, 61);
		}
		if(c->Dead==0 && GetLargeRand(4)==0)
		{
			Vector(o->Position[0]+(mu_float)(GetLargeRand(64)-32),
				o->Position[1]+(mu_float)(GetLargeRand(64)-32),
				o->Position[2]+(mu_float)(GetLargeRand(32)-16),vPos);
    			CreateParticle(ThreadIndex, BITMAP_SMOKE+1,vPos,o->Angle,vLight, 0);
		}

		if (o->Type == MODEL_MONSTER01+190)
		{
			Vector(1.0f,0.2f,0.1f,vLight);
			for (mu_int32 j = 0; j < 50; ++j)
			{
				if (j >= 0 && j <= 1) continue;
				if (j >= 12 && j <= 20) continue;
				if (j >= 24 && j <= 32) continue;
				if (j >= 35 && j <= 50) continue;
				b->TransformByObjectBone(ThreadIndex, vPos, o, j);
				CreateSprite ( BITMAP_LIGHT, vPos, 3.1f, vLight, o );
			}

			mu_float fScale = 0.8f;
			Vector(1.0f,1.0f,1.0f,vLight);
			for (mu_int32 i = 0; i < 30; ++i)
			{
				b->TransformByObjectBone(ThreadIndex, vPos, o, GetLargeRand(50));
				vPos[0] += GetLargeRand(10)-20;
				vPos[1] += GetLargeRand(10)-20;
				vPos[2] += GetLargeRand(10)-20;

 				switch(GetLargeRand(3))
				{
				case 0:
					CreateParticle(ThreadIndex, BITMAP_FIRE_HIK1,vPos,o->Angle,vLight,0,fScale);
					break;
				case 1:
					CreateParticle(ThreadIndex, BITMAP_FIRE_CURSEDLICH,vPos,o->Angle,vLight,4,fScale);
					break;
				case 2:
					CreateParticle(ThreadIndex, BITMAP_FIRE_HIK3,vPos,o->Angle,vLight,0,fScale);
					break;
				}
			}
		}
		return true;
	}

	return true;
}