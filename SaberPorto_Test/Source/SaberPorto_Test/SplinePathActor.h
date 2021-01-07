// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePathActor.generated.h"

class AMySaberPorto_MyVehicle;
class UBoxComponent;

UCLASS()
class SABERPORTO_TEST_API ASplinePathActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		UBoxComponent* DriftZone;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineController")
	class AMySaberPorto_MyVehicle* ActorToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineController")
	float VectorDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class USplineComponent* SplinePath;

public:
	UFUNCTION(BlueprintPure, Category = "Steering")
	FVector SetActorSteer(AMySaberPorto_MyVehicle* Actor);
	UFUNCTION(BlueprintCallable, Category = "SplineController")
	void ReplaceReference(AMySaberPorto_MyVehicle* Actor);
	FVector Steering;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlapComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	ASplinePathActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
