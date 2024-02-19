// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Stuning.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UBTService_Stuning : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Stuning();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};