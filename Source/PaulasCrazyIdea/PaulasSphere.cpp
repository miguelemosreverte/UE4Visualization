// Fill out your copyright notice in the Description page of Project Settings.

#include "PaulasCrazyIdea.h"
#include "PaulasSphere.h"


// Sets default values
APaulasSphere::APaulasSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Asset, Reference Obtained Via Right Click in Editor
	// Create and position a mesh component so we can see where our sphere is
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
     RootComponent = SphereComponent;
     SphereComponent->InitSphereRadius(0.08f);
     SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	  SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
		SphereVisual->SetMobility(EComponentMobility::Movable);
    SphereVisual->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
		static ConstructorHelpers::FObjectFinder<UMaterial> Material1(TEXT("/Game/Procedural/Materials/StandardSphereMaterial.StandardSphereMaterial"));
		static ConstructorHelpers::FObjectFinder<UMaterial> Material2(TEXT("/Game/Procedural/Materials/OrangeSphereMaterial.OrangeSphereMaterial"));
		StandardSphereMaterial = Material1.Object;
		OrangeSphereMaterial = Material2.Object;

		if (SphereVisualAsset.Succeeded())
    {
        SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetMaterial(0, Material1.Object);
		SphereVisual->SetRelativeLocation(FVector(35.0f,0.0f,22.0f));
        SphereVisual->SetWorldScale3D(FVector(0.08f));
    }

}

// Called when the game starts or when spawned
void APaulasSphere::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APaulasSphere::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}




void APaulasSphere::maybeMove(UPARAM(ref) int32& newRowID)
{
	if (RowID != newRowID)
	{
		if (Moved)
		{
			Moved = false;
			SphereVisual->SetWorldLocation(SphereVisual->GetComponentLocation() + FVector(50.0f, 0.0f, 0.0f));
			//SphereVisual->GetComponentLocation();
			
			//(FVector(50.0f,0.0f,0.0f));
		}
	}
	if (RowID == newRowID)
	{
		if (!Moved)
		{
				Moved = true;
				SphereVisual->SetWorldLocation(SphereVisual->GetComponentLocation() + FVector(-50.0f, 0.0f, 0.0f));
				//SphereVisual->AddLocalOffset(FVector(-50.0f,0.0f,0.0f));
		}
	}
}

void APaulasSphere::setID(UPARAM(ref) FVector& newID)
{
	ID = newID;
}
FVector APaulasSphere::getID()
{
	return ID;
}


void APaulasSphere::setRowID(UPARAM(ref) int32& newRowID)
{
	RowID = newRowID;
}
int32 APaulasSphere::getRowID()
{
	return RowID;
}

void APaulasSphere::changeMaterialToHighlightVersion()
{
	SphereVisual->SetMaterial(0, HighlightSphereMaterial);
}
void APaulasSphere::changeMaterialOriginal()
{
		SphereVisual->SetMaterial(0, StandardSphereMaterial);
}

void APaulasSphere::changeMaterial()
{
	if (SphereVisual->GetMaterial(0) == OrangeSphereMaterial)
	{
		SphereVisual->SetMaterial(0, StandardSphereMaterial);
	}
	else
	{
		SphereVisual->SetMaterial(0, OrangeSphereMaterial);
	}

}
