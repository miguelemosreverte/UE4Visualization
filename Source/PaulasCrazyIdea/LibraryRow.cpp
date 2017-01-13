// Fill out your copyright notice in the Description page of Project Settings.

#include "PaulasCrazyIdea.h"
#include "LibraryRow.h"


// Sets default values
ALibraryRow::ALibraryRow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	//Asset, Reference Obtained Via Right Click in Editor
	// Create and position a mesh component so we can see where our sphere is
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
		 RootComponent = SphereComponent;
		 SphereComponent->InitSphereRadius(0.0f);
		 SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

		LibraryRowVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
		LibraryRowVisual->SetMobility(EComponentMobility::Movable);
		LibraryRowVisual->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> LibraryRowVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
		//static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished"));
		static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/Room/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished"));

		if (LibraryRowVisualAsset.Succeeded())
		{
				LibraryRowVisual->SetStaticMesh(LibraryRowVisualAsset.Object);
				LibraryRowVisual->SetMaterial(0, Material.Object);
				LibraryRowVisual->SetWorldScale3D(FVector(0.4f,2.2f,0.02f));

				/*
				UTextRenderComponent* TextRender = ConstructObject<UTextRenderComponent>(UTextRenderComponent::StaticClass(), this, FName(*(FString::Printf(TEXT("Debug Text Component %i"), (int32)i))));

	         TextRender->SetMobility(EComponentMobility::Movable);
	         TextRender->SetCastShadow(false);
	         TextRender->bCastDynamicShadow = false;
	         TextRender->bAffectDynamicIndirectLighting = false;

	         TextRender->SetMaterial(0, Material.Object);

					 TextRender->SetWorldScale3D(FVector(0.4f,8.0f,0.02f));
	         TextRender->SetText(FString::Printf(TEXT("Segment")));
	 				 TextRender->SetRelativeLocation(LibraryPositionOffset);
					  */
		}


}

// Called when the game starts or when spawned
void ALibraryRow::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALibraryRow::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ALibraryRow::maybeMove(UPARAM(ref) int32& newRowID)
{
	if (ID != newRowID)
	{
		if (Moved)
		{
			Moved = false;
			LibraryRowVisual->AddLocalOffset(FVector(50.0f,0.0f,0.0f));
		}
	}
	if (ID == newRowID)
	{
		if (!Moved)
		{
				Moved = true;
				LibraryRowVisual->AddLocalOffset(FVector(-50.0f,0.0f,0.0f));
		}
	}


}

void ALibraryRow::setID(UPARAM(ref) int32& newID)
{
	ID = newID;
}
int32 ALibraryRow::getID()
{
	return ID;
}
