// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorrorGame/HorrorGameCharacter.h"
#include "CustomUI.generated.h"
/**
 * 
 */
UCLASS()
class HORRORGAME_API UCustomUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	//UCustomUI(const FObjectInitializer& ObjectInitializer);

	virtual void AllWidgetInit() {};

	virtual void Init() {};

public:
	AHorrorGameCharacter* Player;
};
