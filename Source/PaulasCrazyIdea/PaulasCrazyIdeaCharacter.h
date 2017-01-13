// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LibraryRow.h"
#include "PaulasSphere.h"
#include "PaulasCrazyIdeaCharacter.generated.h"

UCLASS()
class PAULASCRAZYIDEA_API APaulasCrazyIdeaCharacter : public ACharacter
{
	GENERATED_BODY()

		/** First person camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;


		// Lenght of ray tracing. Defaults to 10m.
		UPROPERTY(EditAnywhere)
			float Length = 1000.f;

		// Cast a ray accross the level
		float TimeSinceLastTrace = 0.0f;
		int32 FocusedLibraryRow = -1;
		FVector LastFocusedPaulasSphereID = FVector(0, 0, 0);
		ALibraryRow* LastFocusedLibraryRow;
		ALibraryRow* MaybeFocusedLibraryRow;
		FProcHandle Proc;

		UPROPERTY(VisibleAnywhere)
		APaulasSphere* LastFocusedPaulasSphere;
public:
	// Sets default values for this character's properties
	APaulasCrazyIdeaCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	void DoTrace();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Starts an analytics session without any custom attributes specified */


	UFUNCTION(BlueprintCallable, Category = "JSON")
		TArray<FVector> GetJSON(UPARAM(ref) int32& index);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FVector> Data;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<bool> ClickOrSentence;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 maxY;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int defaultClusteringOption;//0 to 9

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int ammountOfNeighboors;//0 to 9
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 groupsAmmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector LastClickedPaulasSphereID = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FString> DataSentences;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FString> GroupNames;
	TMap<FVector, int32>SphereIDToIndexMap;

	UFUNCTION(BlueprintImplementableEvent, Category = "Output")
		void ChangeURL(int32 RowID);
protected:

	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	
};
