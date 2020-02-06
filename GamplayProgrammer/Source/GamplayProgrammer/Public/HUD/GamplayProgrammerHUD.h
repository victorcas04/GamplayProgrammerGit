// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GamplayProgrammerHUD.generated.h"

UCLASS()
class AGamplayProgrammerHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGamplayProgrammerHUD() {}

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	/** Reticle asset pointer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Reticle 2DTexture")
		class UTexture2D* ReticleTex;

};

