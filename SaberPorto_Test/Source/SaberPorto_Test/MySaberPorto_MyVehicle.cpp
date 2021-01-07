// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaberPorto_MyVehicle.h"
#include "Kismet/KismetMathLibrary.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicle.h"
#include "SplinePathActor.h"
#include "Components/SplineComponent.h"
#include "Engine/World.h"



// Called when the game starts or when spawned
void AMySaberPorto_MyVehicle::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void AMySaberPorto_MyVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if my spline is valid continue, avoiding any error during runtime
	if (CurrentSpline) 
	{
		SplineDrive();
	}

}

void AMySaberPorto_MyVehicle::OverrideSteer(FVector Steering)
{
	SteeringVector = Steering;
	return;
}

float AMySaberPorto_MyVehicle::SteeringCalc()
{
	//Getting the look up to steer location
	FRotator CurrentLookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SteeringVector);
	//Getting the delta rotation of the actor from the steer location
	FRotator DeltaSteer = UKismetMathLibrary::NormalizedDeltaRotator(CurrentLookAt, GetActorRotation());
	//Setting up the steer rotation
	float Steer = FMath::GetMappedRangeValueUnclamped(FVector2D(-90.f,90.f), FVector2D(-1.f,1.f), DeltaSteer.Yaw);
	return Steer;
}



void AMySaberPorto_MyVehicle::WirelessSteer()
{
	//Setting steer to my vector

		GetVehicleMovementComponent()->SetSteeringInput(SteeringCalc());


	
}

void AMySaberPorto_MyVehicle::Drifting()
{
	//im not experience working with vehicles, i tried a better drift setup without any sucess, so i decided to keep it simple since im have no much time
	
	GetVehicleMovementComponent()->SetHandbrakeInput(true);

	//Little delay to release the brake while doing a curve
	FTimerHandle    ReleaseBrake;
	GetWorld()->GetTimerManager().SetTimer(ReleaseBrake, [this]()
	{

		GetVehicleMovementComponent()->SetHandbrakeInput(false);
	}, 2.5f, 0);





	
}

void AMySaberPorto_MyVehicle::SplineDrive()
{
		WirelessSteer();
//Getting the dinstance between my actor and the spline
	float VectorLength = ((UKismetMathLibrary::Subtract_VectorVector(GetActorLocation(), SplinePosition)).Size());
//Setting up the throttle of my actor depending on the spline distance
	float Throttle = FMath::GetMappedRangeValueClamped(FVector2D(250.f,750.f),FVector2D(0.f,1.f),VectorLength);
	GasConsumption(ThrottleControl * TrafficLightSpeed*Throttle*.005f);
	GetVehicleMovementComponent()->SetThrottleInput(Throttle*ThrottleControl*TrafficLightSpeed);
}

void AMySaberPorto_MyVehicle::GasConsumption(float Throttle)
{
	//Calculation of gas consumption depending on Throttle
	if (CurrentGas <= 0.f)
	{
		CurrentGas = 0.f;
		ThrottleControl = 0.f;
	}
	else
	{
		ThrottleControl = 1.f;
		CurrentGas = CurrentGas - Throttle;
	}

	GasProgress = CurrentGas / MaxGas;

	return;
}

int32 AMySaberPorto_MyVehicle::AddScore(int Score)
{
	TotalScore = TotalScore + Score;
	return TotalScore;
}



