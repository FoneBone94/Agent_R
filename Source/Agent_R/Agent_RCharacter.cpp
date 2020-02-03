
#include "Agent_RCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"
//////////////////////////////////////////////////////////////////////////
// AAgent_RCharacter

AAgent_RCharacter::AAgent_RCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.0f);

	// set our turn rates for input
	BaseTurnRate = 35.f;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.01f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attachs the camera to the end of the camera boom 
	FollowCamera->bUsePawnControlRotation = false; // disable free camera rotation based on boom location

	}

//float AAgent_RCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
//{
//	return 0.0f;
//}
void AAgent_RCharacter::BeginPlay()

{
	Super::BeginPlay();
	FullHealth = 1000.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	bCanBeDamaged = true;

}
void AAgent_RCharacter::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);

	//if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);

}
//////////////////////////////////////////////////////////////////////////
// Input

float AAgent_RCharacter::GetHealth()

{

	return HealthPercentage;

}

FText AAgent_RCharacter::GetHealthIntText()

{

	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);

	FString HPS = FString::FromInt(HP);

	FString HealthHUD = HPS + FString(TEXT("%"));

	FText HPText = FText::FromString(HealthHUD);

	return HPText;

}

void AAgent_RCharacter::SetDamageState()

{
		bCanBeDamaged = true;
}

bool AAgent_RCharacter::PlayFlash()

{

	if (redFlash)

	{

		redFlash = false;

		return true;

	}

	
	return false;

}



float AAgent_RCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)

{

	bCanBeDamaged = false;

	redFlash = true;

	UpdateHealth(-DamageAmount);

	DamageTimer();

	return DamageAmount;

}

void AAgent_RCharacter::DamageTimer()

{

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AAgent_RCharacter::SetDamageState, 2.0f, false);

}

void AAgent_RCharacter::UpdateHealth(float HealthChange)

{

	Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);

	HealthPercentage = Health / FullHealth;

}
void AAgent_RCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAgent_RCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAgent_RCharacter::MoveRight);
	
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that treated as a rate of change, such as a joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAgent_RCharacter::TurnAtRate);
	

	}

void AAgent_RCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAgent_RCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAgent_RCharacter::SprintForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

	void AAgent_RCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
				AddMovementInput(Direction, Value);
	}
}

	void AAgent_RCharacter::SprintRight(float Value)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}



	