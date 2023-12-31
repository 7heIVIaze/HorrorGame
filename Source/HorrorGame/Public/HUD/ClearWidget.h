// CopyrightNotice=0 2023 Sunggon Kim kimdave205@gmail.com

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public: // FUNCTION
	UFUNCTION()
		void OnClickNextStage();

	UFUNCTION()
		void OnClickBackToMain();

	UFUNCTION()
		void OnHoveredNextStage();

	UFUNCTION()
		void OnHoveredBackToMain();

	UFUNCTION()
		void UpdateButtonSlate();

public: // PROPERTY
	UPROPERTY()
		class UButton* NextStageButton; // 다음 스테이지 이동 버튼 => 다음 스테이지가 있으면 뜨고 없으면 안 뜨게

	UPROPERTY()
		class UButton* BackToMainButton; // 메인 화면 버튼

	UPROPERTY()
		FString CurrentLevel; // 현재 레벨

	UPROPERTY()
		int32 MenuNavigationIndex = 0;

	UPROPERTY()
		int32 MenuNumber;

	UPROPERTY()
		bool bHaveNextLevel;
};
