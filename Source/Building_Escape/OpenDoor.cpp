// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw; 
	TargetYaw = InitialYaw + 90.f;
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > 50.f)
	{
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		OpenAndCloseDoor(DeltaTime, true);
	}
	else 
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			OpenAndCloseDoor(DeltaTime, false);
		}
	}
}
	

void UOpenDoor::OpenAndCloseDoor(float DeltaTime, bool open) 
{
	float currentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator openDoor(0.f, 0.f, 0.f); 
	openDoor.Yaw = FMath::Lerp(currentYaw, (open? TargetYaw : InitialYaw), DeltaTime * (open ? DoorOpenSpeed : DoorCloseSpeed));
	GetOwner()->SetActorRotation(openDoor);
}


float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}