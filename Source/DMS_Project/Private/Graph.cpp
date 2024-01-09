// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"
#include <map>
#include <set>
#include "Kismet/KismetSystemLibrary.h"

#define PRINT(x) UKismetSystemLibrary::PrintString(this, x);

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

    // Calculate the unit normal vector perpendicular to line
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

UGraphNode* UGraph::GetNodeByName(const FString& Name)
{
	for (auto& Node : Nodes)
	{
		if (Node->GetName() == Name)
		{
			return Node;
		}   
	}
    return nullptr;
}

FPathCollection UGraph::Dijkstra(UGraphNode* StartNode, UGraphNode* DestinationNode, TTuple<TArray<UGraphNode*>, float>& ShortestPath, float& ShortestDistance)
{
    FPathCollection PathCollection;

    std::map<UGraphNode*, float> Distance;
    std::map<UGraphNode*, UGraphNode*> Previous;
    // try to use TTuple instead of TPair
    std::set<std::pair<float, UGraphNode*>> PriorityQueue;

    // Initialization
    TSet<UGraphNode*> AllNodes = GetVertexSet();
    for (const auto Node : AllNodes)
    {
        Distance[Node] = FLT_MAX;
        Previous[Node] = nullptr;
        PriorityQueue.insert({ FLT_MAX, Node });
    }

    Distance[StartNode] = 0.0f;
    PriorityQueue.erase({ FLT_MAX, StartNode });
    PriorityQueue.insert({ 0.0f, StartNode });

    // Dijkstra's algorithm
    while (!PriorityQueue.empty())
    {
        UGraphNode* CurrNode = PriorityQueue.begin()->second;
		PathCollection.PathTraced.Add(CurrNode);
        PriorityQueue.erase(PriorityQueue.begin());
        const TArray<TTuple<UGraphNode*, float>> Neighbors = CurrNode->GetNeighboursAsTuple();

        for (const TTuple<UGraphNode*, float> Neighbor : Neighbors)
        {
            UGraphNode* NextNode = Neighbor.Get<0>();
            float EdgeWeight = Neighbor.Get<1>();
            float NewDistance = Distance[CurrNode] + EdgeWeight;

            if (NewDistance < Distance[NextNode])
            {
                PriorityQueue.erase({ Distance[NextNode], NextNode });
                PriorityQueue.insert({ NewDistance, NextNode });
                Distance[NextNode] = NewDistance;
                Previous[NextNode] = CurrNode;
            }
        }
    }

    // Reconstruct the shortest path
    ShortestDistance = Distance[DestinationNode];
    UGraphNode* CurrentNode = DestinationNode;
    while (CurrentNode != nullptr)
    {
        ShortestPath.Get<0>().Insert(CurrentNode, 0);
        CurrentNode = Previous[CurrentNode];
    }

    PathCollection.ShortestPath = FPathInfo(ShortestPath.Get<0>(), ShortestPath.Get<1>());
    
    PRINT("Shortest Path(inside): " + FString::FromInt(PathCollection.ShortestPath.Path.Num()));
	PRINT("Path Traced(inside): " + FString::FromInt(PathCollection.PathTraced.Num()));

    return PathCollection;
}

FPathCollection UGraph::RunAlgorithm(UGraphNode* StartingNode, UGraphNode* DestinationNode, const FString& AlgorithmName)
{
	if (AlgorithmName == "Dijkstras")
	{
		TTuple<TArray<UGraphNode*>, float> ShortestPath;
		float ShortestDistance;
        FPathCollection P = Dijkstra(StartingNode, DestinationNode, ShortestPath, ShortestDistance);
		PRINT("Shortest Path(outside): " + FString::FromInt(P.ShortestPath.Path.Num()));
        PRINT("Path Traced(outside): " + FString::FromInt(P.PathTraced.Num()));
        return P;
	}
	else
	{
		return FPathCollection();
	}
}


