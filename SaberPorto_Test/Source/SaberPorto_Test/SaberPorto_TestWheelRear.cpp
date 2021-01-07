// Copyright Epic Games, Inc. All Rights Reserved.

#include "SaberPorto_TestWheelRear.h"
#include "TireConfig.h"
#include "UObject/ConstructorHelpers.h"

USaberPorto_TestWheelRear::USaberPorto_TestWheelRear()
{
	ShapeRadius = 18.0f;
	ShapeWidth = 15.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 0.f;

	LatStiffValue = 12.0f;
	

	// Setup suspension forces
	SuspensionForceOffset = -0.0f;
	SuspensionMaxRaise = 0.0f;
	SuspensionMaxDrop = 18.0f;
	SuspensionNaturalFrequency = 9.0f;
	SuspensionDampingRatio = 3.0f;

	// Find the tire object and set the data for it
	static ConstructorHelpers::FObjectFinder<UTireConfig> TireData(TEXT("/Game/VehicleAdv/Vehicle/WheelData/Vehicle_BackTireConfig.Vehicle_BackTireConfig"));
	TireConfig = TireData.Object;

}
