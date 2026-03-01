// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PCPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/PCBaseCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PCGameplayTags.h"
#include "Actors/Components/TargetLockComponent.h"
#include "GAS/PCAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"


APCPlayerController::APCPlayerController()
{
}

void APCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void APCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if(UEnhancedInputComponent* EnhancedInput=Cast<UEnhancedInputComponent>(InputComponent))
	{ 
		check(MoveAction)
		check(SpaceBarAction)
		check(LookAroundAction)
		check(ShiftAction)
		check(CtrlAction)
		
		//Move
		EnhancedInput->BindAction(
				MoveAction,
				ETriggerEvent::Triggered,
				this,
				&APCPlayerController::Move
			);
		//look
		EnhancedInput->BindAction(
				LookAroundAction,
				ETriggerEvent::Triggered,
				this,
				&APCPlayerController::Look
			);
		//SpaceBar
		EnhancedInput->BindAction(
				SpaceBarAction,
				ETriggerEvent::Started,
				this,
				&APCPlayerController::SpaceBarHandle
			);
		//lmb rmb Mouse Button
		EnhancedInput->BindAction(
				LMBAction,
				ETriggerEvent::Started,
				this,
				&APCPlayerController::LMBPressHandle
			);
		EnhancedInput->BindAction(
			LMBAction,
			ETriggerEvent::Triggered,
			this,
			&APCPlayerController::LMBHeldHandle
		);
		EnhancedInput->BindAction(
				LMBAction,
				ETriggerEvent::Completed,
				this,
				&APCPlayerController::LMBReleaseHandle
			);
		EnhancedInput->BindAction(
				RMBAction,
				ETriggerEvent::Started,
				this,
				&APCPlayerController::RMBPressHandle
			);
		EnhancedInput->BindAction(
				RMBAction,
				ETriggerEvent::Triggered,
				this,
				&APCPlayerController::RMBHeldHandle
			);
		EnhancedInput->BindAction(
				RMBAction,
				ETriggerEvent::Completed,
				this,
				&APCPlayerController::RMBReleaseHandle
			);
		//Shift Pressed and Released
		EnhancedInput->BindAction(
            				ShiftAction,
            				ETriggerEvent::Started,
            				this,
            				&APCPlayerController::ShiftHandle
            			);
		EnhancedInput->BindAction(
            				ShiftAction,
            				ETriggerEvent::Completed,
            				this,
            				&APCPlayerController::ShiftHandle
            			);
		//Ctrl Clicked and Released
		EnhancedInput->BindAction(
							CtrlAction,
							ETriggerEvent::Started,
							this,
							&APCPlayerController::CtrlHandle
						);	
		EnhancedInput->BindAction(
							CtrlAction,
							ETriggerEvent::Completed,
							this,
							&APCPlayerController::CtrlHandle
						);	
	}
	
}

void APCPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (GetTargetLockComp() && GetTargetLockComp()->IsTargetLockingEnabled())
	{
		LookAtLockedTarget(DeltaSeconds);
	}
}

// ----------------  input handles start

void APCPlayerController::Move(const FInputActionValue& Value)  
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector2D Movement = Value.Get<FVector2D>();
		const FRotator YawRotation =FRotator(0.f,GetControlRotation().Yaw,0.f);
		const FVector ForwardVector= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightVector= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		ControlledPawn->AddMovementInput(ForwardVector,Movement.X);
		ControlledPawn->AddMovementInput(RightVector,Movement.Y);
	}
}

void APCPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	AddYawInput(LookAxis.X);
	AddPitchInput(LookAxis.Y);
}

void APCPlayerController::SpaceBarHandle(const FInputActionValue& Value)
{
	//space bar action
}

void APCPlayerController::LMBPressHandle(const FInputActionValue& Value)
{
	const auto& PCTags = FPCGameplayTags::Get();
	FGameplayTag InputTag = PCTags.Input_LMB;

	if (bCtrlPressed && bShiftPressed) InputTag = PCTags.Input_LMB_Shift_Ctrl;
	else if (bShiftPressed) InputTag = PCTags.Input_LMB_Shift;
	else if (bCtrlPressed) InputTag = PCTags.Input_LMB_Ctrl;

	
	GetPCAbilitySystem()->AbilityInputPress(InputTag);
}

void APCPlayerController::LMBHeldHandle(const FInputActionValue& Value)
{
}

void APCPlayerController::LMBReleaseHandle(const FInputActionValue& Value)
{
	const auto& PCTags = FPCGameplayTags::Get();
	FGameplayTag InputTag = PCTags.Input_LMB;

	if (bCtrlPressed && bShiftPressed) InputTag = PCTags.Input_LMB_Shift_Ctrl;
	else if (bShiftPressed) InputTag = PCTags.Input_LMB_Shift;
	else if (bCtrlPressed) InputTag = PCTags.Input_LMB_Ctrl;

	GetPCAbilitySystem()->AbilityInputRelease(InputTag);
}

void APCPlayerController::RMBPressHandle(const FInputActionValue& Value)
{
	const auto& PCTags = FPCGameplayTags::Get();
	FGameplayTag InputTag = PCTags.Input_RMB;

	if (bCtrlPressed && bShiftPressed) InputTag = PCTags.Input_RMB_Shift_Ctrl;
	else if (bShiftPressed) InputTag = PCTags.Input_RMB_Shift;
	else if (bCtrlPressed) InputTag = PCTags.Input_RMB_Ctrl;

	
	GetPCAbilitySystem()->AbilityInputPress(InputTag);
}

void APCPlayerController::RMBHeldHandle(const FInputActionValue& Value)
{
}

void APCPlayerController::RMBReleaseHandle(const FInputActionValue& Value)
{
	
}

void APCPlayerController::ShiftHandle(const FInputActionValue& Value)
{
	bShiftPressed = Value.Get<bool>();
}

void APCPlayerController::CtrlHandle(const FInputActionValue& Value)
{
	bCtrlPressed= Value.Get<bool>();
}

// ----------------  input handles end

UTargetLockComponent* APCPlayerController::GetTargetLockComp()
{
	if (!TargetLockComponent)
	{
		if (GetPawn() && GetPawn()->Implements<UCombatInterface>())
		{
			TargetLockComponent =
				ICombatInterface::Execute_GetLockTargetComponent(GetPawn());
		}
	}
	
	return TargetLockComponent;
}

APCBaseCharacter* APCPlayerController::GetPCCharacter()
{
	if (!ControlledCharacter)
	{
		ControlledCharacter=Cast<APCBaseCharacter>(GetPawn());
	}
	
	return ControlledCharacter;
}

UPCAbilitySystemComponent* APCPlayerController::GetPCAbilitySystem()
{
	if (!ASC)
	{
		ASC=Cast<UPCAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ASC;
}

void APCPlayerController::LookAtLockedTarget(float DeltaTime)
{
   
   	if (!GetTargetLockComp()->GetLockedTarget()) return;
   	
   	APawn* MyPawn = GetPawn();
   	if (!MyPawn) return;
	   
   	FVector StartLoc = MyPawn->GetActorLocation();
   	FVector TargetLoc = GetTargetLockComp()->GetLockedTarget()->GetActorLocation();
	   
   	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(StartLoc, TargetLoc);
	   
   	FRotator CurrentRot = GetControlRotation();
   	FRotator SmoothedRot = FMath::RInterpTo(CurrentRot, LookAtRot, DeltaTime, 10.f);
	
	
	
   	SetControlRotation(FRotator(SmoothedRot.Pitch, SmoothedRot.Yaw, 0.f));
    
}
