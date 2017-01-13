// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralSpheresCPP.generated.h"

UCLASS()
class PAULASCRAZYIDEA_API AProceduralSpheresCPP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralSpheresCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Output")
	void MoveSphereRow(int32 RowID);

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;



};
