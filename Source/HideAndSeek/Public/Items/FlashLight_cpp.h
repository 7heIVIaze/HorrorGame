// CopyrightNotice 2023 Sunggon Kim kimdave205@gmail.com. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Items.h"
#include "FlashLight_cpp.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class HIDEANDSEEK_API AFlashLight_cpp : public AItems
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashLight_cpp();

public:
	// Sets FlashLight Actor
	UPROPERTY(VisibleAnywhere, Category = "Root")
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* FlashLightMesh;

public:	
	void OnInteract(class AHorrorGameCharacter* Player) override;

	void UseInteract(class AHorrorGameCharacter* Player) override;
};
