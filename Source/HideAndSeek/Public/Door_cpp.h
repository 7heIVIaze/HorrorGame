// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"
#include "DoorInterface_cpp.h"
#include "Door_cpp.generated.h"

UCLASS()
class HIDEANDSEEK_API ADoor_cpp : public AActor, public IDoorInterface_cpp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor_cpp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnInteract(class AHorrorGameCharacter* Player) override;

	UFUNCTION()
		virtual void UseInteract(class AHorrorGameCharacter* Player) override;

	UFUNCTION()
		void AIInteract(AActor* Creature);

	UFUNCTION()
		void OpenDoor(float Value);

	UFUNCTION()
		void SetDoorCollision(bool inIsPlayerNear);

	UFUNCTION()
		void PlayerBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void PlayerBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void ChangeDoorCollision();

	UFUNCTION()
		void BreakDoor();

	UFUNCTION()
		void CreatureBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
		TObjectPtr<UStaticMeshComponent> Door;

	/** Please add a variable description */
	UPROPERTY(VisibleAnywhere, Category = "Door")
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
		TObjectPtr<class UBoxComponent> PlayerOverlapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
		TObjectPtr<class UBoxComponent> CreatureOverlapBox;

	/** Please add a variable description */
	UPROPERTY(VisibleAnywhere, Category = "Door")
		FTimeline OpenAndClose; // Create TimeLine 

	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat; // Timeline Curve

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		float DoorRotateAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		bool bIsDoorClosed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		bool bIsDoorLocked = true;

	UPROPERTY(BlueprintReadWrite)
		bool bIsDoorBroken = false;

	UPROPERTY(BlueprintReadWrite)
		bool bIsPlayerNear = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DoorOpenSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DoorCloseSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DoorBreakSound;

	UPROPERTY()
		TArray<AActor*> InteractingCreatures;

	UPROPERTY()
		FTimerHandle Timer;
};