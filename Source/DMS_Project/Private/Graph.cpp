// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"

UGraphNode* UGraph::CreateNewNode(const FString& Name, const FVector2D& Coordinates)
{
    auto NewNode = NewObject<UGraphNode>();
    NewNode->SetName(Name);;
    NewNode->SetCoordinates(Coordinates);
    Nodes.Add(NewNode);
    OnNodeCreated.Broadcast(NewNode);
	return NewNode;
}

void UGraph::RemoveNode(UGraphNode* NodeToRemove)
{
	Nodes.Remove(NodeToRemove);
}

UGraphEdge* UGraph::CreateNewEdge(UGraphNode* Start, UGraphNode* End)
{
    auto NewEdge = NewObject<UGraphEdge>();
    NewEdge->SetStart(Start);
    NewEdge->SetEnd(End);
    Edges.Add(NewEdge);
    OnEdgeCreated.Broadcast(NewEdge);
    return NewEdge;
}

void UGraph::RemoveEdge(UGraphEdge* EdgeToRemove)
{
    Edges.Remove(EdgeToRemove);
}

TSet<UGraphNode*> UGraph::GetVertexSet()
{
    return Nodes;
}

TSet<UGraphEdge*> UGraph::GetEdgeSet()
{
    return Edges;
}

UGraph* UGraph::CreateGraph()
{
	return NewObject<UGraph>();
}

FVector2D UGraph::GetTextFieldCoord(const FVector2D& PositionOne, const FVector2D& PositionTwo, float Distance)
{
    // Find the midpoint of the line connecting PositionOne and PositionTwo
    FVector2D MidPoint = (PositionOne + PositionTwo) * 0.5f;

    // Find the direction vector of the line
    FVector2D LineDirection = (PositionTwo - PositionOne).GetSafeNormal();

    // Calculate the unit normal vector perpendicular to the line
    FVector2D NormalVector = FVector2D(-LineDirection.Y, LineDirection.X);

    // Ensure the normal vector always faces in a consistent direction (up or down)
    if (NormalVector.Y < 0)
    {
        NormalVector *= -1.0f;
    }

    // Calculate the final result by scaling the unit vector with the constant k
    FVector2D Result = MidPoint + Distance * NormalVector;

    
    return Result;
}
