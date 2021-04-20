// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Building_EscapeHUD.generated.h"

UCLASS()
class ABuilding_EscapeHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABuilding_EscapeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

