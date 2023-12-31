// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Items/Items.h"
#include "DrawerClass.generated.h"

UCLASS()
class HORRORGAME_API ADrawerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrawerClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Drawer")
		TObjectPtr<UChildActorComponent> Item;

	UPROPERTY(VisibleAnywhere, Category = "Drawer")
		TObjectPtr<UStaticMeshComponent> Drawer;

	/** Please add a variable description */
	UPROPERTY(VisibleAnywhere, Category = "Drawer")
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	//	TObjectPtr<UAudioComponent> DrawerSound;

	UPROPERTY(VisibleAnywhere, Category = "Drawer")
		FTimeline OpenAndClose; // Create TimeLine 

	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat; // Timeline Curve

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
		float DrawerOpenMove = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
		float fNoItemProbability = 0.5f; // 아이템이 안 나올 확률

	bool bIsDrawerClosed = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Drawer")
		bool bIsFirstOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
		TArray<TSubclassOf<class AItems>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
		TArray<float> ItemProbability;

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		virtual void OnInteract();

	UFUNCTION(BlueprintCallable, Category = "Drawer")
		virtual void OpenDrawer(float Value);
};
