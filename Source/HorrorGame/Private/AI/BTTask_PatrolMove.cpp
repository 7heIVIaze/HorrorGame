// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#include "AI/BTTask_PatrolMove.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AISystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AI/CreatureAI.h"
#include "AI/AIController_Runner.h"
#include "AI/AIController_Brute.h"
#include "AI/Reaper_cpp.h"
#include "AI/Runner_cpp.h"
#include "AI/Brute_cpp.h"
#include "Tasks/AITask_MoveTo.h"
#include "HorrorGame/HorrorGameCharacter.h"

UBTTask_PatrolMove::UBTTask_PatrolMove()
{
	NodeName = TEXT("PatrolMove");
	bNotifyTick = true;

}

EBTNodeResult::Type UBTTask_PatrolMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Super::ExecuteTask(OwnerComp, NodeMemory);
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress; // 동작 수행은 여기서 처리하지 않을 것이기 때문에 InProgress로 아직 결과가 미정임을 밝힌다.

	
	AAIController* AIController = OwnerComp.GetAIOwner();
	// APawn* Creature = AIController->GetPawn();

	if (AIController == nullptr) // AI 컴포넌트의 Controller가 없다면 실패를 리턴시킨다.
	{
		NodeResult = EBTNodeResult::Failed; 
	}

	return NodeResult;

	/*if (ACreatureAI* ReaperAI = Cast<ACreatureAI>(AIController))
	{
		AReaper_cpp* Reaper = Cast<AReaper_cpp>(ReaperAI->GetPawn());

		if (nullptr == Reaper)
		{
			return EBTNodeResult::Failed;
		}

		return EBTNodeResult::InProgress;
	}

	if (AAIController_Runner* RunnerAI = Cast<AAIController_Runner>(AIController))
	{
		ARunner_cpp* Runner = Cast<ARunner_cpp>(RunnerAI->GetPawn());

		if (nullptr == Runner)
		{
			return EBTNodeResult::Failed;
		}

		return EBTNodeResult::InProgress;
	}

	if (AAIController_Brute* BruteAI = Cast<AAIController_Brute>(AIController))
	{
		ABrute_cpp* Brute = Cast<ABrute_cpp>(BruteAI->GetPawn());

		if (nullptr == Brute)
		{
			UE_LOG(LogTemp, Warning, TEXT("Creature Initialize Failed"));
			return EBTNodeResult::Failed;
		}

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;*/
	/*ACreatureAI* ReaperAI = Cast<ACreatureAI>(OwnerComp.GetAIOwner());
	AAIController_Runner* RunnerAI = Cast<AAIController_Runner>(OwnerComp.GetAIOwner());
	APawn* Creature = nullptr;
	
	if (ReaperAI)
	{
		Creature = ReaperAI->GetPawn();
	}
	
	if (RunnerAI)
	{
		Creature = RunnerAI->GetPawn();
	}

	if (nullptr == Creature)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task_PatrolMove: Creature Initialized Failed"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;*/
}

void UBTTask_PatrolMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController) // AI Controller가 있는 경우에만 아래의 동작을 수행한다.
	{
		if (ACreatureAI* ReaperAI = Cast<ACreatureAI>(AIController))
		{
			AReaper_cpp* Reaper = Cast<AReaper_cpp>(ReaperAI->GetPawn());

			if (nullptr == Reaper)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				return;
			}

			/*FAIMoveRequest MoveReq;
			MoveReq.SetNavigationFilter(ReaperAI->GetDefaultNavigationFilterClass());
			MoveReq.SetAllowPartialPath(bAllowPartialPath);
			MoveReq.SetAcceptanceRadius(AcceptableRadius);
			MoveReq.SetProjectGoalLocation(bProjectGoalLocation);
			MoveReq.SetUsePathfinding(bUsePathfinding);*/

			FVector PatrolLocation = ReaperAI->GetBlackboard()->GetValueAsVector(ACreatureAI::PatrolPosKey);
			AActor* PatrolTarget= Cast<AActor>(ReaperAI->GetBlackboard()->GetValueAsObject(ACreatureAI::PatrolTargetKey));
			// AActor* pTarget = Cast<AActor>(ReaperAI->GetBlackboard()->GetValueAsObject(ACreatureAI::TargetKey));
			bool bCanSeePlayer = ReaperAI->GetBlackboard()->GetValueAsBool(ACreatureAI::CanSeePlayer);
			bool bNoiseDetected = ReaperAI->GetBlackboard()->GetValueAsBool(ACreatureAI::NoiseDetected);
			//bool bSprintDetected = ReaperAI->GetBlackboard()->GetValueAsBool(ACreatureAI::SprintDetected);
			float Distance = 200.f;
			FVector ReaperLocation = Reaper->GetActorLocation(); // 리퍼의 Z 값은 132(132.400002)
			

			if (bCanSeePlayer) // 만약 플레이어를 추격하다가 플레이어를 놓쳤을 경우, 
			{
				ReaperAI->MoveToLocation(PatrolLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
					bProjectGoalLocation, bAllowStrafe, ReaperAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
				Distance = FMath::Abs(FVector::Distance(PatrolLocation, ReaperLocation));
				// 추격하다 놓친 상태에서는 FindPlayerLocation에서 랜덤 순찰 지점을 PatrolPosKey에 저장하므로 Location임
			}
			else // 플레이어를 추격 중이 아닌 상황일 경우
			{
				if (bNoiseDetected) // 타이머나 알람이 울리는 소리를 들었을 경우
				{
					FVector TargetLocation = ReaperAI->GetBlackboard()->GetValueAsVector(ACreatureAI::TargetLocation); // 타겟 위치
					AActor* NoiseTarget = Cast<AActor>(ReaperAI->GetBlackboard()->GetValueAsObject(ACreatureAI::NoiseTargetKey)); // 타겟

					if (NoiseTarget) // 소리 근원지 타겟 존재 시
					{
						ReaperAI->MoveToActor(NoiseTarget, AcceptableRadius, bStopOverlap, bUsePathfinding,
							bAllowStrafe, ReaperAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
						ReaperLocation.Z = NoiseTarget->GetActorLocation().Z; // 그냥 액터의 Z 위치 동일화시킴
						Distance = FMath::Abs(FVector::Distance(NoiseTarget->GetActorLocation(), ReaperLocation));
					}
					else
					{
						ReaperAI->MoveToLocation(TargetLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
							bProjectGoalLocation, bAllowStrafe, ReaperAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
						ReaperLocation.Z = TargetLocation.Z; // 그냥 액터의 Z 위치 동일화시킴
						Distance = FMath::Abs(FVector::Distance(TargetLocation, ReaperLocation));
					}
					// 소리를 들은 상태에서는 NoiseDetect에서 근원지를 TargetLocationKey에 저장하므로 Location임
				}
				//else if (bSprintDetected) // 달리는 소리를 들었을 때
				//{
				//	FVector TargetLocation = ReaperAI->GetBlackboard()->GetValueAsVector(ACreatureAI::TargetLocation); // 타겟 위치
				//	ReaperAI->MoveToLocation(TargetLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
				//		bProjectGoalLocation, bAllowStrafe, ReaperAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
				//	Distance = FMath::Abs(FVector::Distance(TargetLocation, ReaperLocation));
				//}
				else // 그것이 아닌 상황은 진짜 PatrolPoint를 향해 가는 것
				{
					ReaperAI->MoveToActor(PatrolTarget, AcceptableRadius, bStopOverlap, bUsePathfinding,
						bAllowStrafe, ReaperAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
					ReaperLocation.Z -= 122.400002f;
					Distance = FMath::Abs(FVector::Distance(PatrolTarget->GetActorLocation(), ReaperLocation));
					// PatrolPoint는 PatrolTarget에 저장하니까 MoveToActor 사용
					/*	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Target: %s, Distance: %f"), *PatrolTarget->GetActorLabel(), Distance));*/
				}
				
			}
			
			// 리퍼와 패트롤 포인트의 거리 차이는 90.8으로 나옴

			if (Distance <= 100.f)
			{
				Reaper->SetPatrolSuccess(true);
			}
		
			if (Reaper->GetPatrolSuccess())
			{
				Reaper->SetPatrolSuccess(false);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Reaper Patrol Success")));
				UE_LOG(LogTemp, Warning, TEXT("End Task"));
				return;
			}
		}

		else if (AAIController_Runner* RunnerAI = Cast<AAIController_Runner>(AIController))
		{
			ARunner_cpp* Runner = Cast<ARunner_cpp>(RunnerAI->GetPawn());

			if (nullptr == Runner)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				return;
			}

			FVector PatrolLocation = RunnerAI->GetBlackboard()->GetValueAsVector(AAIController_Runner::PatrolPosKey);
			AActor* PatrolTarget = Cast<AActor>(RunnerAI->GetBlackboard()->GetValueAsObject(AAIController_Runner::PatrolTargetKey));
			
			bool bCanSeePlayer = RunnerAI->GetBlackboard()->GetValueAsBool(AAIController_Runner::CanSeePlayer);
			bool bNoiseDetected = RunnerAI->GetBlackboard()->GetValueAsBool(AAIController_Runner::NoiseDetected);
			// bool bSprintDetected = RunnerAI->GetBlackboard()->GetValueAsBool(AAIController_Runner::SprintDetected);

			FVector RunnerLocation = Runner->GetActorLocation(); // 러너의 Z 값은 100(100.15)
			
			float Distance = 200.f;

			if (bCanSeePlayer) // 만약 플레이어를 추격하다가 플레이어를 놓쳤을 경우거나
			{
				RunnerAI->MoveToLocation(PatrolLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
					bProjectGoalLocation, bAllowStrafe, RunnerAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
				Distance = FMath::Abs(FVector::Distance(PatrolLocation, RunnerLocation));
				// 추격하다 놓친 상태에서는 FindPlayerLocation에서 랜덤 순찰 지점을 PatrolPosKey에 저장하므로 Location임
			}
			else // 플레이어를 추격 중이 아닌 상황일 경우
			{
				if (bNoiseDetected) // 타이머나 알람이 울리는 소리를 들었을 때
				{
					FVector TargetLocation = RunnerAI->GetBlackboard()->GetValueAsVector(AAIController_Runner::TargetLocation);
					AActor* NoiseTarget = Cast<AActor>(RunnerAI->GetBlackboard()->GetValueAsObject(AAIController_Runner::NoiseTargetKey));
					
					if (NoiseTarget) // 타겟이 존재할 땐 MoveToActor
					{
						RunnerAI->MoveToActor(NoiseTarget, AcceptableRadius, bStopOverlap, bUsePathfinding,
							bAllowStrafe, RunnerAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
						RunnerLocation.Z = NoiseTarget->GetActorLocation().Z; // 그냥 액터의 Z 위치 동일화시킴
						Distance = FMath::Abs(FVector::Distance(NoiseTarget->GetActorLocation(), RunnerLocation));
					}
					else // 존재 안할 땐, MoveToLocation
					{
						RunnerAI->MoveToLocation(TargetLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
							bProjectGoalLocation, bAllowStrafe, RunnerAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
						RunnerLocation.Z = TargetLocation.Z; // 그냥 액터의 Z 위치 동일화시킴
						Distance = FMath::Abs(FVector::Distance(TargetLocation, RunnerLocation));
					}
					// 소리를 들은 상태에서는 NoiseDetect에서 근원지를 TargetLocationKey에 저장하므로 Location임
				}
				else // 그것이 아닌 상황은 진짜 PatrolPoint를 향해 가는 것
				{
					RunnerAI->MoveToActor(PatrolTarget, AcceptableRadius, bStopOverlap, bUsePathfinding,
						bAllowStrafe, RunnerAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
					RunnerLocation.Z -= 90.15f;
					Distance = FMath::Abs(FVector::Distance(PatrolTarget->GetActorLocation(), RunnerLocation));
					// PatrolPoint는 PatrolTarget에 저장하니까 MoveToActor 사용
				}
			}
			
			// 러너와 패트롤 포인트의 거리 차이는 80으로 나옴

			if (Distance <= 80.f)
			{
				Runner->SetPatrolSuccess(true);
			}

			if (Runner->GetPatrolSuccess())
			{
				Runner->SetPatrolSuccess(false);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				/*if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Runner Patrol Success")));*/
				UE_LOG(LogTemp, Warning, TEXT("End Task"));
				return;
			}
		}

		else if (AAIController_Brute* BruteAI = Cast<AAIController_Brute>(AIController))
		{
			ABrute_cpp* Brute = Cast<ABrute_cpp>(BruteAI->GetPawn());

			if (nullptr == Brute)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				return;
			}

			FVector PatrolLocation = BruteAI->GetBlackboard()->GetValueAsVector(AAIController_Brute::PatrolPosKey);
			AActor* PatrolTarget = Cast<AActor>(BruteAI->GetBlackboard()->GetValueAsObject(AAIController_Brute::PatrolTargetKey));
			
			bool bCanSeePlayer = BruteAI->GetBlackboard()->GetValueAsBool(AAIController_Brute::CanSeePlayer);
			bool bNoiseDetected = BruteAI->GetBlackboard()->GetValueAsBool(AAIController_Brute::NoiseDetected);

			FVector BruteLocation = Brute->GetActorLocation(); // 브루트의 Z 값은 100
			
			float Distance = 200.f;

			if (bCanSeePlayer) // 만약 플레이어를 추격하다가 플레이어를 놓쳤을 경우거나
			{
				BruteAI->MoveToLocation(PatrolLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
					bProjectGoalLocation, bAllowStrafe, BruteAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
				BruteLocation.Z = PatrolLocation.Z;
				Distance = FMath::Abs(FVector::Distance(PatrolLocation, BruteLocation));
				// 추격하다 놓친 상태에서는 FindPlayerLocation에서 랜덤 순찰 지점을 PatrolPosKey에 저장하므로 Location임
			}
			else // 플레이어를 추격 중이 아닌 상황일 경우
			{
				if (bNoiseDetected) // 플레이어나 무언가가 내는 소리를 들었을 경우
				{
					FVector TargetLocation = BruteAI->GetBlackboard()->GetValueAsVector(AAIController_Brute::TargetLocation);
					AActor* NoiseTarget = Cast<AActor>(BruteAI->GetBlackboard()->GetValueAsObject(AAIController_Brute::NoiseTargetKey));
					
					if (NoiseTarget) // 타겟이 존재하면 MoveToActor로
					{
						BruteAI->MoveToActor(NoiseTarget, AcceptableRadius, bStopOverlap, bUsePathfinding,
							bAllowStrafe, BruteAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
						BruteLocation.Z = NoiseTarget->GetActorLocation().Z;
						Distance = FMath::Abs(FVector::Distance(NoiseTarget->GetActorLocation(), BruteLocation));
					}
					else
					{
						BruteAI->MoveToLocation(TargetLocation, AcceptableRadius, bStopOverlap, bUsePathfinding,
							bProjectGoalLocation, bAllowStrafe, BruteAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
						BruteLocation.Z = TargetLocation.Z;
						Distance = FMath::Abs(FVector::Distance(TargetLocation, BruteLocation));
						// 소리를 들은 상태에서는 NoiseDetect에서 근원지를 TargetLocationKey에 저장하므로 Location임
					}
				}
				else
				{
					BruteAI->MoveToActor(PatrolTarget, AcceptableRadius, bStopOverlap, bUsePathfinding,
						bAllowStrafe, BruteAI->GetDefaultNavigationFilterClass(), bAllowPartialPath);
					BruteLocation.Z -= 90.f;
					Distance = FMath::Abs(FVector::Distance(PatrolTarget->GetActorLocation(), BruteLocation));
					// PatrolPoint는 PatrolTarget에 저장하니까 MoveToActor 사용
				}
				// 브루트와 패트롤 포인트의 거리 차이는 76으로 나옴
			}
			
			if (Distance <= 80.f)
			{
				Brute->SetPatrolSuccess(true);
			}

			if (Brute->GetPatrolSuccess())
			{
				Brute->SetPatrolSuccess(false);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				/*if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Brute Patrol Success")));*/
				UE_LOG(LogTemp, Warning, TEXT("End Task"));
				return;
			}
			/*else
			{
				Reaper->SetPatrolSuccess(false);
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Brute Patrol Failed")));
				return;
			}*/
		}
	}
	else // AI Controller가 없는 경우엔, 그냥 실패했다고 알리고 Task를 종료한다.
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
//
//	ACreatureAI* ReaperAI = Cast<ACreatureAI>(OwnerComp.GetAIOwner());
//	AAIController_Runner* RunnerAI = Cast<AAIController_Runner>(OwnerComp.GetAIOwner());
//	APawn* Creature = nullptr;
//
//	if (ReaperAI)
//	{
//		Creature = ReaperAI->GetPawn();
//	}
//	
//	if (RunnerAI)
//	{
//		Creature = RunnerAI->GetPawn();
//	}
//
//	if (nullptr == Creature)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Task_PatrolMove: Creature Initialized Failed"));
//		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//		return;
//	}
//
//	
//	FVector vPatrolLocation(0.f, 0.f, 0.f);
//	UObject* pTarget = nullptr;
//
//	if(ReaperAI) 
//	{
//		vPatrolLocation = ReaperAI->GetBlackboard()->GetValueAsVector(ACreatureAI::TargetLocation);
//		pTarget = ReaperAI->GetBlackboard()->GetValueAsObject(ACreatureAI::TargetKey);
//	}
//
//	if(RunnerAI)
//	{
//		vPatrolLocation = RunnerAI->GetBlackboard()->GetValueAsVector(AAIController_Runner::TargetLocation);
//		pTarget = RunnerAI->GetBlackboard()->GetValueAsObject(AAIController_Runner::TargetKey);
//	}
//	//FVector vPatrolLocation = AIController->GetBlackboard()->GetValueAsVector(ACreatureAI::PatrolPosKey);
//	FVector vCreatureLocation = Creature->GetActorLocation();
////	vPatrolLocation.Z = vCreatureLocation.Z;
//	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, vPatrolLocation);
//	if(nullptr == pTarget) 
//	{
//		if(ReaperAI)
//			ReaperAI->MoveToLocation(vPatrolLocation, 0.f, false, true);
//
//		if(RunnerAI)
//			RunnerAI->MoveToLocation(vPatrolLocation, 0.f, false, true);
//	}
//
//	/*else
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//		return;
//	}*/
//	
//
//	vPatrolLocation.Z = 0.f;
//	vCreatureLocation.Z = 0.f;
//	float fDistance = FVector::Distance(vCreatureLocation, vPatrolLocation);
//
//	if (fDistance <= 5.0f)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//		UE_LOG(LogTemp, Warning, TEXT("End Task"));
//		return;
//	}
}
