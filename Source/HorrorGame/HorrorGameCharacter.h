// CopyrightNotice=0 2023 Sunggon Kim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/AudioComponent.h"
#include "InteractInterface.h"
#include "CustomDataTables.h"
#include "Components/TimelineComponent.h"
#include "HorrorGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UPointLightComponent;
class USpotLightComponent;
class UGameUI;

UENUM(BlueprintType)
enum class Item_Num : uint8
{
	CigetLighter UMETA(DisplayName = "CigarLighter"),
	FlashLight UMETA(DisplayName = "FlashLight"),
	Key UMETA(DisplayName = "Key"),
	Timer UMETA(DisplayName = "Timer"),
	Sword UMETA(DisplayName = "Sword"),
	Bell UMETA(DisplayName = "Bell"),
	Mirror UMETA(DisplayName = "Mirror"),
	Extinguisher UMETA(DisplayName = "Extinguisher"),
	Cutter UMETA(DisplayName = "Cutter"),
	SoulLantern UMETA(DisplayName = "SoulLantern"),
};

UENUM(BlueprintType)
enum class Player_Status : uint8
{
	Loading UMETA(DisplayName = "Loading"),
	Survive UMETA(DisplayName = "Survive"),
	Catched UMETA(DisplayName = "Catched"),
	Stunned UMETA(DisplayName = "Stunned"),
	Died UMETA(DisplayName = "Died"),
};

UCLASS(config=Game)
class AHorrorGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
public:
	AHorrorGameCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

public: // Unreal Property
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	int32 Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FlashLight", meta = (AllowPrivateAccess = "true"))
	int32 FlashLightBattery;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Extinguisher", meta = (AllowPrivateAccess = "true"))
	int32 ExtinguisherLeft = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cutter", meta = (AllowPrivateAccess = "true"))
	int32 CutterDurability = 5;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patience")
	int32 Patience = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patience")
	int32 PatienceToReduce = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patience")
	bool bIsPatienceReduce = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Walk")
	bool bIsMove = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint")
	bool bIsSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crouch")
	bool bIsCrouch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlashLight")
	bool bIsFlashLightOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlashLight")
	bool bFLIntenseDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CigarLight")
	bool bIsCigarLightOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	bool bisSoundOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	bool bIsHiding = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	Player_Status PlayerStatus = Player_Status::Survive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SoundCue")
	USoundBase* RunStop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SoundCue")
	USoundBase* TurnOnSoundCue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SoundCue")
	USoundBase* CigarLightOnSoundCue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SoundCue")
	class USoundCue* CigarLightOffSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SoundCue")
		class USoundCue* PanicSoundCue; // 패닉 시 낼 소리

	// About Item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	int32 CurrentItemNum = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	int32 InventoryNum = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	FString InteractText = TEXT("");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	FString ErrorInteractText = TEXT("");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patience")
		bool bIsCooldown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patience")
		bool bIsScreaming = false;

	UPROPERTY()
		bool bIsBellSoundOn = false;

public: // Unreal Component
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TArray<FHorrorGameItemData> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UGameUI> GameUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
		UGameUI* GameUIWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CigarLight")
	TObjectPtr<UPointLightComponent> CigarLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlashLight")
	TObjectPtr<USpotLightComponent> FlashLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TObjectPtr<UChildActorComponent> Lantern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TObjectPtr<UChildActorComponent> Sword;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
		TObjectPtr<UChildActorComponent> Mirror;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentItems")
		TSubclassOf<class AItems> ItemActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<UAudioComponent> Sound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		TObjectPtr<UAudioComponent> SprintSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<UAudioComponent> Turnon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		TObjectPtr<UAudioComponent> PanicSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		TObjectPtr<UAudioComponent> HeartBeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TObjectPtr<UAudioComponent> CigarLightOnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TObjectPtr<UAudioComponent> CigarLightOffSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		TObjectPtr<UAudioComponent>BellSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ATimerProjectile_cpp> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Extinguisher")
		TObjectPtr<class UNiagaraComponent> SmokeComponent;
	
	UPROPERTY()
		class AHorrorGamePlayerController* HorrorGamePlayerController;

	UPROPERTY(VisibleAnywhere, Category = "LightMesh")
		FTimeline FlickeringLight; // Create Timeline

	//UPROPERTY(VisibleAnywhere, Category = "LightMesh")
	//	FTimeline RadiusTime; // Create Timeline

	UPROPERTY(EditAnywhere, Category = "LightMesh")
		UCurveFloat* CurveFloat; // Timeline Curve -> 불빛 깜빡이는거 효과 줄 변수

	UPROPERTY(EditAnywhere, Category = "LightMesh")
		class UMaterialInstanceDynamic* PostProcessMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "LightMesh")
		class UMaterialInstance* PostProcessMaterial;
	/*UPROPERTY(EditAnywhere, Category = "PPM")
		UCurveFloat* PPMFloat;*/ // Timeline Curve -> 거울 사용 시 색상 반전 효과 줄 변수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LightBoolean")
		int32 CreatureNum = 0; // Creature의 개수(불 깜박임을 위해서)

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
		TObjectPtr<class UBoxComponent> DoorBoxComp;

	float FlashIntensity = 15000.f, CigarIntensity = 5000.f;
	bool bCanExtinguisherUse = true, bCanItemGet = true;
	int32 SwordCount, MirrorCount, BellCount;

public: // Unreal Function

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	
	UFUNCTION(BlueprintCallable, Category = "FlashLight")
	void AddCigarLight();

	UFUNCTION(BlueprintCallable, Category = "FlashLight")
	void UseCigarLight();

	UFUNCTION()
	void CigarLightOn();

	UFUNCTION(BlueprintCallable, Category = "FlashLight")
	void AddFlashLight();

	UFUNCTION(BlueprintCallable, Category = "FlashLight")
	void UseFlashLight();

	UFUNCTION(BlueprintCallable, Category = "Key")
	void AddKey();

	UFUNCTION(BlueprintCallable, Category = "Key")
	void UseKey();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void AddTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void UseTimer();

	UFUNCTION(BlueprintCallable, Category = "Sword")
	void AddSword();

	UFUNCTION(BlueprintCallable, Category = "Sword")
	void UseSword();

	UFUNCTION(BlueprintCallable, Category = "Bell")
	void AddBell();

	UFUNCTION(BlueprintCallable, Category = "Bell")
	void UseBell();

	UFUNCTION(BlueprintCallable, Category = "Mirror")
	void AddMirror();

	UFUNCTION(BlueprintCallable, Category = "Mirror")
	void UseMirror();

	UFUNCTION(BlueprintCallable, Category = "Extinguisher")
	void AddExtinguisher();

	UFUNCTION(BlueprintCallable, Category = "Extinguisher")
	void UseExtinguisher();

	UFUNCTION(BlueprintCallable, Category = "Door")
		void OnDoorBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Door")
		void OnDoorBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// UFUNCTION(BlueprintCallable, Category = "Extinguisher")
		void OnSprayOverlap(const TArray<FOverlapResult>& OverlapResults);
	
	UFUNCTION(BlueprintCallable, Category = "Cutter")
	void AddCutter();

	UFUNCTION(BlueprintCallable, Category = "Cutter")
	void UseCutter();

	UFUNCTION(BlueprintCallable, Category = "SoulLantern")
		void AddLantern();

	UFUNCTION(BlueprintCallable, Category = "SoulLantern")
		void UseLantern();

	UFUNCTION()
	void StaminaChange();
	
	UFUNCTION()
	void FlashLightBatteryChange();

	UFUNCTION()
	void CurrentItem();

	UFUNCTION(BlueprintCallable)
	void SetPlayerStatus(Player_Status Value);

	UFUNCTION(BlueprintCallable)
	int32 GetStamina();

	UFUNCTION(BlueprintCallable)
	int32 GetFlashLightBattery();

	UFUNCTION(BlueprintCallable)
	int32 GetExtinguisherLeft();

	UFUNCTION(BlueprintCallable)
	int32 GetPatience();

	UFUNCTION(BlueprintCallable)
	FString GetInteractText();

	UFUNCTION(BlueprintCallable)
	FString GetErrorInteractText();

	UFUNCTION(BlueprintCallable)
	bool GetIsHiding();

	UFUNCTION(BlueprintCallable)
	bool GetIsSprinting();

	UFUNCTION(BlueprintCallable)
	Player_Status GetPlayerStatus();

	UFUNCTION(BlueprintCallable)
	void AddPatience(int32 value);

	UFUNCTION(BlueprintCallable)
	void BellSoundFinish();

	UFUNCTION(BlueprintCallable)
		void BreatheSoundFinish();

	UFUNCTION(BlueprintCallable)
		void SetExplainText(FString text, int32 time);

	UFUNCTION(BlueprintCallable)
		void SetErrorText(FString text, int32 time);

private:
	FTimerHandle _loopStaminaTimerHandle, _loopLightTimerHandle, _MirrorTimerHandle;
	// FTimerHandle _CigarLightTimerHandle;
	int32 TextTimer = 0, ErrorTextTimer = 0;
	float cnt = 0.f, ErrorTextCount = 0.f, StunTimer = 0.f, TimeStopTimer = 0.f;
	float InWaterSpeedDown = 0.6f;

	bool bIsInWater = false, bIsTimeStop = false, bIsTimeStopChange = false;
	bool bShouldAttack = false;
	bool bNotifyAttackStart = false;
	
	UPROPERTY()
		UDataTable* ItemTable;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/* Called for Sprint Input */
	void BeginSprint();
	
	void EndSprint();

	/* Called for Crouch Input*/
	void BeginCrouch();

	void EndCrouch();

	void ItemUse();

	// Interact Function
	// UFUNCTION(BlueprintCallable)
	void Interact();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/*UFUNCTION(BlueprintCallable, Category = "Pause")
		void OnGamePause();*/

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool GetLineTraceSingle(AActor* &HitActor);

	UFUNCTION(BlueprintCallable, Category = "CameraNoise")
	void SetCameraComponentNoise(int32 WhichStatus); // 0: 노이즈 해제, 1: 근처에 있음, 2: 추격 시작

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SelectItem(FKey fkey);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void ScrollUpItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void ScrollDownItem();

	UFUNCTION(BlueprintCallable, Category = "Speed")
		void SetIsInWater(bool value);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int32 GetCurrentItemNumber();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FString GetCurrentItemName();

	UFUNCTION(BlueprintCallable, Category = "Object")
		int32 GetObjectNumbers();

	UFUNCTION(BlueprintCallable, Category = "Object")
		int32 GetSwordNumbers();

	UFUNCTION(BlueprintCallable, Category = "Object")
		int32 GetMirrorNumbers();

	UFUNCTION(BlueprintCallable, Category = "Object")
		int32 GetBellNumbers();

	UFUNCTION(BlueprintCallable)
		bool GetIsTimeStop();

	UFUNCTION(BlueprintCallable)
		bool GetIsTimeStopChange();

	UFUNCTION(BlueprintCallable)
		void LevelStart();

	UFUNCTION(BlueprintCallable)
		void LightFlicker(float value);

	UFUNCTION(BlueprintCallable)
		void SetIsTimeStop(bool value);

	UFUNCTION(BlueprintCallable)
		void SetNotifyAttackStart(const bool value);

	UFUNCTION(BlueprintCallable)
		bool GetNotifyAttackStart();

	UFUNCTION(BlueprintCallable)
		void AttackCheck(bool value);

	UFUNCTION(BlueprintCallable)
		bool GetAttackCheck();

	UFUNCTION(BlueprintCallable)
		bool GetIsScreaming();

	UFUNCTION(BlueprintCallable)
		void SetPanicScreamEnd();

	UFUNCTION(BlueprintCallable)
		void SetBrightness(float Value);
};

