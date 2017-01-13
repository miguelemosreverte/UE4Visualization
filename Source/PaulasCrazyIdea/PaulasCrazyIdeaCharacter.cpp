// Fill out your copyright notice in the Description page of Project Settings.

#include "PaulasCrazyIdea.h"
#include "PaulasCrazyIdeaCharacter.h"

#include "ProceduralSpheresCPP.h"
#include "PaulasSphere.h"
#include "Json.h"
#include <Engine.h>


// Sets default values
APaulasCrazyIdeaCharacter::APaulasCrazyIdeaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(25.f, 50.0f);


	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void APaulasCrazyIdeaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FString DocGenToolPath = TEXT("/Game/run_server.exe");

	FString pepe = FPaths::GameDir() + FString("Content/ResearchAnalyzer/visualization/executable/dist/run_cmd_from_exe");
	//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::White, FString::Printf(TEXT("%s"),*pepe));
	//FString Args = TEXT(" foo pepe");
		/*FString(TEXT("-outputdir=")) + TEXT("\"") + OutputDir + TEXT("\"")
		+ TEXT(" -fromintermediate -intermediatedir=") + TEXT("\"") + IntermediateDir + TEXT("\"")
		+ TEXT(" -name=") + DocTitle
		+ (bCleanOutput ? TEXT(" -cleanoutput") : TEXT(""))
		;*/
	Proc = FPlatformProcess::CreateProc(
		*pepe,
		nullptr,
		true,
		false,
		false,
		nullptr,
		0,
		nullptr,
		nullptr
	);

	if (Proc.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("It worked")));
	}
}
void APaulasCrazyIdeaCharacter::BeginDestroy()
{
	Super::BeginDestroy();
	if (Proc.IsValid())
	{
		FPlatformProcess::CloseProc(Proc);
	}
}

// Called every frame
void APaulasCrazyIdeaCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	TimeSinceLastTrace += DeltaTime;
	if (TimeSinceLastTrace >= 0.25f) {
		DoTrace();
		TimeSinceLastTrace = 0.0f;
	}

}

// Called to bind functionality to input
void APaulasCrazyIdeaCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &APaulasCrazyIdeaCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APaulasCrazyIdeaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APaulasCrazyIdeaCharacter::OnFire);
}

void APaulasCrazyIdeaCharacter::OnFire()
{
	APlayerController * PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController) {
		FVector Location;
		FRotator Rotation;
		PlayerController->GetPlayerViewPoint(Location, Rotation);
		//	const AActor* Camera = PlayerController->GetViewTarget();
		//	Camera->GetActorEyesViewPoint(Location, Rotation);
		const FVector TraceStart = Location;
		const FVector TraceEnd = TraceStart + Rotation.Vector() * Length;

		// AActor* Camera = PlayerController->GetViewTarget();
		const AActor * ActorToIgnore = nullptr;


		FCollisionQueryParams TraceParams(FName(TEXT("RayTracing")), true, ActorToIgnore);
		TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.bTraceComplex = true;

		FHitResult HitResult(ForceInit);

		const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);


		// Print out the name of the traced actor
		if (HitResult.GetActor())
		{


			APaulasSphere* APaulasSphereInstance = Cast<APaulasSphere>(HitResult.GetActor());

			if (IsValid(APaulasSphereInstance)) 
			{
				FVector ID = APaulasSphereInstance->getID();
				if (Data.Contains(ID))
				{
					LastClickedPaulasSphereID = APaulasSphereInstance->SphereVisual->GetComponentLocation() + FVector(0.0f, 0.0f, 5.0f);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sphere %d%d%d says Hello"), ID.X, ID.Y, ID.Z));
					ChangeURL(Data.Find(ID));
					
				}
			}
			else
			{
				LastClickedPaulasSphereID = FVector(0, 0, 0);
			}
			MaybeFocusedLibraryRow = Cast<ALibraryRow>(HitResult.GetActor());

			if (IsValid(MaybeFocusedLibraryRow)) 
			{
				if (Proc.IsValid())
				{

					FPlatformProcess::CloseProc(Proc);
				}
				int32 ID = MaybeFocusedLibraryRow->getID();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("library is valid, heres the ID %d"), ID));
				if (ID != FocusedLibraryRow)
				{
					for (TActorIterator<AProceduralSpheresCPP> Library(GetWorld()); Library; ++Library)
					{
						Library->MoveSphereRow(ID);
					}
					/*
					MaybeFocusedLibraryRow->moveForwards();
					if (FocusedLibraryRow != -1)
					{
					LastFocusedLibraryRow->moveBackwards();
					}
					else
					{
					FocusedLibraryRow = ID;
					}
					LastFocusedLibraryRow = MaybeFocusedLibraryRow;
					*/
				}
			}
		}
	}
}

void APaulasCrazyIdeaCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APaulasCrazyIdeaCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


TArray<FVector> APaulasCrazyIdeaCharacter::GetJSON(UPARAM(ref) int32& index) {
	Data.Empty();
	DataSentences.Empty();
	FString projectDir = FPaths::GameDir();
	projectDir += "/Content/data/UE4Ready_" + FString::FromInt(index) + ".json";
	//

	FString FileData = "TEST";
	FFileHelper::LoadFileToString(FileData, *projectDir);
	TSharedPtr <FJsonObject> JsonParsed;

	TSharedRef <TJsonReader <TCHAR>> JsonReader = TJsonReaderFactory <TCHAR> ::Create(FileData);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		auto nameEvents = JsonParsed->GetArrayField("data");
		auto group_names = JsonParsed->GetArrayField("groups_names");

		auto b = FString::FromInt(nameEvents.Num());

		FString groupsAmmountString = JsonParsed->GetStringField(TEXT("number_of_groups"));
		groupsAmmount = FCString::Atoi(*groupsAmmountString);

		maxY = FCString::Atoi(*JsonParsed->GetStringField(TEXT("maxY")));
		
		
		for (int32 i = 0; i < group_names.Num(); i++) {

			TSharedPtr <FJsonValue> value = group_names[i];
			FString groupName = value->AsString();
			GroupNames.Add(groupName);
		}

		for (int32 i = 0; i <nameEvents.Num(); i++) {
			TSharedPtr <FJsonValue> value = nameEvents[i];
			TSharedPtr <FJsonObject> json = value->AsObject();

			float X = FCString::Atof(*json->GetStringField(TEXT("X")));
			float Y = FCString::Atof(*json->GetStringField(TEXT("Y")));
			float Z = FCString::Atof(*json->GetStringField(TEXT("Z")));
			float tempX = X;
			FVector temp = FVector((Z*10000-10000)*20-20, tempX,Y*20-20);
			//UE_LOG(LogStats,Log,TEXT("temp %f %f %f "),temp.X,temp.Y,temp.Z);
			Data.Add(temp);
			SphereIDToIndexMap.Add(temp, i);
			FString EventContent = json->GetStringField(TEXT("sentence"));
			DataSentences.Add(EventContent);
			ClickOrSentence.Add(EventContent == "Click");


		}
	}
	else {
		if (index != 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("JSON KO")));
			UE_LOG(LogStats, Warning, TEXT("JSON KO"));
		}
	}
	return Data;

}


// Cast a ray accross the level
void APaulasCrazyIdeaCharacter::DoTrace() {
	// Find the actor that handles control for the local player.
	APlayerController * PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController) {
		FVector Location;
		FRotator Rotation;
		PlayerController->GetPlayerViewPoint(Location, Rotation);
		//	const AActor* Camera = PlayerController->GetViewTarget();
		//	Camera->GetActorEyesViewPoint(Location, Rotation);
		const FVector TraceStart = Location;
		const FVector TraceEnd = TraceStart + Rotation.Vector() * Length;

		// AActor* Camera = PlayerController->GetViewTarget();
		const AActor * ActorToIgnore = nullptr;


		FCollisionQueryParams TraceParams(FName(TEXT("RayTracing")), true, ActorToIgnore);
		TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.bTraceComplex = true;

		FHitResult HitResult(ForceInit);

		const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);


		// Print out the name of the traced actor
		if (HitResult.GetActor()) {


			APaulasSphere* APaulasSphereInstance = Cast<APaulasSphere>(HitResult.GetActor());

			if (IsValid(APaulasSphereInstance)) {
				FVector ID = APaulasSphereInstance->getID();				
				if (Data.Contains(ID))
				{
					if (ID != LastFocusedPaulasSphereID)
					{
						if (LastFocusedPaulasSphereID != FVector(0, 0, 0))
							LastFocusedPaulasSphere->changeMaterial();
						LastFocusedPaulasSphereID = ID;
						APaulasSphereInstance->changeMaterial();
						LastFocusedPaulasSphere = APaulasSphereInstance;

						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *DataSentences[SphereIDToIndexMap[ID]]));
					}
				}
			}
		}
	}
}
