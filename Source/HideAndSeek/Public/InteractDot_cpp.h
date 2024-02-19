// CopyrightNotice=0 2023 Sunggon Kim
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractDot_cpp.generated.h"

//class UInteractText_cpp;
//class UUseInteract_cpp;
UCLASS(Meta=(DisableNativeTick))
class HIDEANDSEEK_API UInteractDot_cpp : public UUserWidget
{
	GENERATED_BODY()
	
	//void InteractUIInit() override;

	//void Refresh();
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void SetInteractText(FText strText);

	UFUNCTION()
		void SetErrorText(FText strText);

	UFUNCTION()
		void SetInteractDot(bool Value);

private:
	UPROPERTY()
		class UImage* InteractDot;

	UPROPERTY()
		class UTextBlock* InteractText;

	UPROPERTY()
		class UTextBlock* ErrorText;
};