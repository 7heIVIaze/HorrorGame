// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#include "PatrolPoint_cpp.h"
#include "Components/BoxComponent.h"
#include "AI/Reaper_cpp.h"
#include "AI/Runner_cpp.h"
#include "AI/Brute_cpp.h"
#include "LevelManager.h"
#include "EngineUtils.h"

// Sets default values
APatrolPoint_cpp::APatrolPoint_cpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;
}

// Called when the game starts or when spawned
void APatrolPoint_cpp::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<ALevelManager>LevelManager(GetWorld()); LevelManager; ++LevelManager)
	{
		ALevelManager* CurrentLevelManager = *LevelManager;
		CurrentLevelManager->PatrolPoint.Add(true);
	}
}