// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "GameFramework/Character.h"
#include "DrawerClass.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"
#include "Drawer_cpp.generated.h"

class UChildActorComponent;
class UStaticMeshComponent;
class UAudioComponent;
UCLASS()
class HORRORGAME_API ADrawer_cpp : public ADrawerClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrawer_cpp();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//UPROPERTY(VisibleAnywhere, Category = "Drawer")
	//	TObjectPtr<UChildActorComponent> Item;
	///** Please add a variable description */
	//UPROPERTY(VisibleAnywhere, Category = "Drawer")
	//	TObjectPtr<UStaticMeshComponent> Drawer;

	///** Please add a variable description */
	//UPROPERTY(VisibleAnywhere, Category = "Drawer")
	//	TObjectPtr<USceneComponent> DefaultSceneRoot;
	///** Please add a variable description */
	//UPROPERTY(VisibleAnywhere, Category = "Drawer")
	//	FTimeline OpenAndClose; // Create TimeLine 

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	//	TObjectPtr<UAudioComponent> DrawerSound;

	//UPROPERTY(EditAnywhere)
	//	UCurveFloat* CurveFloat; // Timeline Curve

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
	//	float DrawerOpenMove = 80.0f;

	//bool bIsDrawerClosed = true;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Drawer")
	//	bool bIsFirstOpen = false;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
	//	TArray<TSubclassOf<class AItems>> Items;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer")
	//	TArray<float> ItemProbability;

public:
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		virtual void OnInteract() override;

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Drawer")
		virtual void OpenDrawer(float Value) override;
};
