// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphNode.h"
#include "Graph.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DMS_PROJECT_API UGraph : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<UGraphNode*> Nodes;

public:
	UFUNCTION(BlueprintCallable)
	UGraphNode* CreateNewNode(const FString& Name, const FVector2D& Coordinates);

	UFUNCTION(BlueprintCallable)
	void RemoveNode(UGraphNode* NodeToRemove);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetNumberOfNodes() const { return Nodes.Num(); }

	UFUNCTION(BlueprintCallable)
	static UGraph* CreateGraph();
};
