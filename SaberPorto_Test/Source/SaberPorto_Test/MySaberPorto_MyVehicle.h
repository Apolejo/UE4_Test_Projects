// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaberPorto_TestPawn.h"
#include "MySaberPorto_MyVehicle.generated.h"



class ASplinePathActor;
class ATrafficLight;
/**
 * 
 */
UCLASS()
class SABERPORTO_TEST_API AMySaberPorto_MyVehicle : public ASaberPorto_TestPawn
{
	GENERATED_BODY()


public:

	//Steering depending on spline current position
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Steering")
	FVector SteeringVector;
	//Spline current position
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SplineSetup")
	FVector SplinePosition;
	//Getting the current spline so can detect the closest location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineSetup")
	ASplinePathActor* CurrentSpline;
	//Current Gas Storage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI_Settings")
	float CurrentGas = 180.f;
	//MaxGas storage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Settings")
	float MaxGas = 200.f;
	//Float to progress bar
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI_Settings")
	float GasProgress = 1.f;
	//SpeedControl while light is red
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TrafficLight")
	float TrafficLightSpeed = 1.f;
public:

	UFUNCTION(BlueprintPure, Category = "Steering")
		float SteeringCalc();
	UFUNCTION(BlueprintCallable, Category = "Steering")
		void OverrideSteer(FVector Steering);
	UFUNCTION(BlueprintCallable, Category = "Steering")
		void WirelessSteer();
	UFUNCTION(BlueprintCallable, Category = "Steering")
		void Drifting();
	UFUNCTION(BlueprintCallable, Category = "Throttle")
		void SplineDrive();
	UFUNCTION(BlueprintCallable, Category = "Throttle")
		void GasConsumption(float Throttle);
	UFUNCTION(BlueprintCallable, Category = "Throttle")
		int32 AddScore(int Score);





protected:

	virtual void BeginPlay() override;



public:

	virtual void Tick(float DeltaTime) override;


protected:

	float MaxSteer;
	float TotalScore;
	float ThrottleControl;


};
