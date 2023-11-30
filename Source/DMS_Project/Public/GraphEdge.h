// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphNode.h"
#include "GraphEdge.generated.h"


UCLASS(Blueprintable)
class DMS_PROJECT_API UGraphEdge : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UGraphNode* Start;

	UPROPERTY()
    UGraphNode* End;
	
	UPROPERTY()
	float AverageSpeed;

public:
    UFUNCTION(BlueprintPure, Category = "Graph Edge")
    UGraphNode* GetStart() const { return Start; }

    // Setter for Start
    UFUNCTION(BlueprintCallable, Category = "Graph Edge")
    void SetStart(UGraphNode* NewStart) { Start = NewStart; }

    // Getter for End
    UFUNCTION(BlueprintPure, Category = "Graph Edge")
    UGraphNode* GetEnd() const { return End; }

    // Setter for End
    UFUNCTION(BlueprintCallable, Category = "Graph Edge")
    void SetEnd(UGraphNode* NewEnd) { End = NewEnd; }

    // Getter for AverageSpeed
    UFUNCTION(BlueprintPure, Category = "Graph Edge")
    float GetAverageSpeed() const { return AverageSpeed; }

    // Setter for AverageSpeed
    UFUNCTION(BlueprintCallable, Category = "Graph Edge")
    void SetAverageSpeed(float NewAverageSpeed) { AverageSpeed = NewAverageSpeed; }

    // Getter for Distance
    UFUNCTION(BlueprintPure, Category = "Graph Edge")
    float GetDistance() const { return FVector2D::Distance(Start->GetCoordinates(), End->GetCoordinates()); }
	
   
};
