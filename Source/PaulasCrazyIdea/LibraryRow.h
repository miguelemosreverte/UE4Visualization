// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LibraryRow.generated.h"

UCLASS()
class PAULASCRAZYIDEA_API ALibraryRow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALibraryRow();


UStaticMeshComponent* LibraryRowVisual;

	bool Moved = false;
	UFUNCTION(BlueprintCallable, Category = PaulasLibrary)
	void maybeMove(UPARAM(ref) int32& newRowID);

	int32 ID;
	UFUNCTION(BlueprintCallable, Category = PaulasLibrary)
	void setID(UPARAM(ref) int32& newID);
	UFUNCTION(BlueprintCallable, Category = PaulasLibrary)
	int32 getID();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaulasLibrary)
	FVector LibraryPositionOffset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


};
