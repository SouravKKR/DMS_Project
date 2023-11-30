// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"

UGraphNode* UGraph::CreateNewNode(const FString& Name, const FVector2D& Coordinates)
{
	Nodes.Add(NewObject<UGraphNode>());
	Nodes.Last()->SetName(Name);
	Nodes.Last()->SetCoordinates(Coordinates);
	return Nodes.Last();
}

void UGraph::RemoveNode(UGraphNode* NodeToRemove)
{
	Nodes.Remove(NodeToRemove);
}

UGraph* UGraph::CreateGraph()
{
	return NewObject<UGraph>();
}
