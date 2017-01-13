// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class PAULASCRAZYIDEA_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	
	
	
	
};
