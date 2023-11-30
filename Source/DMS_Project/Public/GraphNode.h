// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphNode.generated.h"


UCLASS(Blueprintable)
class DMS_PROJECT_API UGraphNode : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FVector2D Coordinates;

	UPROPERTY()
	TArray<UGraphNode*> Neighbours;

public:
    // Getter for Name
    UFUNCTION(BlueprintPure, Category = "Graph Node")
    FString GetName() const { return Name; }

    // Setter for Name
    UFUNCTION(BlueprintCallable, Category = "Graph Node")
    void SetName(const FString& NewName) { Name = NewName; }

    // Getter for Coordinates
    UFUNCTION(BlueprintPure, Category = "Graph Node")
    FVector2D GetCoordinates() const { return Coordinates; }

    // Setter for Coordinates
    UFUNCTION(BlueprintCallable, Category = "Graph Node")
    void SetCoordinates(const FVector2D& NewCoordinates) { Coordinates = NewCoordinates; }

    // Getter for Neighbours
    UFUNCTION(BlueprintPure, Category = "Graph Node")
    const TArray<UGraphNode*>& GetNeighbours() const { return Neighbours; }

    // Add a neighbour
    UFUNCTION(BlueprintCallable, Category = "Graph Node")
    void AddNeighbour(UGraphNode* NewNeighbour) { Neighbours.AddUnique(NewNeighbour); }

    // Remove a neighbour
    UFUNCTION(BlueprintCallable, Category = "Graph Node")
    void RemoveNeighbour(UGraphNode* NeighbourToRemove) { Neighbours.Remove(NeighbourToRemove); }

};
