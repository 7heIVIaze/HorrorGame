// CopyrightNotice=0 2023 Sunggon Kim

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_MoveToLocker.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UBTTask_MoveToLocker : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
		float AcceptableRadius;

	UPROPERTY(Category = Node, EditAnywhere)
		bool bAllowPartialPath = true;

	UPROPERTY(Category = Node, EditAnywhere)
		bool bTrackMovingGoal = true;

	UPROPERTY(Category = Node, EditAnywhere)
		bool bProjectGoalLocation = true;

	UPROPERTY(Category = Node, EditAnywhere)
		bool bAllowStrafe = true;

	UPROPERTY(Category = Node, VisibleInstanceOnly)
		bool bStopOverlap = true;

	bool bUsePathfinding = true;
public:
	UBTTask_MoveToLocker();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	AActor* Target = nullptr;
};
