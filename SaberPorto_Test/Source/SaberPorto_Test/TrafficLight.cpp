// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLight.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MySaberPorto_MyVehicle.h"
#include "WheeledVehicleMovementComponent.h"

class ASplinePathActor;
class AMySaberPorto_MyVehicle;
// Sets default values
ATrafficLight::ATrafficLight()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	TrafficLightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrafficLightMesh"));
	TrafficLightMesh->SetupAttachment(RootComponent);
	TrafficLightCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TrafficZoneCollider"));
	TrafficLightCollision->SetupAttachment(RootComponent);
	TrafficLightCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TrafficLightCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	TrafficLightCollision->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);



 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrafficLight::SetVehicleMovement(int CurrentColor)
{
	//Getting the current traffic light color and define if our vehicle will stop or not
	switch (CurrentColor)
	{
		case 0:
		{
			CurrentVehicle->GetVehicleMovementComponent()->SetHandbrakeInput(true);
			CurrentVehicle->TrafficLightSpeed = 0.f;
			break;
		}
		case 1:
		{
			CurrentVehicle->GetVehicleMovementComponent()->SetHandbrakeInput(false);	
			CurrentVehicle->TrafficLightSpeed = 1.f;
			break;
		}
		case 2:
		{
			CurrentVehicle->GetVehicleMovementComponent()->SetHandbrakeInput(false);
			CurrentVehicle->TrafficLightSpeed = 1.f;
			break;
		}
		case 3:
		{
			CurrentVehicle->GetVehicleMovementComponent()->SetHandbrakeInput(true);
			CurrentVehicle->TrafficLightSpeed = 0.f;
			break;
		}
	}
	return;
	
}
