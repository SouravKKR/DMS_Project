// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DMS_ProjectEnums.generated.h"

UENUM(BlueprintType)
enum class EGraphEdgeAttachState: uint8
{
	NotAttached,
	StartOnly,
	StartAndEnd,
};	


UCLASS()
class DMS_PROJECT_API UDMS_ProjectEnums : public UObject
{
	GENERATED_BODY()
	
};
