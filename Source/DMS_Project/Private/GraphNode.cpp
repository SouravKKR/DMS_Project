// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNode.h"

const TArray<UGraphNode*> UGraphNode::GetNeighbours() const
{
	TArray<UGraphNode*> NeighbourNodes;
	NeighbourNodes.Reserve(Neighbours.Num());
	
	for (auto& Neighbour : Neighbours)
	{
		NeighbourNodes.Emplace(Neighbour.Get<0>());
	}
	
	return NeighbourNodes;
}

TArray<TTuple<UGraphNode*, float>> UGraphNode::GetNeighboursAsTuple() const
{
	return Neighbours;
}

void UGraphNode::AddNeighbour(UGraphNode* NewNeighbour)
{
	Neighbours.AddUnique(TTuple<UGraphNode*, float>(NewNeighbour, 0.0f));
}

void UGraphNode::RemoveNeighbour(UGraphNode* NeighbourToRemove)
{
	for (auto& Neighbour : Neighbours)
	{
		if (Neighbour.Get<0>() == NeighbourToRemove)
		{
			Neighbours.Remove(Neighbour);
			return;
		}
	}
}

void UGraphNode::UpdateNeighbour(UGraphNode* FirstNode, UGraphNode* SecondNode, float NewPathCost)
{
	for (auto& Neighbour : FirstNode->Neighbours)
	{
		UGraphNode* CurrentNeighbour = Neighbour.Get<0>();
		if (CurrentNeighbour == SecondNode)
		{
			Neighbour = MakeTuple(CurrentNeighbour, NewPathCost);
			return;
		}
	}

	for (auto& Neighbour : SecondNode->Neighbours)
	{
		UGraphNode* CurrentNeighbour = Neighbour.Get<0>();
		if (CurrentNeighbour == FirstNode)
		{
			Neighbour = MakeTuple(CurrentNeighbour, NewPathCost);
			return;
		}
	}
}
