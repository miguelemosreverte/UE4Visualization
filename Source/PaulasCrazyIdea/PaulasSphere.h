// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaulasSphere.generated.h"

UCLASS()
class PAULASCRAZYIDEA_API APaulasSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APaulasSphere();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaulasSpheres)
	UStaticMeshComponent* SphereVisual;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaulasSpheres)
	UMaterial* StandardSphereMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaulasSpheres)
	UMaterial* OrangeSphereMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaulasSpheres)
	UMaterial* HighlightSphereMaterial;

	bool Moved = false;
	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	void maybeMove(UPARAM(ref) int32& newRowID);

	FVector ID;
	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	void setID(UPARAM(ref) FVector& newID);
	FVector getID();

	int32 RowID;
	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	void setRowID(UPARAM(ref) int32& newRowID);

	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	int32 getRowID();

	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	void changeMaterial();

	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	void changeMaterialOriginal();

	UFUNCTION(BlueprintCallable, Category = PaulasSpheres)
	void changeMaterialToHighlightVersion();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaulasSpheres)
	FVector LibraryPositionOffset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UStaticMeshComponent* JoyfulControl;
	UStaticMesh * AssetSM_JoyControl;

	FORCEINLINE void SetupSMComponentsWithCollision(UStaticMeshComponent* Comp)
	{
		if(!Comp) return;
		//~~~~~~~~

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Block);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Block);
		Comp->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Block);
		Comp->SetHiddenInGame(false);
	}

};
