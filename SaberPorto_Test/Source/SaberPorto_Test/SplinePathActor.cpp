// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePathActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "MySaberPorto_MyVehicle.h"




// Sets default values
ASplinePathActor::ASplinePathActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplinePath->SetupAttachment(Root);
	DriftZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DriftZoneCollider"));
	DriftZone->SetupAttachment(RootComponent);
	DriftZone->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DriftZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	DriftZone->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);

	VectorDistance = 1000.0f;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ASplinePathActor::BeginPlay()
{
	Super::BeginPlay();
	DriftZone->OnComponentBeginOverlap.AddDynamic(this, &ASplinePathActor::OnOverlapBegin);

}

// Called every frame
void ASplinePathActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector ASplinePathActor::SetActorSteer(AMySaberPorto_MyVehicle* Actor)
{
	//Getting my actor location so i can find the forward vector between my current actor's location and the current SplinePosition
	//I used an offset so i can get a smooth steer movement
	FVector MyActorLocation = Actor->GetActorLocation();
	FRotator MyRotator = UKismetMathLibrary::MakeRotationFromAxes(SplinePath->FindRightVectorClosestToWorldLocation(MyActorLocation, ESplineCoordinateSpace::Local), FVector(0.f), FVector(0.0f));
	FVector MyForwardVector = UKismetMathLibrary::GetForwardVector(MyRotator);
	FVector ClosestLocation = UKismetMathLibrary::Subtract_VectorVector(MyActorLocation, MyForwardVector*(VectorDistance));
	Steering = SplinePath->FindLocationClosestToWorldLocation(ClosestLocation, ESplineCoordinateSpace::World);
	Actor->SplinePosition=Steering;

	return Steering;

}

void ASplinePathActor::OnOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		AMySaberPorto_MyVehicle* OverlappedCharacter = Cast<AMySaberPorto_MyVehicle>(OtherActor);
		if (OverlappedCharacter)
		{

			OverlappedCharacter->Drifting();
		}
	}

}

void ASplinePathActor::ReplaceReference(AMySaberPorto_MyVehicle* Actor)
{

	ActorToMove = Actor;

	return;
}