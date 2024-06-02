// CopyrightNotice 2023 Sunggon Kim kimdave205@gmail.com. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/TimelineComponent.h"
#include "DrawerClass.h"
#include "WardrobeDrawer_cpp.generated.h"

UCLASS()
class HIDEANDSEEK_API AWardrobeDrawer_cpp : public ADrawerClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWardrobeDrawer_cpp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/*UPROPERTY(VisibleAnywhere, Category = "Wardrobe")
		TObjectPtr<class UStaticMeshComponent> Drawer;

	UPROPERTY(VisibleAnywhere, Category = "Wardrobe")
		TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, Category = "Wardrobe")
		FTimeline OpenAndClose;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wardrobe")
		TObjectPtr<class UAudioComponent> DrawerSound;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wardrobe")
		float DrawerOpenMove = 80.f;

	bool bIsDrawerClosed = true;*/

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* DrawerOpenSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* DrawerCloseSound;

public:
	//UFUNCTION(BlueprintCallable, Category = "Interaction")
		virtual void OnInteract() override;

	//UFUNCTION(BlueprintCallable, Category = "Drawer")
		virtual void OpenDrawer(float Value) override;
};
