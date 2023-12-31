// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#include "Items/Timer_cpp.h"
#include "HorrorGame/HorrorGameCharacter.h"

// Sets default values
ATimer_cpp::ATimer_cpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FVector DefaultLoc = FVector(0.f, 0.f, 0.f);
	FVector DefaultScale = FVector(1.f, 1.f, 1.f);

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DefaultSceneRoot->SetWorldLocation(DefaultLoc);
	DefaultSceneRoot->SetWorldScale3D(DefaultScale);
	RootComponent = DefaultSceneRoot;

	TimerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Timer"));
	TimerMesh->SetupAttachment(DefaultSceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TimerObj(TEXT("/Game/Assets/Items/timer"));
	if (TimerObj.Succeeded())
	{
		TimerMesh->SetStaticMesh(TimerObj.Object);
	}
	TimerMesh->SetRelativeLocation(DefaultLoc);
	TimerMesh->SetRelativeScale3D(FVector(3.f, 2.f, 3.f));
	TimerMesh->SetCollisionProfileName("ItemObjects");
}

// Called when the game starts or when spawned
void ATimer_cpp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
//void ATimer_cpp::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ATimer_cpp::OnInteract(class AHorrorGameCharacter* Player) // Player Click Event
{
	Super::OnInteract(Player);

	Player->AddTimer();
	if (Player->bCanItemGet)
	{
		Destroy();
	}
}

void ATimer_cpp::UseInteract(class AHorrorGameCharacter* Player)
{
	Super::UseInteract(Player);
}