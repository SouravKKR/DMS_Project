// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Graph.generated.h"

USTRUCT(BlueprintType)
struct FPathInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UGraphNode*> Path;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Cost;

	FPathInfo(TArray<UGraphNode*> InPath, float InCost) :
		Path(InPath),
		Cost(InCost)
	{

	}

	FPathInfo(){}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeCreated, UGraphNode*, NewNode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEdgeCreated, UGraphEdge*, NewEdge);

UCLASS(Blueprintable)
class DMS_PROJECT_API UGraph : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<UGraphNode*> Nodes;

	UPROPERTY()
	TSet<UGraphEdge*> Edges;

public:
	UFUNCTION(BlueprintCallable)
	UGraphNode* CreateNewNode(const FString& Name, const FVector2D& Coordinates);

	UFUNCTION(BlueprintCallable)
	void RemoveNode(UGraphNode* NodeToRemove);

	UFUNCTION(BlueprintCallable)
	UGraphEdge* CreateNewEdge(UGraphNode* Start, UGraphNode* End);

	UFUNCTION(BlueprintCallable)
	void RemoveEdge(UGraphEdge* NodeToRemove);

	UFUNCTION(BlueprintCallable)
	TSet<UGraphNode*> GetVertexSet();

	UFUNCTION(BlueprintCallable)
	TSet<UGraphEdge*> GetEdgeSet();

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetNumberOfNodes() const { return Nodes.Num(); }

	UFUNCTION(BlueprintCallable)
	static UGraph* CreateGraph();

	UFUNCTION(BlueprintPure)
	static FVector2D GetTextFieldCoord(const FVector2D& PositionOne, const FVector2D& PositionTwo, float Distance);

	//Logic for traversing and finding shortest path
	void Dijkstra(UGraphNode* StartNode, UGraphNode* DestinationNode, TTuple<TArray<UGraphNode*>, float>& Result, float& ShortestDistance);

	UFUNCTION(BlueprintCallable)
	FPathInfo FindShortestPath(UGraphNode* StartingNode, UGraphNode* DestinationNode);

	//Delegates

	UPROPERTY(BlueprintAssignable)
	FOnNodeCreated OnNodeCreated;

	UPROPERTY(BlueprintAssignable)
	FOnEdgeCreated OnEdgeCreated;
};