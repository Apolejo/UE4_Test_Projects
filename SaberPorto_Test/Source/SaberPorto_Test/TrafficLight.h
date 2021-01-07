// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLight.generated.h"


class UStaticMeshComponent;
class AMySaberPorto_MyVehicle;
class ASplinePathActor;
class UBoxComponent;

UCLASS()
class SABERPORTO_TEST_API ATrafficLight : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		UStaticMeshComponent* TrafficLightMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		UBoxComponent* TrafficLightCollision;
public:
	// Sets default values for this actor's properties
	ATrafficLight();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


	FVector MyLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrafficLight")
	TArray<ASplinePathActor*> MySplines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrafficLight")
	class AMySaberPorto_MyVehicle* CurrentVehicle;


public:

	UFUNCTION(BlueprintCallable, Category = "TraffictLight")
		void SetVehicleMovement(int CurrentLight);

};
