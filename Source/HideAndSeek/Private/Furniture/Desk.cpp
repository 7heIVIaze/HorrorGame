// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com


#include "Furniture/Desk.h"

// Sets default values
ADesk::ADesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADesk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
